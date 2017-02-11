#include "Graphics.h"
#include <Core/Math/Rect.h>
#include <Core/Math/Math.h>
#include <Core/Reflection/ConstructorInfo.h>
#include "Renderer.h"
#include "Vertex.h"
#include "VertexBuffer.h"
#include "Mesh.h"
#include "Font.h"
#include "CommandList.h"

namespace uut
{
	UUT_MODULE_IMPLEMENT(Graphics)
	{
		UUT_REGISTER_CTOR_DEFAULT();
	}

	Graphics::Graphics()
		: _vbufCount(50000)
		, _currentPM(PM_NONE)
		, _nextPM(PM_NONE)
		, _materialType(MT_OPAQUE)
		, _fillMode(FillMode::Solid)
	{
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
		_materialType = type;
	}

	void Graphics::SetFillMode(FillMode mode)
	{
		_fillMode = mode;
	}

	void Graphics::DrawPoint(const Vector3& point, const Color32& color /* = Color32::WHITE */)
	{
		auto mat = GetMaterial(_materialType, Topology::PointList, _fillMode);
		if (!TestBatch(mat, nullptr, 1))
			return;

		mat->vertices[mat->vdxIndex].pos = point;
		mat->vertices[mat->vdxIndex].color = color.ToInt();
		mat->vdxIndex++;
	}

	void Graphics::DrawLine(const Vector3& p0, const Vector3& p1, const Color32& color /* = Color32::WHITE */)
	{
		auto mat = GetMaterial(_materialType, Topology::LineList, _fillMode);
		if (!TestBatch(mat, nullptr, 2))
			return;

		mat->vertices[mat->vdxIndex].pos = p0;
		mat->vertices[mat->vdxIndex].color = color.ToInt();
		mat->vdxIndex++;

		mat->vertices[mat->vdxIndex].pos = p1;
		mat->vertices[mat->vdxIndex].color = color.ToInt();
		mat->vdxIndex++;
	}

	void Graphics::DrawPolyLine(const List<Vector3>& points, const Color32& color)
	{
		if (points.Count() < 2)
			return;

		auto mat = GetMaterial(_materialType, Topology::LineList, _fillMode);
		if (!TestBatch(mat, nullptr, (points.Count() - 1) * 2))
			return;

		const uint32_t col = color.ToInt();
		for (uint i = 1; i < points.Count(); i++)
		{
			mat->vertices[mat->vdxIndex].pos = points[i - 1];
			mat->vertices[mat->vdxIndex].color = col;
			mat->vdxIndex++;

			mat->vertices[mat->vdxIndex].pos = points[i];
			mat->vertices[mat->vdxIndex].color = col;
			mat->vdxIndex++;
		}
	}

	void Graphics::DrawSolidTriangle(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Color32& color /*= Color32::WHITE*/)
	{
		auto mat = GetMaterial(_materialType, Topology::TrinagleList, _fillMode);
		if (!TestBatch(mat, nullptr, 3))
			return;

		mat->vertices[mat->vdxIndex].pos = p0;
		mat->vertices[mat->vdxIndex].color = color.ToInt();
		mat->vdxIndex++;

		mat->vertices[mat->vdxIndex].pos = p1;
		mat->vertices[mat->vdxIndex].color = color.ToInt();
		mat->vdxIndex++;

		mat->vertices[mat->vdxIndex].pos = p2;
		mat->vertices[mat->vdxIndex].color = color.ToInt();
		mat->vdxIndex++;
	}

	void Graphics::DrawTrinagle(const Vertex& v0, const Vertex& v1, const Vertex& v2, const SharedPtr<Texture2D>& texture /*= nullptr*/)
	{
		auto mat = GetMaterial(_materialType, Topology::TrinagleList, _fillMode);
		if (!TestBatch(mat, texture, 3))
			return;

		mat->vertices[mat->vdxIndex++] = v0;
		mat->vertices[mat->vdxIndex++] = v1;
		mat->vertices[mat->vdxIndex++] = v2;
	}

	void Graphics::DrawQuad(const Vertex& v0, const Vertex& v1, const Vertex& v2, const Vertex& v3, const SharedPtr<Texture2D>& texture /*= nullptr*/)
	{
		auto mat = GetMaterial(_materialType, Topology::TrinagleList, _fillMode);
		if (!TestBatch(mat, texture, 6))
			return;

		mat->vertices[mat->vdxIndex++] = v0;
		mat->vertices[mat->vdxIndex++] = v1;
		mat->vertices[mat->vdxIndex++] = v2;

		mat->vertices[mat->vdxIndex++] = v3;
		mat->vertices[mat->vdxIndex++] = v0;
		mat->vertices[mat->vdxIndex++] = v2;
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

	void Graphics::DrawMesh(const Matrix4& transform, const SharedPtr<Mesh>& mesh, const SharedPtr<Texture2D>& texture)
	{
		if (mesh == nullptr)
			return;

		auto& vertices = mesh->GetVertices();
		auto& uvs = mesh->GetUV();
		auto& colors = mesh->GetColors32();
		auto& indexes = mesh->GetIndexes();
		const uint count = indexes.Count();

		auto mat = GetMaterial(_materialType, Topology::TrinagleList, _fillMode);
		if (!TestBatch(mat, texture, count))
			return;

		for (uint i = 0; i < count; i++)
		{
			const uint32_t index = indexes[i];
			mat->vertices[mat->vdxIndex].pos = transform.VectorTransform(vertices[index]);
			mat->vertices[mat->vdxIndex].tex = uvs[index];
			mat->vertices[mat->vdxIndex].color = colors[index].ToInt();
			mat->vdxIndex++;
		}
	}

	void Graphics::DrawPrimitive(Topology topology, const List<Vertex>& vertexes, const SharedPtr<Texture2D>& texture /* = nullptr */)
	{
		const uint count = vertexes.Count();
		if (count == 0)
			return;

		auto mat = GetMaterial(_materialType, Topology::TrinagleList, _fillMode);
		if (!TestBatch(mat, texture, count))
			return;

		for (uint i = 0; i < count; i++)
			mat->vertices[mat->vdxIndex++] = vertexes[i];
	}

	void Graphics::DrawIndexedPrimitive(Topology topology, const List<Vertex>& vertexes,
		const List<uint16_t>& indexes, const SharedPtr<Texture2D>& texture /* = nullptr */)
	{
		const uint count = indexes.Count();
		if (count == 0)
			return;

		auto mat = GetMaterial(_materialType, Topology::TrinagleList, _fillMode);
		if (!TestBatch(mat, texture, count))
			return;

		for (uint i = 0; i < count; i++)
			mat->vertices[mat->vdxIndex++] = vertexes[indexes[i]];
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

	void Graphics::BeginRecord()
	{
		for (auto& mat : _materialList)
		{
			mat->Reset();
			mat->commandList->SetVertexBuffer(mat->vbuffer, sizeof(Vertex));
			mat->vertices = static_cast<Vertex*>(mat->vbuffer->Lock(_vbufCount*Vertex::SIZE));
		}
	}

	void Graphics::EndRecord()
	{
		for (auto& mat : _materialList)
		{
			if (mat->offset < mat->vdxIndex)
			{
				int count = mat->vdxIndex - mat->offset;
				mat->commandList->DrawPrimitive(count, mat->offset);
				mat->offset = mat->vdxIndex;
			}

			mat->vbuffer->Unlock();
			mat->commandList->Close();
		}
	}

	void Graphics::Draw()
	{
		ModuleInstance<Renderer> render;
		for (auto& mat : _materialList)
		{
			if (mat->vdxIndex == 0)
				continue;

			render->Execute(mat->commandList);
		}
	}

	///////////////////////////////////////////////////////////////////////////
	SharedPtr<Graphics::Material> Graphics::GetMaterial(MaterialType type, Topology topology /*= Topology::TrinagleList*/, FillMode fillMode /*= FillMode::Solid*/)
	{
		for (auto& mat : _materialList)
		{
			if (mat->type != type)
				continue;

			auto& desc = mat->renderState->GetDesc();
			if (desc.topology != topology || desc.fillMode != fillMode)
				continue;

			return mat;
		}

		auto mat = SharedPtr<Material>::Make();
		
		RenderStateDesc desc;
		desc.cullMode = CullMode::Disabled;
		desc.fillMode = fillMode;
		desc.zwriteEnable = true;
		desc.alphaRef = 1;
		desc.alphaFunc = CompareFunc::GreaterEqual;
// 		desc.sampler[0].minFilter = TextureFilter::Linear;
// 		desc.sampler[0].magFilter = TextureFilter::Linear;
		desc.inputLayout = Vertex::DECLARE;

		switch (type)
		{
		case uut::Graphics::MT_OPAQUE:
			desc.textureStage[0] = RenderTextureStageState::Opaque;
			break;

		case uut::Graphics::MT_TRANSPARENT:
			desc.alphaBlend = true;
			desc.alphaTest = true;
			desc.textureStage[0] = RenderTextureStageState::Transparent;
			break;
		}

		ModuleInstance<Renderer> renderer;

		mat->renderState = renderer->CreateRenderState(desc);
		mat->commandList = renderer->CreateCommandList();
		mat->vbuffer = renderer->CreateVertexBuffer(Vertex::SIZE*_vbufCount);
		mat->vertices = static_cast<Vertex*>(mat->vbuffer->Lock(_vbufCount*Vertex::SIZE));
		mat->commandList->Reset(mat->renderState);

		_materialList.Add(mat);
		return mat;
	}

	bool Graphics::TestBatch(const SharedPtr<Material>& material, const SharedPtr<Texture2D>& tex, int vrtCount)
	{
		if (material->vdxIndex + vrtCount >= _vbufCount)
			return false;

		if (material->texture != tex)
		{
			if (material->offset < material->vdxIndex)
			{
				int count = material->vdxIndex - material->offset;
				material->commandList->DrawPrimitive(count, material->offset);
				material->offset = material->vdxIndex;
			}

			material->commandList->SetTexture(0, tex);
			material->texture = tex;
		}

		return true;
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

	//////////////////////////////////////////////////////////////////////////
	void Graphics::Material::Reset()
	{
		commandList->Reset(renderState);
	}
}