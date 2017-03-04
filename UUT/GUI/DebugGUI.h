#pragma once
#include <Core/Module.h>
#include <Core/Timer.h>
#include <Core/Math/Matrix4.h>
#include <Video/PipelineState.h>
#include <Video/Viewport.h>

struct ImDrawData;

namespace uut
{
	class Input;
	class Renderer;
	class VertexBuffer;
	class IndexBuffer;
	class Texture2D;
	class PipelineState;
	class CommandList;

	class DebugGUI : public Module
	{
		UUT_MODULE(uut, DebugGUI, Module)
	public:
		DebugGUI();

		void NewFrame();
		void Draw() const;

	protected:
		Timer _timer;
		SharedPtr<PipelineState> _pipeline;
		SharedPtr<CommandList> _commandList;
		SharedPtr<VertexBuffer> _vb;
		SharedPtr<IndexBuffer> _ib;
		SharedPtr<Texture2D> _fontTex;
		Matrix4 _matProj;
		Viewport _viewport;

		int _vbSize;
		int _ibSize;

		void RenderDrawLists(ImDrawData* draw_data);
		static void StaticRenderDrawLists(ImDrawData* draw_data);
	};
}