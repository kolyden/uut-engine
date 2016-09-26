#include "BSPLevelLoader.h"
#include <Core/Math/Math.h>
#include <Core/Math/Vector3.h>
#include <Core/IO/Stream.h>
#include <Core/IO/BinaryReader.h>
#include <Video/Mesh.h>
#include "BSPLevel.h"
#include "Q1Utils.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(BSPLevelLoader)
	{}

	struct dentry_t                // A Directory entry
	{
		long  offset;                // Offset to entry, in bytes, from start of file
		long  size;                  // Size of entry in file, in bytes
	};

	struct dheader_t                // The BSP file header
	{
		long  version;               // Model version, must be 0x17 (23).
		dentry_t entities;           // List of Entities.
		dentry_t planes;             // Map Planes.
									 // numplanes = size/sizeof(plane_t)
		dentry_t miptex;             // Wall Textures.
		dentry_t vertices;           // Map Vertices.
									 // numvertices = size/sizeof(vertex_t)
		dentry_t visilist;           // Leaves Visibility lists.
		dentry_t nodes;              // BSP Nodes.
									 // numnodes = size/sizeof(node_t)
		dentry_t texinfo;            // Texture Info for faces.
									 // numtexinfo = size/sizeof(texinfo_t)
		dentry_t faces;              // Faces of each surface.
									 // numfaces = size/sizeof(face_t)
		dentry_t lightmaps;          // Wall Light Maps.
		dentry_t clipnodes;          // clip nodes, for Models.
									 // numclips = size/sizeof(clipnode_t)
		dentry_t leaves;             // BSP Leaves.
									 // numlaves = size/sizeof(leaf_t)
		dentry_t lface;              // List of Faces.
		dentry_t edges;              // Edges of faces.
									 // numedges = Size/sizeof(edge_t)
		dentry_t ledges;             // List of Edges.
		dentry_t models;             // List of Models.
									 // nummodels = Size/sizeof(model_t)
	};

	typedef struct                 // Bounding Box, Float values
	{
		Vector3   min;                // minimum values of X,Y,Z
		Vector3   max;                // maximum values of X,Y,Z
	} boundbox_t;

	typedef struct                 // Bounding Box, Short values
	{
		short   min;                 // minimum values of X,Y,Z
		short   max;                 // maximum values of X,Y,Z
	} bboxshort_t;

	typedef struct                 // Mip Texture
	{
		char   name[16];             // Name of the texture.
		uint32_t width;                // width of picture, must be a multiple of 8
		uint32_t height;               // height of picture, must be a multiple of 8
		uint32_t offset1;              // offset to u_char Pix[width   * height]
		uint32_t offset2;              // offset to u_char Pix[width/2 * height/2]
		uint32_t offset4;              // offset to u_char Pix[width/4 * height/4]
		uint32_t offset8;              // offset to u_char Pix[width/8 * height/8]
	} miptex_t;

	typedef struct
	{
		boundbox_t bound;            // The bounding box of the Model
		Vector3 origin;               // origin of model, usually (0,0,0)
		long node_id0;               // index of first BSP node
		long node_id1;               // index of the first Clip node
		long node_id2;               // index of the second Clip node
		long node_id3;               // usually zero
		long numleafs;               // number of BSP leaves
		long face_id;                // index of Faces
		long face_num;               // number of Faces
	} model_t;

	typedef struct
	{
		uint16_t vertex0;             // index of the start vertex
									 //  must be in [0,numvertices[
		uint16_t vertex1;             // index of the end vertex
									 //  must be in [0,numvertices[
	} edge_t;

	typedef struct
	{
		uint16_t plane_id;            // The plane in which the face lies
									 //           must be in [0,numplanes[ 
		uint16_t side;                // 0 if in front of the plane, 1 if behind the plane
		long ledge_id;               // first edge in the List of edges
									 //           must be in [0,numledges[
		uint16_t ledge_num;           // number of edges in the List of edges
		uint16_t texinfo_id;          // index of the Texture info the face is part of
									 //           must be in [0,numtexinfos[ 
		uint8_t typelight;            // type of lighting, for the face
		uint8_t baselight;            // from 0xFF (dark) to 0 (bright)
		uint8_t light[2];             // two additional light models  
		long lightmap;               // Pointer inside the general light map, or -1
									 // this define the start of the face light map
	} face_t;

	SharedPtr<Resource> BSPLevelLoader::Load(const SharedPtr<Stream>& stream)
	{
		auto reader = SharedPtr<BinaryReader>::Make(stream);

		dheader_t header;
		if (reader->ReadBytes(sizeof(dheader_t), &header) != sizeof(dheader_t))
			return nullptr;

		const int numverts = header.vertices.size / sizeof(Vector3);
		const int numedges = header.edges.size / sizeof(edge_t);
		const int numfaces = header.faces.size / sizeof(face_t);
		const int nummodels = header.models.size / sizeof(model_t);
		const int numlfaces = header.lface.size / sizeof(uint16_t);
		const int numledges = header.ledges.size / sizeof(int16_t);

		auto level = MakeShared<BSPLevel>();

		// Load Textures
		stream->SetPosition(header.miptex.offset);
		long numtex = reader->ReadInt32();
		List<int32_t> texoffsets;
		texoffsets.SetSize(numtex);
		for (int i = 0; i < numtex; i++)
			texoffsets[i] = reader->ReadInt32();

		for (int i = 0; i < numtex; i++)
		{
			stream->SetPosition(header.miptex.offset + texoffsets[i]);
			miptex_t texheader;
			if (reader->ReadBytes(sizeof(miptex_t), &texheader) != sizeof(miptex_t))
				continue;

			stream->SetPosition(header.miptex.offset + texoffsets[i] + texheader.offset1);
			auto tex = uutQ1::Q1Utils::LoadTexture(stream, IntVector2(texheader.width, texheader.height));
			level->_textures.Add(texheader.name, tex);
		}

		// Load Vertices;
		stream->SetPosition(header.vertices.offset);
		List<Vector3> vertexlist;
		vertexlist.SetSize(numverts);
		reader->ReadBytes(vertexlist.GetDataSize(), vertexlist.GetData());

		// Load List of Edges
		stream->SetPosition(header.ledges.offset);
		List<int16_t> ledges;
		ledges.SetSize(numledges);
		reader->ReadBytes(ledges.GetDataSize(), ledges.GetData());

		// Load Edges
		stream->SetPosition(header.edges.offset);
		List<edge_t> edges;
		edges.SetSize(numedges);
		reader->ReadBytes(edges.GetDataSize(), edges.GetData());

		// Load List of Faces
// 		stream->SetPosition(header.lface.offset);
// 		List<uint16_t> lfaces;
// 		lfaces.SetSize(numlfaces);
// 		reader->ReadBytes(lfaces.GetDataSize(), lfaces.GetData());

		// Load Faces
		stream->SetPosition(header.faces.offset);
		List<face_t> faces;
		faces.SetSize(numfaces);
		reader->ReadBytes(faces.GetDataSize(), faces.GetData());

		// Load Models
		stream->SetPosition(header.models.offset);
		List<model_t> models;
		models.SetSize(nummodels);
		reader->ReadBytes(models.GetDataSize(), models.GetData());

		// Make Meshes
		for (int i = 1; i < models.Count(); i++)
		{
			const model_t& model = models[i];

			List<Vector3> vertices;
			List<Vector2> uv;
			List<Color32> colors;
			List<size_t> indexes;

			for (int face_index = model.face_id; face_index < model.face_id + model.face_num; face_index++)
			{
				assert(face_index >= 0);
				const face_t& face = faces[face_index];
				List<Vector3> points;

				for (int ledge_index = face.ledge_id; ledge_index < face.ledge_id + face.ledge_num; ledge_index++)
				{
					int edge_index = ledges[ledge_index];
					if (edge_index < 0)
					{
						const edge_t& edge = edges[-edge_index];
						for (int vertex_index = edge.vertex1; vertex_index >= edge.vertex0; vertex_index--)
						{
							assert(vertex_index >= 0);
							points << vertexlist[vertex_index];
						}
					}
					else
					{
						const edge_t& edge = edges[edge_index];
						for (int vertex_index = edge.vertex0; vertex_index <= edge.vertex1; vertex_index++)
						{
							assert(vertex_index >= 0);
							points << vertexlist[vertex_index];
						}
					}
				}

				for (int j = 1; j + 1 < points.Count(); j++)
				{
					const uint offset = vertices.Count();
					vertices << uutQ1::Q1Utils::ConvertFrom(model.origin + points[0]);
					vertices << uutQ1::Q1Utils::ConvertFrom(model.origin + points[j]);
					vertices << uutQ1::Q1Utils::ConvertFrom(model.origin + points[j + 1]);

					indexes << offset;
					indexes << offset + 1;
					indexes << offset + 2;

					uv.Add(3, Vector2::Zero);
					colors.Add(3, Color32::White);
				}
			}

			auto mesh = MakeShared<Mesh>();
			mesh->SetVertices(vertices);
			mesh->SetUV(uv);
			mesh->SetColors32(colors);
			mesh->SetIndexes(indexes);
			level->_models << mesh;
		}

		return level;
	}
}