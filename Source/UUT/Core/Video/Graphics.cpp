#include "Graphics.h"
#include "Renderer.h"
#include "Vertex.h"
#include "VertexBuffer.h"
#include <Core/Math/Rect.h>

namespace uut
{
	Graphics::Graphics(Renderer* renderer)
		: _renderer(renderer)
		, _vbufCount(5000)
		, _ibufCount(10000)
		, _topology(Topology::TrinagleList)
		, _vertices(nullptr)
		, _vdxIndex(0)
	{
		_vbuf = _renderer->CreateVertexBuffer(Vertex::SIZE*_vbufCount);
		_vdec = _renderer->CreateVertexDeclaration(Vertex::DECLARE);

		_vertices = static_cast<Vertex*>(_vbuf->Lock(_vbufCount*Vertex::SIZE));
	}

	void Graphics::DrawPoint(const Vector3& point, const Color32& color /* = Color32::WHITE */)
	{
		TestBatch(Topology::PointList, nullptr, 1);

		_vertices[_vdxIndex].pos = point;
		_vertices[_vdxIndex].color = color.ToInt();
		_vdxIndex++;
	}

	void Graphics::DrawLine(const Vector3& p0, const Vector3& p1, const Color32& color /* = Color32::WHITE */)
	{
		TestBatch(Topology::LineList, nullptr, 2);

		_vertices[_vdxIndex].pos = p0;
		_vertices[_vdxIndex].color = color.ToInt();
		_vdxIndex++;

		_vertices[_vdxIndex].pos = p1;
		_vertices[_vdxIndex].color = color.ToInt();
		_vdxIndex++;
	}

	void Graphics::DrawSolidTriangle(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Color32& color /*= Color32::WHITE*/)
	{
		TestBatch(Topology::TrinagleList, nullptr, 3);

		_vertices[_vdxIndex].pos = p0;
		_vertices[_vdxIndex].color = color.ToInt();
		_vdxIndex++;

		_vertices[_vdxIndex].pos = p1;
		_vertices[_vdxIndex].color = color.ToInt();
		_vdxIndex++;

		_vertices[_vdxIndex].pos = p2;
		_vertices[_vdxIndex].color = color.ToInt();
		_vdxIndex++;
	}

	void Graphics::DrawTrinagle(const Vertex& v0, const Vertex& v1, const Vertex& v2, Texture2D* texture /*= nullptr*/)
	{
		TestBatch(Topology::TrinagleList, texture, 3);

		_vertices[_vdxIndex++] = v0;
		_vertices[_vdxIndex++] = v1;
		_vertices[_vdxIndex++] = v2;
	}

	void Graphics::DrawQuad(const Vertex& v0, const Vertex& v1, const Vertex& v2, const Vertex& v3, Texture2D* texture /*= nullptr*/)
	{
		TestBatch(Topology::TrinagleList, texture, 6);

		_vertices[_vdxIndex++] = v0;
		_vertices[_vdxIndex++] = v1;
		_vertices[_vdxIndex++] = v2;

		_vertices[_vdxIndex++] = v3;
		_vertices[_vdxIndex++] = v0;
		_vertices[_vdxIndex++] = v2;
	}

	void Graphics::DrawQuad(const Rect& rect, float z /* = 0.0f */, Texture2D* texture /* = nullptr */, const Color32& color /* = Color32::WHITE */)
	{
		const Vector3 p0(rect.GetLeft(), rect.GetTop(), z);
		const Vector3 p1(rect.GetRight(), rect.GetTop(), z);
		const Vector3 p2(rect.GetRight(), rect.GetBottom(), z);
		const Vector3 p3(rect.GetLeft(), rect.GetBottom(), z);

		DrawQuad(
			Vertex(p0, color, Vector2(0,0)),
			Vertex(p1, color, Vector2(1,0)),
			Vertex(p2, color, Vector2(1,1)),
			Vertex(p3, color, Vector2(0,1)),
			texture);
	}

	void Graphics::Flush()
	{
		DrawAll();
	}

	///////////////////////////////////////////////////////////////////////////
	void Graphics::TestBatch(Topology topology, Texture2D* tex, int vrtCount)
	{
		if (_topology == topology && _texture == tex &&
			_vdxIndex + vrtCount < _vbufCount)
			return;

		if (_vdxIndex > 0)
			DrawAll();

		_topology = topology;
		_texture = tex;
	}

	void Graphics::DrawAll()
	{
		_vbuf->Unlock();

		_renderer->SetTexture(0, _texture);
		_renderer->SetVertexBuffer(_vbuf, Vertex::SIZE);
		_renderer->SetVertexDeclaration(_vdec);

		switch (_topology)
		{
		case Topology::PointList:
			_renderer->DrawPrimitive(_topology, _vdxIndex);
			break;
		case Topology::LineList:
			_renderer->DrawPrimitive(_topology, _vdxIndex / 2);
			break;

		case Topology::TrinagleList:
			_renderer->DrawPrimitive(_topology, _vdxIndex / 3);
			break;
		}

		_vdxIndex = 0;

		_vertices = static_cast<Vertex*>(_vbuf->Lock(_vbufCount*Vertex::SIZE));
	}
}
