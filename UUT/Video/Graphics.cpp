#include "Graphics.h"
#include <Core/Math/Rect.h>
#include <Core/Math/Math.h>
#include "Renderer.h"
#include "Vertex.h"
#include "VertexBuffer.h"
#include "Mesh.h"
#include "Font.h"
#include <Core/Reflection/ConstructorInfo.h>
#include "Material.h"

namespace uut
{
	UUT_MODULE_IMPLEMENT(Graphics)
	{
		UUT_REGISTER_CTOR_DEFAULT();
	}

	Graphics::Graphics()
		: _vbufCount(5000)
		, _topology(Topology::TrinagleList)
		, _vertices(nullptr)
		, _vdxIndex(0)
		, _currentPM(PM_NONE)
		, _nextPM(PM_NONE)
		, _currentMT(MT_OPAQUE)
		, _nextMT(MT_OPAQUE)
		, _currentFM(FillMode::Solid)
		, _nextFM(FillMode::Solid)
	{
		ModuleInstance<Renderer> renderer;
		_vbuf = renderer->CreateVertexBuffer(Vertex::SIZE*_vbufCount);
		_vdec = renderer->CreateVertexDeclaration(Vertex::DECLARE);

		_opaqueMat = renderer->CreateMaterial();
		_opaqueMat->SetTextureStage(RenderTextureStageState::Opaque);

		_transparentMat = renderer->CreateMaterial();
		_transparentMat->SetAlphaBlend(true);
		_transparentMat->SetAlphaTest(true);
		_transparentMat->SetTextureStage(RenderTextureStageState::Transparent);

		_vertices = static_cast<Vertex*>(_vbuf->Lock(_vbufCount*Vertex::SIZE));

// 		_renderState.cullMode = CullMode::Disabled;
		_renderState.fillMode = _currentFM;
		_renderState.zwriteEnable = true;
		_renderState.alphaRef = 1;
		_renderState.alphaFunc = CompareFunc::GreaterEqual;
// 		_renderState.sampler[0].minFilter = TextureFilter::Linear;
// 		_renderState.sampler[0].magFilter = TextureFilter::Linear;

		UpdateMaterial();
		UpdateProjection();
	}

	Graphics::~Graphics()
	{	
	}

	void Graphics::SetProjection(ProjectionMode mode)
	{
		_nextPM = mode;
	}

	void Graphics::SetMaterial(MaterialType type)
	{
		_nextMT = type;
	}

	void Graphics::SetMaterial(const SharedPtr<Material>& material)
	{
		if (!material)
			return;

		_nextMT = MT_CUSTOM;
		_customMat = material;
	}

	void Graphics::SetFillMode(FillMode mode)
	{
		_nextFM = mode;
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
		for (uint i = 1; i < points.Count(); i++)
		{
			_vertices[_vdxIndex].pos = points[i - 1];
			_vertices[_vdxIndex].color = col;
			_vdxIndex++;

			_vertices[_vdxIndex].pos = points[i];
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

	void Graphics::DrawTrinagle(const Vertex& v0, const Vertex& v1, const Vertex& v2, const SharedPtr<Texture2D>& texture /*= nullptr*/)
	{
		TestBatch(Topology::TrinagleList, texture, 3);

		_vertices[_vdxIndex++] = v0;
		_vertices[_vdxIndex++] = v1;
		_vertices[_vdxIndex++] = v2;
	}

	void Graphics::DrawQuad(const Vertex& v0, const Vertex& v1, const Vertex& v2, const Vertex& v3, const SharedPtr<Texture2D>& texture /*= nullptr*/)
	{
		TestBatch(Topology::TrinagleList, texture, 6);

		_vertices[_vdxIndex++] = v0;
		_vertices[_vdxIndex++] = v1;
		_vertices[_vdxIndex++] = v2;

		_vertices[_vdxIndex++] = v3;
		_vertices[_vdxIndex++] = v0;
		_vertices[_vdxIndex++] = v2;
	}

	void Graphics::DrawQuad(const Rect& rect, float z /* = 0.0f */, const SharedPtr<Texture2D>& texture /* = nullptr */, const Color32& color /* = Color32::WHITE */)
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

	void Graphics::DrawQuad(const Rect& rect, float z, const SharedPtr<Texture2D>& texture, const Rect& texRect, const Color32& color)
	{
		const Vector3 p0(rect.GetLeft(), rect.GetTop(), z);
		const Vector3 p1(rect.GetRight(), rect.GetTop(), z);
		const Vector3 p2(rect.GetRight(), rect.GetBottom(), z);
		const Vector3 p3(rect.GetLeft(), rect.GetBottom(), z);

		DrawQuad(
			Vertex(p0, color, Vector2(texRect.x, texRect.y)),
			Vertex(p1, color, Vector2(texRect.x + texRect.width, texRect.y)),
			Vertex(p2, color, Vector2(texRect.x + texRect.width, texRect.y + texRect.height)),
			Vertex(p3, color, Vector2(texRect.x, texRect.y + texRect.height)),
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

		DrawIndexedPrimitive(Topology::LineList,
			{
				Vertex(v0, color), Vertex(v1, color),
				Vertex(v2, color), Vertex(v3, color),
				Vertex(v4, color), Vertex(v5, color),
				Vertex(v6, color), Vertex(v7, color)
			},
			{
				0, 1, 1, 2, 2, 3, 3, 0,
				4, 5, 5, 6, 6, 7, 7, 4,
				0, 4, 4, 7, 7, 3, 3, 0,
				1, 5, 5, 6, 6, 2, 2, 1,
				0, 4, 4, 5, 5, 1, 1, 0,
				3, 7, 7, 6, 6, 2, 2, 3,
			});

// 		DrawPolyLine({ v0, v1, v2, v3, v0 }, color);
// 		DrawPolyLine({ v4, v5, v6, v7, v4 }, color);
// 
// 		DrawPolyLine({ v0, v4, v7, v3, v0 }, color);
// 		DrawPolyLine({ v1, v5, v6, v2, v1 }, color);
// 
// 		DrawPolyLine({ v0, v4, v5, v1, v0 }, color);
// 		DrawPolyLine({ v3, v7, v6, v2, v3 }, color);
	}

	void Graphics::DrawCube(const Vector3& center, float side, const Color32& color, const SharedPtr<Texture2D>& texture)
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

	void Graphics::DrawGeometry(const Matrix4& transform, const SharedPtr<Mesh>& geometry, const SharedPtr<Texture2D>& texture)
	{
		if (!geometry)
			return;

		auto& vertices = geometry->GetVertices();
		auto& uvs = geometry->GetUV();
		auto& colors = geometry->GetColors32();
		auto& indexes = geometry->GetIndexes();
		const uint count = indexes.Count();

		TestBatch(Topology::TrinagleList, texture, count);

		for (uint i = 0; i < count; i++)
		{
			const uint32_t index = indexes[i];
			_vertices[_vdxIndex].pos = transform.VectorTransform(vertices[index]);
			_vertices[_vdxIndex].tex = uvs[index];
			_vertices[_vdxIndex].color = colors[index].ToInt();
			_vdxIndex++;
		}
	}

	void Graphics::DrawPrimitive(Topology topology, const List<Vertex>& vertexes, const SharedPtr<Texture2D>& texture /* = nullptr */)
	{
		const uint count = vertexes.Count();
		if (count == 0)
			return;

		TestBatch(topology, texture, count);

		for (uint i = 0; i < count; i++)
			_vertices[_vdxIndex++] = vertexes[i];
	}

	void Graphics::DrawIndexedPrimitive(Topology topology, const List<Vertex>& vertexes,
		const List<uint16_t>& indexes, const SharedPtr<Texture2D>& texture /* = nullptr */)
	{
		const uint count = indexes.Count();
		if (count == 0)
			return;

		TestBatch(topology, texture, count);

		for (uint i = 0; i < count; i++)
			_vertices[_vdxIndex++] = vertexes[indexes[i]];
	}

	void Graphics::PrintText(const Vector2& position, float z, const String& text, Font* font, const Color32& color)
	{
		if (font == nullptr || text.IsEmpty())
			return;

// 		SetMaterial(MT_TRANSPARENT);
// 		SetProjection(PM_2D);

		Vector2 pos = position;
		IntRect rect;
		Rect tex;
		uint8_t page;

		for (uint i = 0; i < text.Count(); i++)
		{
			const uint32_t code = text[i];
			const uint32_t next = (i < (text.Count() - 1) ? text[i + 1] : 0);
			if (font->PrintToQuad(pos, code, next, rect, tex, page))
				DrawQuad(rect, z, font->GetTexture(page), tex, color);
		}
	}

	void Graphics::Flush()
	{
		DrawAll();
	}

	///////////////////////////////////////////////////////////////////////////
	void Graphics::TestBatch(Topology topology, const SharedPtr<Texture2D>& tex, int vrtCount)
	{
		if (_topology == topology && _texture == tex &&
			_vdxIndex + vrtCount < _vbufCount &&
			_currentMT == _nextMT &&
			_currentPM == _nextPM &&
			_currentFM == _nextFM)
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

		if (_currentFM != _nextFM)
		{
			_currentFM = _nextFM;
			_renderState.fillMode = _currentFM;
		}
	}

	void Graphics::DrawAll()
	{
		_vbuf->Unlock();

		auto render = Renderer::Instance();
		render->SetState(_renderState);
		if (_currentPM != PM_NONE)
			render->SetTransform(RT_PROJECTION, _matProj);

		render->SetTexture(0, _texture);
		render->SetVertexBuffer(_vbuf, Vertex::SIZE);
		render->SetVertexDeclaration(_vdec);

		switch (_topology)
		{
		case Topology::PointList:
			render->DrawPrimitive(_topology, _vdxIndex);
			break;

		case Topology::LineList:
			render->DrawPrimitive(_topology, _vdxIndex / 2);
			break;

		case Topology::TrinagleList:
			render->DrawPrimitive(_topology, _vdxIndex / 3);
			break;

		default:
			break;
		}

		_vdxIndex = 0;
		_texture = nullptr;
		_customMat = nullptr;
		_vertices = static_cast<Vertex*>(_vbuf->Lock(_vbufCount*Vertex::SIZE));
	}

	void Graphics::UpdateProjection()
	{
		auto render = Renderer::Instance();
		const Vector2 size = render->GetScreenSize();
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
		Material* mat = nullptr;
		switch (_currentMT)
		{
		case MT_OPAQUE: mat = _opaqueMat; break;
		case MT_TRANSPARENT: mat = _transparentMat; break;
		case MT_CUSTOM: mat = _customMat; break;
		}

		if (mat == nullptr)
			return;

		_renderState.alphaBlend = mat->IsAlphaBlend();
		_renderState.alphaTest = mat->IsAlphaTest();
		_renderState.textureStage[0] = mat->GetTextureStage();
	}
}