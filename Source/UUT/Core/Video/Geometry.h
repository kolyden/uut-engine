#pragma once
#include <Core/Object.h>
#include <Core/Collections/List.h>
#include <Core/Math/Vector3.h>
#include <Core/Math/Vector2.h>
#include <Core/Video/Color.h>
#include <Core/Video/Color32.h>

namespace uut
{
	// hardware? vertex and index buffer
	class Geometry : public Object
	{
		UUT_OBJECT(Geometry, Object)
	public:
		Geometry();
		virtual ~Geometry();

// 		void Fill(const List<Vertex>& verts, const List<uint32_t>& indexes);
// 		void Apply();
		void Clear();

		void SetVertices(const List<Vector3>& vertices);
		const List<Vector3>& GetVertices() const;

		void SetUV(const List<Vector2>& uv);
		const List<Vector2>& GetUV() const;

		void SetColors(const List<Color>& colors);
		List<Color> GetColors() const;

		void SetColors32(const List<Color32>& colors);
		const List<Color32>& GetColors32() const;

		void SetIndexes(const List<uint32_t>& indexes);
		const List<uint32_t>& GetIndexes() const;

// 		void SetVertexes(const List<Vertex>& vertexes);

		List<Vector3>& GetVertices() { return _vertices; }
		List<Vector2>& GetUV() { return _uv; }
		List<Color32>& GetColors32() { return _colors; }
		List<uint32_t>& GetIndexes() { return _indexes; }

// 		void AddQuad(const rect2f& rect, const Vector3& tex0, const Vector3& tex1, const DWORD color);
// 		void AddQuad(const rect2f& rect, const rect2f& tex, const DWORD color);
// 		void AddQuad(const engQuad& quad, DWORD color = 0xFFFFFFFF);
// 		void AddQuad(const engQuadColor& quad);
// 		void AddQuad(const engVertex& v0, const engVertex& v1, const engVertex& v2, const engVertex& v3, DWORD color = 0xFFFFFFFF);
// 		void AddQuad(const Vertex& v0, const Vertex& v1, const Vertex& v2, const Vertex& v3);

	protected:
		List<Vector3> _vertices;
		List<Vector2> _uv;
		List<Color32> _colors;
		List<uint32_t> _indexes;
		bool _changed;
	};
}