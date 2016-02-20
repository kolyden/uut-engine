#pragma once
#include "Core/Object.h"
#include "Core/Video/Color.h"
#include "Core/Video/Texture2D.h"
#include "Core/Video/Color32.h"
#include "Core/Math/IntRect.h"
#include "Core/Math/Matrix4.h"
#include "VertexDeclaration.h"
#include <Core/Collections/List.h>

namespace uut
{
	class Window;
	class Texture2D;
	class VertexBuffer;
	class IndexBuffer;

	enum class RenderState
	{
		AlphaBlend,
		AlphaTest,
		ScissorTest,
		Lightning,
	};

	enum class Topology
	{
		PointList,
		LineList,
		LineStrip,
		TrinagleList,
		TrinagleStrip,
		TrinagleFan,
	};

	enum RenderTransform
	{
		RT_VIEW,
		RT_WORLD,
		RT_PROJECTION,
	};

	class Renderer : public Object
	{
	public:
		Renderer();
		virtual ~Renderer();

		const IntVector2& GetScreenSize() const { return _screenSize; }
		Window* GetWindow() const { return _window; }

		virtual void ResetStates() = 0;
		virtual void SetState(RenderState state, bool enabled) = 0;
		virtual void SetScissorRect(const IntRect& rect) = 0;

		virtual bool SetTransform(RenderTransform type, const Matrix4& mat) = 0;

		virtual bool BeginScene() = 0;
		virtual void EndScene() = 0;

		virtual bool SetTexture(int stage, Texture2D* texture) = 0;
		virtual bool SetVertexBuffer(VertexBuffer* buffer, uint16_t stride, uint32_t offset = 0) = 0;
		virtual bool SetIndexBuffer(IndexBuffer* buffer) = 0;
		virtual bool SetVertexDeclaration(VertexDeclaration* declare) = 0;

		virtual bool DrawPrimitive(Topology topology, uint32_t primitiveCount, uint32_t offset = 0) = 0;
		virtual bool DrawIndexedPrimitive(Topology topology, int baseVertexIndex, uint32_t minVertexIndex, uint32_t numVertices, uint32_t startIndex, uint32_t primitiveCount) = 0;

		virtual bool Clear(const Color& color = Color::WHITE, float z = 1.0f, uint32_t stencil = 0) = 0;
		virtual bool Present() = 0;

		virtual SharedPtr<Texture2D> CreateTexture(const IntVector2& size, TextureAccess access = TextureAccess::Streaming) = 0;
		virtual SharedPtr<VertexBuffer> CreateVertexBuffer(uint32_t size) = 0;
		virtual SharedPtr<IndexBuffer> CreateIndexBuffer(uint32_t size, bool use32 = false) = 0;
		virtual SharedPtr<VertexDeclaration> CreateVertexDeclaration(const List<VertexElement>& elements) = 0;

	protected:
		SharedPtr<Window> _window;
		IntVector2 _screenSize;
	};
}
