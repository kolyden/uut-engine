#include "Geometry.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(Geometry)
	{}

	Geometry::~Geometry()
	{
	}

	Geometry::Geometry()
		: _changed(false)
	{
	}

// 	void Geometry::Fill(const List<Vertex>& verts, const List<uint32_t>& indexes)
// 	{
// 		const int count = verts.Count();
// 
// 		_vertices.SetSize(count);
// 		_uv.SetSize(count);
// 		_colors.SetSize(count);
// 
// 		for (int i = 0; i < count; i++)
// 		{
// 			_vertices[i] = verts[i].pos;
// 			_uv[i] = verts[i].tex;
// 			_colors[i] = verts[i].col;
// 		}
// 
// 		_indexes = indexes;
// 		_changed = true;
// 	}

// 	void Geometry::Apply()
// 	{
// 		if (!_changed)
// 			return;
// 
// 		_changed = false;
// 	}

	void Geometry::Clear()
	{
		_changed = true;
		_vertices.Clear();
		_uv.Clear();
		_colors.Clear();
		_indexes.Clear();
	}

	void Geometry::SetVertices(const List<Vector3>& vertices)
	{
		if (_vertices.IsEmpty() && vertices.IsEmpty())
			return;

		_vertices = vertices;
		_changed = true;
	}

	const List<Vector3>& Geometry::GetVertices() const
	{
		return _vertices;
	}

	void Geometry::SetUV(const List<Vector2>& uv)
	{
		if (_uv.IsEmpty() && uv.IsEmpty())
			return;

		_uv = uv;
		_changed = true;
	}

	const List<Vector2>& Geometry::GetUV() const
	{
		return _uv;
	}

	void Geometry::SetColors(const List<Color>& colors)
	{
		if (_colors.IsEmpty() && colors.IsEmpty())
			return;

		const int count = colors.Count();
		_colors.SetSize(count);
		for (int i = 0; i < count; i++)
			_colors[i] = colors[i];
		_changed = true;
	}

	List<Color> Geometry::GetColors() const
	{
		List<Color> arr;
		const int count = _colors.Count();
		arr.SetSize(count);
		for (int i = 0; i < count; i++)
			arr[i] = _colors[i];

		return arr;
	}

	void Geometry::SetColors32(const List<Color32>& colors)
	{
		if (_colors.IsEmpty() && colors.IsEmpty())
			return;

		_colors = colors;
		_changed = true;
	}

	const List<Color32>& Geometry::GetColors32() const
	{
		return _colors;
	}

	void Geometry::SetIndexes(const List<uint32_t>& indexes)
	{
		if (_indexes.IsEmpty() && indexes.IsEmpty())
			return;

		_indexes = indexes;
		_changed = true;
	}

	const List<uint32_t>& Geometry::GetIndexes() const
	{
		return _indexes;
	}

// 	void Geometry::SetVertexes(const List<Vertex2>& vertexes)
// 	{
// 		if (_vertices.IsEmpty() && vertexes.IsEmpty())
// 			return;
// 
// 		const int count = vertexes.Count();
// 
// 		_vertices.SetSize(count);
// 		_colors.SetSize(count);
// 		_uv.SetSize(count);
// 		_indexes.SetSize(count);
// 
// 		for (int i = 0; i < count; i++)
// 		{
// 			_vertices[i] = vertexes[i].pos;
// 			_colors[i] = vertexes[i].col;
// 			_uv[i] = vertexes[i].tex;
// 			_indexes[i] = i;
// 		}
// 		_changed = true;
// 	}

// 	void Geometry::AddQuad(const rect2f& rect, const Vector3& tex0, const Vector3& tex1, const DWORD color)
// 	{
// 		const int offset = _vertices.Count();
// 
// 		_vertices << Vector3(rect.x, rect.y);
// 		_vertices << Vector3(rect.x + rect.w, rect.y);
// 		_vertices << Vector3(rect.x + rect.w, rect.y + rect.h);
// 		_vertices << Vector3(rect.x, rect.y + rect.h);
// 
// 		_uv << Vector3(tex0.x, tex0.y);
// 		_uv << Vector3(tex1.x, tex0.y);
// 		_uv << Vector3(tex1.x, tex1.y);
// 		_uv << Vector3(tex0.x, tex1.y);
// 
// 		_colors.Add(4, color);
// 
// 		_indexes << offset + 0;
// 		_indexes << offset + 1;
// 		_indexes << offset + 3;
// 
// 		_indexes << offset + 3;
// 		_indexes << offset + 1;
// 		_indexes << offset + 2;
// 		_changed = true;
// 	}
// 
// 	void Geometry::AddQuad(const rect2f& rect, const rect2f& tex, const DWORD color)
// 	{
// 		AddQuad(rect, tex.GetUpperLeft(), tex.GetLowerRight(), color);
// 	}
// 
// 	void Geometry::AddQuad(const engQuad& quad, DWORD color)
// 	{
// 		AddQuad(quad.m_v[0], quad.m_v[1], quad.m_v[2], quad.m_v[3], color);
// 	}
// 
// 	void Geometry::AddQuad(const engQuadColor& quad)
// 	{
// 		AddQuad(quad.m_v[0], quad.m_v[1], quad.m_v[2], quad.m_v[3], quad.m_color.ToInt());
// 	}
// 
// 	void Geometry::AddQuad(const engVertex& v0, const engVertex& v1, const engVertex& v2, const engVertex& v3, DWORD color /*= 0xFFFFFFFF*/)
// 	{
// 		const int offset = _vertices.Count();
// 
// 		_vertices << Vector3(v0.x, v0.y);
// 		_vertices << Vector3(v1.x, v1.y);
// 		_vertices << Vector3(v2.x, v2.y);
// 		_vertices << Vector3(v3.x, v3.y);
// 
// 		_uv << Vector3(v0.u, v0.v);
// 		_uv << Vector3(v1.u, v1.v);
// 		_uv << Vector3(v2.u, v2.v);
// 		_uv << Vector3(v3.u, v3.v);
// 
// 		_colors.Add(4, color);
// 
// 		_indexes << offset + 0;
// 		_indexes << offset + 1;
// 		_indexes << offset + 3;
// 
// 		_indexes << offset + 3;
// 		_indexes << offset + 1;
// 		_indexes << offset + 2;
// 		_changed = true;
// 	}
// 
// 	void Geometry::AddQuad(const Vertex2& v0, const Vertex2& v1, const Vertex2& v2, const Vertex2& v3)
// 	{
// 		const int offset = _vertices.Count();
// 
// 		_vertices << v0.pos;
// 		_vertices << v1.pos;
// 		_vertices << v2.pos;
// 		_vertices << v3.pos;
// 
// 		_uv << v0.tex;
// 		_uv << v1.tex;
// 		_uv << v2.tex;
// 		_uv << v3.tex;
// 
// 		_colors << v0.col;
// 		_colors << v1.col;
// 		_colors << v2.col;
// 		_colors << v3.col;
// 
// 		_indexes << offset + 0;
// 		_indexes << offset + 1;
// 		_indexes << offset + 3;
// 
// 		_indexes << offset + 3;
// 		_indexes << offset + 1;
// 		_indexes << offset + 2;
// 		_changed = true;
// 	}
}