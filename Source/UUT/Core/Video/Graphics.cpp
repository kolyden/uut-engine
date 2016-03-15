#include "Graphics.h"
#include "Renderer.h"
#include "Vertex.h"
#include "VertexBuffer.h"
#include <Core/Math/Rect.h>
#include <Core/Math/Math.h>

namespace uut
{
	Graphics::Graphics(Renderer* renderer)
		: _renderer(renderer)
		, _vbufCount(5000)
		, _topology(Topology::TrinagleList)
		, _vertices(nullptr)
		, _vdxIndex(0)
		, _currentPM(PM_NONE)
		, _nextPM(PM_NONE)
		, _currentMT(MT_OPAQUE)
		, _nextMT(MT_OPAQUE)
	{
		_vbuf = _renderer->CreateVertexBuffer(Vertex::SIZE*_vbufCount);
		_vdec = _renderer->CreateVertexDeclaration(Vertex::DECLARE);

		_vertices = static_cast<Vertex*>(_vbuf->Lock(_vbufCount*Vertex::SIZE));

// 		_renderState.sampler[0].minFilter = TextureFilter::Linear;
// 		_renderState.sampler[0].magFilter = TextureFilter::Linear;

		UpdateMaterial();
		UpdateProjection();
	}

	void Graphics::SetProjection(ProjectionMode mode)
	{
		_nextPM = mode;
	}

	void Graphics::SetMaterial(MaterialType type)
	{
		_nextMT = type;
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

	void Graphics::DrawPolyLine(const List<Vector3>& points, const Color32& color)
	{
		if (points.Count() < 2)
			return;

		TestBatch(Topology::LineList, nullptr, (points.Count() - 1) * 2);

		const uint32_t col = color.ToInt();
		for (int i = 0; i < points.Count() - 1; i++)
		{
			_vertices[_vdxIndex].pos = points[i];
			_vertices[_vdxIndex].color = col;
			_vdxIndex++;

			_vertices[_vdxIndex].pos = points[i + 1];
			_vertices[_vdxIndex].color = col;
			_vdxIndex++;
		}
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

	void Graphics::DrawSolidCube(const Vector3& center, float side, const Color32& color)
	{
		const float hsize = side / 2;

		const Vector3 v0(center.x - hsize, center.y + hsize, center.z - hsize);
		const Vector3 v1(center.x + hsize, center.y + hsize, center.z - hsize);
		const Vector3 v2(center.x + hsize, center.y - hsize, center.z - hsize);
		const Vector3 v3(center.x - hsize, center.y - hsize, center.z - hsize);

		const Vector3 v4(center.x - hsize, center.y + hsize, center.z + hsize);
		const Vector3 v5(center.x + hsize, center.y + hsize, center.z + hsize);
		const Vector3 v6(center.x + hsize, center.y - hsize, center.z + hsize);
		const Vector3 v7(center.x - hsize, center.y - hsize, center.z + hsize);

		// FRONT
		DrawQuad(
			Vertex(v0, color, Vector2::Zero),
			Vertex(v1, color, Vector2::Right),
			Vertex(v2, color, Vector2::One),
			Vertex(v3, color, Vector2::Up));

		//BACK
		DrawQuad(
			Vertex(v5, color, Vector2::Zero),
			Vertex(v4, color, Vector2::Right),
			Vertex(v7, color, Vector2::One),
			Vertex(v6, color, Vector2::Up));

		// TOP
		DrawQuad(
			Vertex(v4, color, Vector2::Zero),
			Vertex(v5, color, Vector2::Right),
			Vertex(v1, color, Vector2::One),
			Vertex(v0, color, Vector2::Up));

		// BOTTOM
		DrawQuad(
			Vertex(v3, color, Vector2::Zero),
			Vertex(v2, color, Vector2::Right),
			Vertex(v6, color, Vector2::One),
			Vertex(v7, color, Vector2::Up));

		// LEFT
		DrawQuad(
			Vertex(v4, color, Vector2::Zero),
			Vertex(v0, color, Vector2::Right),
			Vertex(v3, color, Vector2::One),
			Vertex(v7, color, Vector2::Up));

		// RIGHT
		DrawQuad(
			Vertex(v1, color, Vector2::Zero),
			Vertex(v5, color, Vector2::Right),
			Vertex(v6, color, Vector2::One),
			Vertex(v2, color, Vector2::Up));
	}

	void Graphics::DrawWireCube(const Vector3& center, float side, const Color32& color /*= Color32::White*/)
	{
		const float hsize = side / 2;

		const Vector3 v0(center.x - hsize, center.y + hsize, center.z - hsize);
		const Vector3 v1(center.x + hsize, center.y + hsize, center.z - hsize);
		const Vector3 v2(center.x + hsize, center.y - hsize, center.z - hsize);
		const Vector3 v3(center.x - hsize, center.y - hsize, center.z - hsize);

		const Vector3 v4(center.x - hsize, center.y + hsize, center.z + hsize);
		const Vector3 v5(center.x + hsize, center.y + hsize, center.z + hsize);
		const Vector3 v6(center.x + hsize, center.y - hsize, center.z + hsize);
		const Vector3 v7(center.x - hsize, center.y - hsize, center.z + hsize);

		DrawPolyLine({ v0, v1, v2, v3, v0 }, color);
		DrawPolyLine({ v4, v5, v6, v7, v4 }, color);

		DrawPolyLine({ v0, v4, v7, v3, v0 }, color);
		DrawPolyLine({ v1, v5, v6, v2, v1 }, color);

		DrawPolyLine({ v0, v4, v5, v1, v0 }, color);
		DrawPolyLine({ v3, v7, v6, v2, v3 }, color);
	}

	void Graphics::DrawCube(const Vector3& center, float side, const Color32& color, Texture2D* texture)
	{
		const float hsize = side / 2;

		const Vector3 v0(center.x - hsize, center.y + hsize, center.z - hsize);
		const Vector3 v1(center.x + hsize, center.y + hsize, center.z - hsize);
		const Vector3 v2(center.x + hsize, center.y - hsize, center.z - hsize);
		const Vector3 v3(center.x - hsize, center.y - hsize, center.z - hsize);

		const Vector3 v4(center.x - hsize, center.y + hsize, center.z + hsize);
		const Vector3 v5(center.x + hsize, center.y + hsize, center.z + hsize);
		const Vector3 v6(center.x + hsize, center.y - hsize, center.z + hsize);
		const Vector3 v7(center.x - hsize, center.y - hsize, center.z + hsize);

		// FRONT
		DrawQuad(
			Vertex(v0, color, Vector2::Zero),
			Vertex(v1, color, Vector2::Right),
			Vertex(v2, color, Vector2::One),
			Vertex(v3, color, Vector2::Up),
			texture);

		//BACK
		DrawQuad(
			Vertex(v5, color, Vector2::Zero),
			Vertex(v4, color, Vector2::Right),
			Vertex(v7, color, Vector2::One),
			Vertex(v6, color, Vector2::Up),
			texture);

		// TOP
		DrawQuad(
			Vertex(v4, color, Vector2::Zero),
			Vertex(v5, color, Vector2::Right),
			Vertex(v1, color, Vector2::One),
			Vertex(v0, color, Vector2::Up),
			texture);

		// BOTTOM
		DrawQuad(
			Vertex(v3, color, Vector2::Zero),
			Vertex(v2, color, Vector2::Right),
			Vertex(v6, color, Vector2::One),
			Vertex(v7, color, Vector2::Up),
			texture);

		// LEFT
		DrawQuad(
			Vertex(v4, color, Vector2::Zero),
			Vertex(v0, color, Vector2::Right),
			Vertex(v3, color, Vector2::One),
			Vertex(v7, color, Vector2::Up),
			texture);

		// RIGHT
		DrawQuad(
			Vertex(v1, color, Vector2::Zero),
			Vertex(v5, color, Vector2::Right),
			Vertex(v6, color, Vector2::One),
			Vertex(v2, color, Vector2::Up),
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
			_vdxIndex + vrtCount < _vbufCount &&
			_currentMT == _nextMT &&
			_currentPM == _nextPM)
			return;

		if (_vdxIndex > 0)
			DrawAll();

		_topology = topology;
		_texture = tex;

		if (_currentMT != _nextMT)
		{
			_currentMT = _nextMT;
			UpdateMaterial();
		}

		if (_currentPM != _nextPM)
		{
			_currentPM = _nextPM;
			UpdateProjection();
		}
	}

	void Graphics::DrawAll()
	{
		_vbuf->Unlock();

		_renderer->SetState(_renderState);
		if (_currentPM != PM_NONE)
			_renderer->SetTransform(RT_PROJECTION, _matProj);

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

	void Graphics::UpdateProjection()
	{
		const Vector2 size = _renderer->GetScreenSize();
		switch (_currentPM)
		{
		case PM_2D:
			_matProj = Matrix4::OrthoOffCenter(0, size.x, 0, size.y, 0.01f, 100.0f);
			break;

		case PM_3D:
			_matProj = Matrix4::PerspectiveFov(Math::PI / 4, size.x / size.y, 1.0f, 1000.0f);
			break;
		}
	}

	void Graphics::UpdateMaterial()
	{
		switch (_currentMT)
		{
		case MT_OPAQUE:
			_renderState.alphaBlend = false;
			_renderState.zwriteEnable = true;
			_renderState.textureStage[0] = RenderTextureStageState::Opaque;
			break;

		case MT_TRANSPARENT:
			_renderState.alphaBlend = true;
			_renderState.zwriteEnable = false;
			_renderState.textureStage[0] = RenderTextureStageState::Transparent;
			break;
		}
	}
}