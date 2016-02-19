#pragma once
#include "Core/Object.h"
#include "Core/Timer.h"
#include "IMGUI/imgui.h"
#include "Core/Math/Vector2.h"
#include "Core/Video/Color.h"

namespace uut
{
	class Input;
	class Renderer;
	class VertexBuffer;
	class VertexDeclaration;
	class IndexBuffer;
	class Texture2D;

	class ImGuiModule : public Object
	{
	public:
		explicit ImGuiModule(Renderer* renderer, Input* input);

		void NewFrame();
		void Draw() const;

	protected:
		Timer _timer;
		SharedPtr<Renderer> _renderer;
		SharedPtr<Input> _input;
		SharedPtr<VertexBuffer> _vb;
		SharedPtr<VertexDeclaration> _vd;
		SharedPtr<IndexBuffer> _ib;
		SharedPtr<Texture2D> _font;

		int _vbSize;
		int _ibSize;

		void RenderDrawLists(ImDrawData* draw_data);
		static void StaticRenderDrawLists(ImDrawData* draw_data);
	};
}