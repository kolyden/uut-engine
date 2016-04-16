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
	class VertexDeclaration;
	class IndexBuffer;
	class Texture2D;

	class DebugGUI : public Module
	{
		UUT_MODULE(DebugGUI, Module)
	public:
		explicit DebugGUI(Renderer* renderer, Input* input);

		void NewFrame();

		void SetupCamera();
		void Draw() const;

		bool Button(const String& title);
		void Label(const String& text);
		float FloatSlider(float value, float minValue, float maxValue);

	protected:
		Timer _timer;
		SharedPtr<Renderer> _renderer;
		SharedPtr<Input> _input;
		SharedPtr<VertexBuffer> _vb;
		SharedPtr<VertexDeclaration> _vd;
		SharedPtr<IndexBuffer> _ib;
		SharedPtr<Texture2D> _font;
		Matrix4 _matProj;
		RenderState _renderState;

		int _vbSize;
		int _ibSize;

		void RenderDrawLists(ImDrawData* draw_data);
		static void StaticRenderDrawLists(ImDrawData* draw_data);
	};
}