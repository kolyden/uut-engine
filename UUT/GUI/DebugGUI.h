#pragma once
#include <Core/Module.h>
#include <Core/Timer.h>
#include <Core/Math/Matrix4.h>
#include <Video/RenderState.h>

struct ImDrawData;

namespace uut
{
	class Input;
	class Renderer;
	class VertexBuffer;
	class IndexBuffer;
	class Texture2D;
	class RenderState;
	class CommandList;

	class DebugGUI : public Module
	{
		UUT_MODULE(uut, DebugGUI, Module)
	public:
		DebugGUI();

		void NewFrame();

		void SetupCamera();
		void Draw() const;

	protected:
		Timer _timer;
		SharedPtr<RenderState> _pipeline;
		SharedPtr<CommandList> _commandList;
		SharedPtr<VertexBuffer> _vb;
		SharedPtr<IndexBuffer> _ib;
		SharedPtr<Texture2D> _fontTex;
		Matrix4 _matProj;

		int _vbSize;
		int _ibSize;

		void RenderDrawLists(ImDrawData* draw_data);
		static void StaticRenderDrawLists(ImDrawData* draw_data);
	};
}