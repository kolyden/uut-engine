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
#include "Viewport.h"
#include "Camera.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(Graphics)
	{
		//UUT_REGISTER_CTOR_DEFAULT();
	}

	Graphics::Graphics(MaterialType material, ProjectionMode projection, FillMode fillMode)
		: _vbufCount(50000)
		, _currentMT(material)
		, _nextMT(material)
		, _currentPM(projection)
		, _nextPM(projection)
	{
		ModuleInstance<Renderer> renderer;

		PipelineStateDesc desc;
		desc.fillMode = fillMode;
		desc.cullMode = CullMode::Disabled;
		desc.alphaFunc = CompareFunc::GreaterEqual;
		desc.inputLayout = Vertex::DECLARE;
// 		desc.sampler[0].minFilter = TextureFilter::Linear;
// 		desc.sampler[0].magFilter = TextureFilter::Linear;

		desc.zwriteEnable = true;
		desc.textureStage[0] = RenderTextureStageState::Opaque;
		_opaqueState = renderer->CreatePipelineState(desc);

		desc.cullMode = CullMode::Disabled;
		desc.lightning = false;
		desc.zbuffer = ZBufferMode::Disable;
		desc.zwriteEnable = false;
		desc.alphaBlend = true;
		desc.blendOp = BlendOperation::Add;
		desc.alphaTest = false;
		desc.srcBlend = BlendFactor::SrcAlpha;
		desc.destBlend = BlendFactor::InvSrcAlpha;
		desc.alphaBlend = true;
		desc.alphaTest = true;
		desc.zwriteEnable = false;
		desc.textureStage[0].alphaOp = TextureOperation::Modulate;
		desc.textureStage[0].alphaArg1 = TextureArgument::Texture;
		desc.textureStage[0].alphaArg2 = TextureArgument::Diffuse;
// 			desc.textureStage[0] = RenderTextureStageState::Transparent;

		_alphaState = renderer->CreatePipelineState(desc);
		_commandList = renderer->CreateCommandList();
		_vbuffer = renderer->CreateVertexBuffer(Vertex::SIZE*_vbufCount);
	}

	Graphics::~Graphics()
	{	
	}

	void Graphics::SetMaterial(MaterialType material)
	{
		_nextMT = material;
	}

	void Graphics::SetProjection(ProjectionMode projection)
	{
		_nextPM = projection;
	}

	void Graphics::SetViewport(const Viewport& viewport)
	{
		_commandList->SetViewport(viewport);
	}

	void Graphics::SetCamera(const SharedPtr<Camera>& camera)
	{
		Flush();
		camera->Setup(_commandList);
	}

	void Graphics::SetViewMatrix(const Matrix4& matrix)
	{
		Flush();
		_commandList->SetTransform(RT_VIEW, matrix);
	}

	void Graphics::Clear(const Color32& color /*= Color32::White*/, float z /*= 1.0f*/, uint32_t stencil /*= 0*/)
	{
		_commandList->Clear(color, z, stencil);
	}

	void Graphics::DrawPoint(const Vector3& point, const Color32& color /* = Color32::WHITE */)
	{
		if (!TestBatch(Topology::PointList, nullptr, 1))
			return;

		_vertices[_vdxIndex].pos = point;
		_vertices[_vdxIndex].color = color.ToInt();
		_vdxIndex++;
	}

	void Graphics::DrawLine(const Vector3& p0, const Vector3& p1, const Color32& color /* = Color32::WHITE */)
	{
		if (!TestBatch(Topology::LineList, nullptr, 2))
			return;

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

		if (!TestBatch(Topology::LineList, nullptr, (points.Count() - 1) * 2))
			return;

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
		if (!TestBatch(Topology::TriangleList, nullptr, 3))
			return;

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
		if (!TestBatch(Topology::TriangleList, texture, 3))
			return;

		_vertices[_vdxIndex++] = v0;
		_vertices[_vdxIndex++] = v1;
		_vertices[_vdxIndex++] = v2;
	}

	void Graphics::DrawQuad(const Vertex& v0, const Vertex& v1, const Vertex& v2, const Vertex& v3, const SharedPtr<Texture2D>& texture /*= nullptr*/)
	{
		if (!TestBatch(Topology::TriangleList, texture, 6))
			return;

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

	void Graphics::DrawMesh(const Matrix4& transform, const SharedPtr<Mesh>& mesh, const SharedPtr<Texture2D>& texture)
	{
		if (mesh == nullptr)
			return;

		auto& vertices = mesh->GetVertices();
		auto& uvs = mesh->GetUV();
		auto& colors = mesh->GetColors32();
		auto& indexes = mesh->GetIndexes();
		const uint count = indexes.Count();

		if (!TestBatch(Topology::TriangleList, texture, count))
			return;

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

		if (!TestBatch(Topology::TriangleList, texture, count))
			return;

		for (uint i = 0; i < count; i++)
			_vertices[_vdxIndex++] = vertexes[i];
	}

	void Graphics::DrawIndexedPrimitive(Topology topology, const List<Vertex>& vertexes,
		const List<uint16_t>& indexes, const SharedPtr<Texture2D>& texture /* = nullptr */)
	{
		const uint count = indexes.Count();
		if (count == 0)
			return;

		if (!TestBatch(Topology::TriangleList, texture, count))
			return;

		for (uint i = 0; i < count; i++)
			_vertices[_vdxIndex++] = vertexes[indexes[i]];
	}

	void Graphics::PrintText(const Vector2& position, float z, const String& text, Font* font, const Color32& color)
	{
		if (font == nullptr || text.IsEmpty())
			return;

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
		_vertices = static_cast<Vertex*>(_vbuffer->Lock(_vbufCount*Vertex::SIZE));
		_vdxIndex = 0;
		_offset = 0;
		_nextMT = _currentMT;		
		_nextPM = _currentPM;
		
		_commandList->SetVertexBuffer(_vbuffer, sizeof(Vertex));
		UpdatePipeline();
		UpdateProjection();
		_commandList->SetTransform(RT_VIEW, Matrix4::Identity);
		_commandList->SetTransform(RT_WORLD, Matrix4::Identity);
	}

	void Graphics::EndRecord()
	{
		if (_offset < _vdxIndex)
		{
			int count = GetPrimitiveCount(_vdxIndex - _offset);
			_commandList->DrawPrimitive(count, _offset);
			_offset = _vdxIndex;
		}

		_vbuffer->Unlock();
		_vertices = nullptr;
		_commandList->Close();
	}

	void Graphics::Draw()
	{
		ModuleInstance<Renderer> render;
		render->Execute(_commandList);
	}

	///////////////////////////////////////////////////////////////////////////
	void Graphics::Flush()
	{
		if (_offset < _vdxIndex)
		{
			int count = GetPrimitiveCount(_vdxIndex - _offset);
			_commandList->DrawPrimitive(count, _offset);
			_offset = _vdxIndex;
		}
	}

	bool Graphics::TestBatch(Topology topology, const SharedPtr<Texture2D>& tex, int vrtCount)
	{
		if (_vdxIndex + vrtCount >= _vbufCount)
			return false;

		if (_texture != tex || _commandList->GetTopology() != topology)
		{
			Flush();

			if (_texture != tex)
			{
				_commandList->SetTexture(0, tex);
				_texture = tex;
			}
			if (_commandList->GetTopology() != topology)
				_commandList->SetTopology(topology);
		}

		if (_nextMT != _currentMT)
		{
			_currentMT = _nextMT;
			UpdatePipeline();
		}

		if (_nextPM != _currentPM)
		{
			_currentPM = _nextPM;
			UpdateProjection();
		}

		return true;
	}

	int Graphics::GetPrimitiveCount(int vertexCount) const
	{
		switch (_commandList->GetTopology())
		{
		case uut::Topology::PointList:
			return vertexCount;

		case uut::Topology::LineList:
			return vertexCount / 2;

		case uut::Topology::LineStrip:
			return vertexCount - 1;

		case uut::Topology::TriangleList:
			return vertexCount / 3;

		case uut::Topology::TriangleStrip:
			return vertexCount - 2;

		case uut::Topology::TriangleFan:
			return vertexCount - 2;
		}

		return 0;
	}

	void Graphics::UpdateProjection()
	{
		ModuleInstance<Renderer> render;


		const Vector2 size = render->GetScreenSize();
		Matrix4 matrix;
		switch (_currentPM)
		{
		case PM_2D:
			matrix = Matrix4::OrthoOffCenter(0, size.x, 0, size.y, 0.01f, 100.0f);
			_commandList->SetTransform(RT_PROJECTION, matrix);
			break;

		case PM_3D:
			matrix = Matrix4::PerspectiveFov(Math::PI / 4, size.x / size.y, 1.0f, 1000.0f);
			_commandList->SetTransform(RT_PROJECTION, matrix);
			break;
		}
	}

	void Graphics::UpdatePipeline()
	{
		switch (_currentMT)
		{
		case uut::Graphics::MT_OPAQUE:
			_commandList->SetPipelineState(_opaqueState);
			break;

		case uut::Graphics::MT_TRANSPARENT:
			_commandList->SetPipelineState(_alphaState);
			break;
		}
	}
}