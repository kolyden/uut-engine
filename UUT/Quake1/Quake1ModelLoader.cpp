#include "Quake1ModelLoader.h"
#include <Core/Debug.h>
#include <Core/IO/BinaryReader.h>
#include <Core/IO/Stream.h>
#include <Core/Math/Quaternion.h>
#include <Video/Renderer.h>
#include <Video/Mesh.h>
#include <Video/Texture2D.h>
#include "Quake1Model.h"

namespace uut
{
	static const Color32 g_palette[] = {
		{ 0,   0,   0 },{ 15,  15,  15 },{ 31,  31,  31 },{ 47,  47,  47 },
		{ 63,  63,  63 },{ 75,  75,  75 },{ 91,  91,  91 },{ 107, 107, 107 },
		{ 123, 123, 123 },{ 139, 139, 139 },{ 155, 155, 155 },{ 171, 171, 171 },
		{ 187, 187, 187 },{ 203, 203, 203 },{ 219, 219, 219 },{ 235, 235, 235 },
		{ 15,  11,   7 },{ 23,  15,  11 },{ 31,  23,  11 },{ 39,  27,  15 },
		{ 47,  35,  19 },{ 55,  43,  23 },{ 63,  47,  23 },{ 75,  55,  27 },
		{ 83,  59,  27 },{ 91,  67,  31 },{ 99,  75,  31 },{ 107,  83,  31 },
		{ 115,  87,  31 },{ 123,  95,  35 },{ 131, 103,  35 },{ 143, 111,  35 },
		{ 11,  11,  15 },{ 19,  19,  27 },{ 27,  27,  39 },{ 39,  39,  51 },
		{ 47,  47,  63 },{ 55,  55,  75 },{ 63,  63,  87 },{ 71,  71, 103 },
		{ 79,  79, 115 },{ 91,  91, 127 },{ 99,  99, 139 },{ 107, 107, 151 },
		{ 115, 115, 163 },{ 123, 123, 175 },{ 131, 131, 187 },{ 139, 139, 203 },
		{ 0,   0,   0 },{ 7,   7,   0 },{ 11,  11,   0 },{ 19,  19,   0 },
		{ 27,  27,   0 },{ 35,  35,   0 },{ 43,  43,   7 },{ 47,  47,   7 },
		{ 55,  55,   7 },{ 63,  63,   7 },{ 71,  71,   7 },{ 75,  75,  11 },
		{ 83,  83,  11 },{ 91,  91,  11 },{ 99,  99,  11 },{ 107, 107,  15 },
		{ 7,   0,   0 },{ 15,   0,   0 },{ 23,   0,   0 },{ 31,   0,   0 },
		{ 39,   0,   0 },{ 47,   0,   0 },{ 55,   0,   0 },{ 63,   0,   0 },
		{ 71,   0,   0 },{ 79,   0,   0 },{ 87,   0,   0 },{ 95,   0,   0 },
		{ 103,   0,   0 },{ 111,   0,   0 },{ 119,   0,   0 },{ 127,   0,   0 },
		{ 19,  19,   0 },{ 27,  27,   0 },{ 35,  35,   0 },{ 47,  43,   0 },
		{ 55,  47,   0 },{ 67,  55,   0 },{ 75,  59,   7 },{ 87,  67,   7 },
		{ 95,  71,   7 },{ 107,  75,  11 },{ 119,  83,  15 },{ 131,  87,  19 },
		{ 139,  91,  19 },{ 151,  95,  27 },{ 163,  99,  31 },{ 175, 103,  35 },
		{ 35,  19,   7 },{ 47,  23,  11 },{ 59,  31,  15 },{ 75,  35,  19 },
		{ 87,  43,  23 },{ 99,  47,  31 },{ 115,  55,  35 },{ 127,  59,  43 },
		{ 143,  67,  51 },{ 159,  79,  51 },{ 175,  99,  47 },{ 191, 119,  47 },
		{ 207, 143,  43 },{ 223, 171,  39 },{ 239, 203,  31 },{ 255, 243,  27 },
		{ 11,   7,   0 },{ 27,  19,   0 },{ 43,  35,  15 },{ 55,  43,  19 },
		{ 71,  51,  27 },{ 83,  55,  35 },{ 99,  63,  43 },{ 111,  71,  51 },
		{ 127,  83,  63 },{ 139,  95,  71 },{ 155, 107,  83 },{ 167, 123,  95 },
		{ 183, 135, 107 },{ 195, 147, 123 },{ 211, 163, 139 },{ 227, 179, 151 },
		{ 171, 139, 163 },{ 159, 127, 151 },{ 147, 115, 135 },{ 139, 103, 123 },
		{ 127,  91, 111 },{ 119,  83,  99 },{ 107,  75,  87 },{ 95,  63,  75 },
		{ 87,  55,  67 },{ 75,  47,  55 },{ 67,  39,  47 },{ 55,  31,  35 },
		{ 43,  23,  27 },{ 35,  19,  19 },{ 23,  11,  11 },{ 15,   7,   7 },
		{ 187, 115, 159 },{ 175, 107, 143 },{ 163,  95, 131 },{ 151,  87, 119 },
		{ 139,  79, 107 },{ 127,  75,  95 },{ 115,  67,  83 },{ 107,  59,  75 },
		{ 95,  51,  63 },{ 83,  43,  55 },{ 71,  35,  43 },{ 59,  31,  35 },
		{ 47,  23,  27 },{ 35,  19,  19 },{ 23,  11,  11 },{ 15,   7,   7 },
		{ 219, 195, 187 },{ 203, 179, 167 },{ 191, 163, 155 },{ 175, 151, 139 },
		{ 163, 135, 123 },{ 151, 123, 111 },{ 135, 111,  95 },{ 123,  99,  83 },
		{ 107,  87,  71 },{ 95,  75,  59 },{ 83,  63,  51 },{ 67,  51,  39 },
		{ 55,  43,  31 },{ 39,  31,  23 },{ 27,  19,  15 },{ 15,  11,   7 },
		{ 111, 131, 123 },{ 103, 123, 111 },{ 95, 115, 103 },{ 87, 107,  95 },
		{ 79,  99,  87 },{ 71,  91,  79 },{ 63,  83,  71 },{ 55,  75,  63 },
		{ 47,  67,  55 },{ 43,  59,  47 },{ 35,  51,  39 },{ 31,  43,  31 },
		{ 23,  35,  23 },{ 15,  27,  19 },{ 11,  19,  11 },{ 7,  11,   7 },
		{ 255, 243,  27 },{ 239, 223,  23 },{ 219, 203,  19 },{ 203, 183,  15 },
		{ 187, 167,  15 },{ 171, 151,  11 },{ 155, 131,   7 },{ 139, 115,   7 },
		{ 123,  99,   7 },{ 107,  83,   0 },{ 91,  71,   0 },{ 75,  55,   0 },
		{ 59,  43,   0 },{ 43,  31,   0 },{ 27,  15,   0 },{ 11,   7,   0 },
		{ 0,   0, 255 },{ 11,  11, 239 },{ 19,  19, 223 },{ 27,  27, 207 },
		{ 35,  35, 191 },{ 43,  43, 175 },{ 47,  47, 159 },{ 47,  47, 143 },
		{ 47,  47, 127 },{ 47,  47, 111 },{ 47,  47,  95 },{ 43,  43,  79 },
		{ 35,  35,  63 },{ 27,  27,  47 },{ 19,  19,  31 },{ 11,  11,  15 },
		{ 43,   0,   0 },{ 59,   0,   0 },{ 75,   7,   0 },{ 95,   7,   0 },
		{ 111,  15,   0 },{ 127,  23,   7 },{ 147,  31,   7 },{ 163,  39,  11 },
		{ 183,  51,  15 },{ 195,  75,  27 },{ 207,  99,  43 },{ 219, 127,  59 },
		{ 227, 151,  79 },{ 231, 171,  95 },{ 239, 191, 119 },{ 247, 211, 139 },
		{ 167, 123,  59 },{ 183, 155,  55 },{ 199, 195,  55 },{ 231, 227,  87 },
		{ 127, 191, 255 },{ 171, 231, 255 },{ 215, 255, 255 },{ 103,   0,   0 },
		{ 139,   0,   0 },{ 179,   0,   0 },{ 215,   0,   0 },{ 255,   0,   0 },
		{ 255, 243, 147 },{ 255, 247, 199 },{ 255, 255, 255 },{ 159,  91,  83 },
	};

	static const Vector3 g_normals[] = {
		{ -0.525731f,  0.000000f,  0.850651f },
		{ -0.442863f,  0.238856f,  0.864188f },
		{ -0.295242f,  0.000000f,  0.955423f },
		{ -0.309017f,  0.500000f,  0.809017f },
		{ -0.162460f,  0.262866f,  0.951056f },
		{ 0.000000f,  0.000000f,  1.000000f },
		{ 0.000000f,  0.850651f,  0.525731f },
		{ -0.147621f,  0.716567f,  0.681718f },
		{ 0.147621f,  0.716567f,  0.681718f },
		{ 0.000000f,  0.525731f,  0.850651f },
		{ 0.309017f,  0.500000f,  0.809017f },
		{ 0.525731f,  0.000000f,  0.850651f },
		{ 0.295242f,  0.000000f,  0.955423f },
		{ 0.442863f,  0.238856f,  0.864188f },
		{ 0.162460f,  0.262866f,  0.951056f },
		{ -0.681718f,  0.147621f,  0.716567f },
		{ -0.809017f,  0.309017f,  0.500000f },
		{ -0.587785f,  0.425325f,  0.688191f },
		{ -0.850651f,  0.525731f,  0.000000f },
		{ -0.864188f,  0.442863f,  0.238856f },
		{ -0.716567f,  0.681718f,  0.147621f },
		{ -0.688191f,  0.587785f,  0.425325f },
		{ -0.500000f,  0.809017f,  0.309017f },
		{ -0.238856f,  0.864188f,  0.442863f },
		{ -0.425325f,  0.688191f,  0.587785f },
		{ -0.716567f,  0.681718f, -0.147621f },
		{ -0.500000f,  0.809017f, -0.309017f },
		{ -0.525731f,  0.850651f,  0.000000f },
		{ 0.000000f,  0.850651f, -0.525731f },
		{ -0.238856f,  0.864188f, -0.442863f },
		{ 0.000000f,  0.955423f, -0.295242f },
		{ -0.262866f,  0.951056f, -0.162460f },
		{ 0.000000f,  1.000000f,  0.000000f },
		{ 0.000000f,  0.955423f,  0.295242f },
		{ -0.262866f,  0.951056f,  0.162460f },
		{ 0.238856f,  0.864188f,  0.442863f },
		{ 0.262866f,  0.951056f,  0.162460f },
		{ 0.500000f,  0.809017f,  0.309017f },
		{ 0.238856f,  0.864188f, -0.442863f },
		{ 0.262866f,  0.951056f, -0.162460f },
		{ 0.500000f,  0.809017f, -0.309017f },
		{ 0.850651f,  0.525731f,  0.000000f },
		{ 0.716567f,  0.681718f,  0.147621f },
		{ 0.716567f,  0.681718f, -0.147621f },
		{ 0.525731f,  0.850651f,  0.000000f },
		{ 0.425325f,  0.688191f,  0.587785f },
		{ 0.864188f,  0.442863f,  0.238856f },
		{ 0.688191f,  0.587785f,  0.425325f },
		{ 0.809017f,  0.309017f,  0.500000f },
		{ 0.681718f,  0.147621f,  0.716567f },
		{ 0.587785f,  0.425325f,  0.688191f },
		{ 0.955423f,  0.295242f,  0.000000f },
		{ 1.000000f,  0.000000f,  0.000000f },
		{ 0.951056f,  0.162460f,  0.262866f },
		{ 0.850651f, -0.525731f,  0.000000f },
		{ 0.955423f, -0.295242f,  0.000000f },
		{ 0.864188f, -0.442863f,  0.238856f },
		{ 0.951056f, -0.162460f,  0.262866f },
		{ 0.809017f, -0.309017f,  0.500000f },
		{ 0.681718f, -0.147621f,  0.716567f },
		{ 0.850651f,  0.000000f,  0.525731f },
		{ 0.864188f,  0.442863f, -0.238856f },
		{ 0.809017f,  0.309017f, -0.500000f },
		{ 0.951056f,  0.162460f, -0.262866f },
		{ 0.525731f,  0.000000f, -0.850651f },
		{ 0.681718f,  0.147621f, -0.716567f },
		{ 0.681718f, -0.147621f, -0.716567f },
		{ 0.850651f,  0.000000f, -0.525731f },
		{ 0.809017f, -0.309017f, -0.500000f },
		{ 0.864188f, -0.442863f, -0.238856f },
		{ 0.951056f, -0.162460f, -0.262866f },
		{ 0.147621f,  0.716567f, -0.681718f },
		{ 0.309017f,  0.500000f, -0.809017f },
		{ 0.425325f,  0.688191f, -0.587785f },
		{ 0.442863f,  0.238856f, -0.864188f },
		{ 0.587785f,  0.425325f, -0.688191f },
		{ 0.688191f,  0.587785f, -0.425325f },
		{ -0.147621f,  0.716567f, -0.681718f },
		{ -0.309017f,  0.500000f, -0.809017f },
		{ 0.000000f,  0.525731f, -0.850651f },
		{ -0.525731f,  0.000000f, -0.850651f },
		{ -0.442863f,  0.238856f, -0.864188f },
		{ -0.295242f,  0.000000f, -0.955423f },
		{ -0.162460f,  0.262866f, -0.951056f },
		{ 0.000000f,  0.000000f, -1.000000f },
		{ 0.295242f,  0.000000f, -0.955423f },
		{ 0.162460f,  0.262866f, -0.951056f },
		{ -0.442863f, -0.238856f, -0.864188f },
		{ -0.309017f, -0.500000f, -0.809017f },
		{ -0.162460f, -0.262866f, -0.951056f },
		{ 0.000000f, -0.850651f, -0.525731f },
		{ -0.147621f, -0.716567f, -0.681718f },
		{ 0.147621f, -0.716567f, -0.681718f },
		{ 0.000000f, -0.525731f, -0.850651f },
		{ 0.309017f, -0.500000f, -0.809017f },
		{ 0.442863f, -0.238856f, -0.864188f },
		{ 0.162460f, -0.262866f, -0.951056f },
		{ 0.238856f, -0.864188f, -0.442863f },
		{ 0.500000f, -0.809017f, -0.309017f },
		{ 0.425325f, -0.688191f, -0.587785f },
		{ 0.716567f, -0.681718f, -0.147621f },
		{ 0.688191f, -0.587785f, -0.425325f },
		{ 0.587785f, -0.425325f, -0.688191f },
		{ 0.000000f, -0.955423f, -0.295242f },
		{ 0.000000f, -1.000000f,  0.000000f },
		{ 0.262866f, -0.951056f, -0.162460f },
		{ 0.000000f, -0.850651f,  0.525731f },
		{ 0.000000f, -0.955423f,  0.295242f },
		{ 0.238856f, -0.864188f,  0.442863f },
		{ 0.262866f, -0.951056f,  0.162460f },
		{ 0.500000f, -0.809017f,  0.309017f },
		{ 0.716567f, -0.681718f,  0.147621f },
		{ 0.525731f, -0.850651f,  0.000000f },
		{ -0.238856f, -0.864188f, -0.442863f },
		{ -0.500000f, -0.809017f, -0.309017f },
		{ -0.262866f, -0.951056f, -0.162460f },
		{ -0.850651f, -0.525731f,  0.000000f },
		{ -0.716567f, -0.681718f, -0.147621f },
		{ -0.716567f, -0.681718f,  0.147621f },
		{ -0.525731f, -0.850651f,  0.000000f },
		{ -0.500000f, -0.809017f,  0.309017f },
		{ -0.238856f, -0.864188f,  0.442863f },
		{ -0.262866f, -0.951056f,  0.162460f },
		{ -0.864188f, -0.442863f,  0.238856f },
		{ -0.809017f, -0.309017f,  0.500000f },
		{ -0.688191f, -0.587785f,  0.425325f },
		{ -0.681718f, -0.147621f,  0.716567f },
		{ -0.442863f, -0.238856f,  0.864188f },
		{ -0.587785f, -0.425325f,  0.688191f },
		{ -0.309017f, -0.500000f,  0.809017f },
		{ -0.147621f, -0.716567f,  0.681718f },
		{ -0.425325f, -0.688191f,  0.587785f },
		{ -0.162460f, -0.262866f,  0.951056f },
		{ 0.442863f, -0.238856f,  0.864188f },
		{ 0.162460f, -0.262866f,  0.951056f },
		{ 0.309017f, -0.500000f,  0.809017f },
		{ 0.147621f, -0.716567f,  0.681718f },
		{ 0.000000f, -0.525731f,  0.850651f },
		{ 0.425325f, -0.688191f,  0.587785f },
		{ 0.587785f, -0.425325f,  0.688191f },
		{ 0.688191f, -0.587785f,  0.425325f },
		{ -0.955423f,  0.295242f,  0.000000f },
		{ -0.951056f,  0.162460f,  0.262866f },
		{ -1.000000f,  0.000000f,  0.000000f },
		{ -0.850651f,  0.000000f,  0.525731f },
		{ -0.955423f, -0.295242f,  0.000000f },
		{ -0.951056f, -0.162460f,  0.262866f },
		{ -0.864188f,  0.442863f, -0.238856f },
		{ -0.951056f,  0.162460f, -0.262866f },
		{ -0.809017f,  0.309017f, -0.500000f },
		{ -0.864188f, -0.442863f, -0.238856f },
		{ -0.951056f, -0.162460f, -0.262866f },
		{ -0.809017f, -0.309017f, -0.500000f },
		{ -0.681718f,  0.147621f, -0.716567f },
		{ -0.681718f, -0.147621f, -0.716567f },
		{ -0.850651f,  0.000000f, -0.525731f },
		{ -0.688191f,  0.587785f, -0.425325f },
		{ -0.587785f,  0.425325f, -0.688191f },
		{ -0.425325f,  0.688191f, -0.587785f },
		{ -0.425325f, -0.688191f, -0.587785f },
		{ -0.587785f, -0.425325f, -0.688191f },
		{ -0.688191f, -0.587785f, -0.425325f }
	};

	static constexpr uint32_t mdl_id = 1330660425;

	struct mdl_header_t
	{
		int32_t id;                     // 0x4F504449 = "IDPO" for IDPOLYGON
		int32_t version;                // Version = 6

		Vector3 scale;                // Model scale factors.
		Vector3 translate;               // Model origin.
		float boundingradius;             // Model bounding radius.
		Vector3 eyeposition;              // Eye position (useless?)

		int32_t numskins;              // the number of skin textures
		int32_t skinwidth;              // Width of skin texture must be multiple of 8
		int32_t skinheight;             // Height of skin texture must be multiple of 8

		int32_t num_verts;               // Number of vertices
		int32_t num_tris;                // Number of triangles surfaces
		int32_t num_frames;              // Number of frames

		int32_t synctype;               // 0 = synchron, 1 = random
		int32_t flags;                  // 0 (see Alias models)
		float size;               // average size of triangles
	};

	static constexpr size_t mdl_header_size = sizeof(mdl_header_t);
	static_assert(mdl_header_size == 84, "Invalid header size");

	struct mdl_texcoord_t
	{
		int onseam;
		int s;
		int t;
	};

	struct mdl_triangle_t
	{
		int facesfront;  /* 0 = backface, 1 = frontface */
		int vertex[3];   /* vertex indices */
	};

	/* Compressed vertex */
	struct mdl_vertex_t
	{
		unsigned char v[3];
		unsigned char normalIndex;
	};

	struct mdl_simpleframe_t
	{
		struct mdl_vertex_t bboxmin; /* bouding box min */
		struct mdl_vertex_t bboxmax; /* bouding box max */
		char name[16];
	};

	UUT_OBJECT_IMPLEMENT(Quake1ModelLoader)
	{}

	SharedPtr<Resource> Quake1ModelLoader::Load(const SharedPtr<Stream>& stream)
	{
		auto reader = SharedPtr<BinaryReader>::Make(stream);

		mdl_header_t header;
		if (reader->ReadBytes(mdl_header_size, &header) != mdl_header_size)
			return nullptr;

		if ((header.id != mdl_id) || (header.version != 6))
			return nullptr;

// 		if (((header.skinwidth % 8) != 0) || ((header.skinheight % 8) != 0))
// 			return nullptr;

		ModuleInstance<Renderer> renderer;
		auto model = SharedPtr<Quake1Model>::Make();

		// Read texture data
		List<uint8_t> data;
		data.SetSize(header.skinwidth * header.skinheight);
		for (int i = 0; i < header.numskins; i++)
		{
			const int32_t type = reader->ReadUint32();
			int32_t count;
			switch (type)
			{
			case 0:
				reader->ReadBytes(data.GetDataSize(), data.GetData());
				break;

			case 1:
				count = reader->ReadUint32();
				reader->SkipBytes(sizeof(float) * count);
				reader->ReadBytes(data.GetDataSize(), data.GetData());
				reader->SkipBytes(header.skinwidth * header.skinheight * (count - 1));
				break;

			default:
				return nullptr;
			}

			auto skin = renderer->CreateTexture(IntVector2(header.skinwidth, header.skinheight), TextureAccess::Streaming);
			int pitch;
			auto bytes = (uint8_t*)skin->Lock(&pitch);
			if (bytes != nullptr)
			{
				for (int y = 0; y < header.skinheight; y++)
				{
					for (int x = 0; x < header.skinwidth; x++)
					{
						const uint8_t index = data[x + y*header.skinwidth];
						const uint32_t offset = x * 4 + y * pitch;
						uint32_t* target = (uint32_t*)(bytes + offset);
// 						if (index != 0xFF)
							target[0] = g_palette[index].ToInt();
// 						else target[0] = Color32::Transparent.ToInt();
					}
				}
				skin->Unlock();
			}
			model->_skins.Add(skin);
		}
		data.Clear();

		// Texture coordinates
		List<mdl_texcoord_t> mdl_tex;
		mdl_tex.SetSize(header.num_verts);
		reader->ReadBytes(mdl_tex.GetDataSize(), mdl_tex.GetData());

		// Triangles
		List<mdl_triangle_t> mdl_tri;
		mdl_tri.SetSize(header.num_tris);
		reader->ReadBytes(mdl_tri.GetDataSize(), mdl_tri.GetData());

		// Frames
		List<mdl_vertex_t> mdl_vert;
		mdl_vert.SetSize(header.num_verts);
		List<Vector3> vertices;
		List<Vector2> uv;
		List<Color32> colors;
		List<size_t> indexes;

		vertices.SetSize(header.num_tris * 3);
		uv.SetSize(header.num_tris * 3);
		colors.SetSize(header.num_tris * 3);
		indexes.SetSize(header.num_tris * 3);

		for (int i = 0; i < header.num_tris * 3; i++)
		{
			indexes[i] = i;
			colors[i] = Color32::White;
		}

		for (int i = 0; i < header.num_frames; i++)
		{
			mdl_simpleframe_t frame;

			const int32_t type = reader->ReadInt32();
			if (type == 0)
			{
				reader->ReadBytes(sizeof(mdl_simpleframe_t), &frame);
				reader->ReadBytes(mdl_vert.GetDataSize(), mdl_vert.GetData());
				model->_animations.Add(frame.name, model->_frames.Count());
			}
			else
			{
				Debug::LogWarning("Can't load Quake 1 MDL with group frames");
				return nullptr;
			}

			auto mesh = SharedPtr<Mesh>::Make();

			static const auto rot = Quaternion::RotationAxis(Vector3::AxisX, -Degree::Angle90) *
				Quaternion::RotationAxis(Vector3::AxisY, Degree::Angle90);
			static const Matrix4 mat = Matrix4::RotationQuaternion(rot);

			for (int i = 0; i < header.num_tris; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					const int index = i * 3 + j;

					const mdl_vertex_t* pvert = &mdl_vert[mdl_tri[i].vertex[j]];

					float s = mdl_tex[mdl_tri[i].vertex[j]].s;
					float t = mdl_tex[mdl_tri[i].vertex[j]].t;

					if (!mdl_tri[i].facesfront && mdl_tex[mdl_tri[i].vertex[j]].onseam)
						s += 0.5f*header.skinwidth;

					const float tx = (s + 0.5f) / header.skinwidth;
					const float ty = (t + 0.5f) / header.skinheight;
					uv[index] = Vector2(tx, ty);

					const Vector3 normal = g_normals[pvert->normalIndex];

					const float x = (header.scale[0] * pvert->v[0]) + header.translate[0];
					const float y = (header.scale[1] * pvert->v[1]) + header.translate[1];
					const float z = (header.scale[2] * pvert->v[2]) + header.translate[2];
					vertices[index] = mat.VectorTransform(Vector3(x, -y, z));
				}
			}

			mesh->SetVertices(vertices);
			mesh->SetUV(uv);
			mesh->SetColors32(colors);
			mesh->SetIndexes(indexes);

			model->_frames << mesh;
		}

		return model;
	}
}