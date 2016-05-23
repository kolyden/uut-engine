#include "DebugGUI.h"
#include <Core/IO/Input.h>
#include <Video/Renderer.h>
#include <Video/Texture.h>
#include <Video/Vertex.h>
#include <Video/VertexBuffer.h>
#include <Video/IndexBuffer.h>
#include <IMGUI/imgui.h>
#include <SDL2/SDL.h>
#include <Core/Reflection/ConstructorInfo.h>

namespace uut
{
	UUT_MODULE_IMPLEMENT(DebugGUI)
	{
		UUT_REGISTER_CTOR_DEFAULT();
	}

	struct UIVertex
	{
		float x, y, z;
		uint32_t col;
		float tx, ty;
	};

	static List<VertexElement> g_declare = {
		VertexElement(VertexElement::DT_FLOAT3, VertexElement::UT_POSITION),
		VertexElement(VertexElement::DT_DWORD, VertexElement::UT_COLOR, offsetof(UIVertex, col)),
		VertexElement(VertexElement::DT_FLOAT2, VertexElement::UT_TEXCOORD, offsetof(UIVertex, tx)),
	};

	DebugGUI::DebugGUI()
		: _vbSize(0)
		, _ibSize(0)
	{
		_renderer = Renderer::Instance();
		_input = Input::Instance();

		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = nullptr;
		io.LogFilename = nullptr;
		io.UserData = this;

		// Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array.
		io.KeyMap[ImGuiKey_Tab] = SDLK_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
		io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
		io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
		io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
		io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
		io.KeyMap[ImGuiKey_Delete] = SDLK_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = SDLK_BACKSPACE;
		io.KeyMap[ImGuiKey_Enter] = SDLK_RETURN;
		io.KeyMap[ImGuiKey_Escape] = SDLK_ESCAPE;
		io.KeyMap[ImGuiKey_A] = SDLK_a;
		io.KeyMap[ImGuiKey_C] = SDLK_c;
		io.KeyMap[ImGuiKey_V] = SDLK_v;
		io.KeyMap[ImGuiKey_X] = SDLK_x;
		io.KeyMap[ImGuiKey_Y] = SDLK_y;
		io.KeyMap[ImGuiKey_Z] = SDLK_z;

		io.RenderDrawListsFn = &StaticRenderDrawLists;

		_vd = _renderer->CreateVertexDeclaration(g_declare);
		_timer.Start();

		unsigned char* pixels;
		int width, height, pitch;
		io.Fonts->GetTexDataAsAlpha8(&pixels, &width, &height);

		_font = _renderer->CreateTexture(IntVector2(width, height), TextureAccess::Streaming);
		auto pBits = static_cast<uint8_t*>(_font->Lock(&pitch));
		for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
		{
			const auto alpha = pixels[x + y*width];
			auto ptr = (uint32_t*)(pBits + x * 4 + y *pitch);
			*ptr = Color32(255, 255, 255, alpha).ToInt();
		}
			//memcpy((unsigned char *)pBits + pitch * y, pixels + (width * bytes_per_pixel) * y, (width * bytes_per_pixel));
		_font->Unlock();

		io.Fonts->TexID = static_cast<void*>(_font);

		_renderState.cullMode = CullMode::Disabled;
		_renderState.lightning = false;
		_renderState.zbuffer = ZBufferMode::Disable;
		_renderState.zwriteEnable = false;
		_renderState.alphaBlend = true;
		_renderState.blendOp = BlendOperation::Add;
		_renderState.alphaTest = false;
		_renderState.srcBlend = BlendFactor::SrcAlpha;
		_renderState.destBlend = BlendFactor::InvSrcAlpha;
		_renderState.scissorTest = true;

		_renderState.textureStage[0].alphaOp = TextureOperation::Modulate;
		_renderState.textureStage[0].alphaArg1 = TextureArgument::Texture;
		_renderState.textureStage[0].alphaArg2 = TextureArgument::Diffuse;
		_renderState.sampler[0].minFilter = TextureFilter::Linear;
		_renderState.sampler[0].magFilter = TextureFilter::Linear;
	}

	void DebugGUI::NewFrame()
	{
		_timer.Update();
		Vector2 size = _renderer->GetScreenSize();
		auto& io = ImGui::GetIO();

		io.DisplaySize.x = size.x;
		io.DisplaySize.y = size.y;
		io.DeltaTime = _timer.GetDeltaTime();
		io.MousePos.x = static_cast<float>(_input->GetMousePos().x);
		io.MousePos.y = static_cast<float>(_input->GetMousePos().y);
		io.MouseDown[0] = _input->IsMouseButton(0);
		io.MouseDown[1] = _input->IsMouseButton(1);

		_matProj = Matrix4::OrthoOffCenter(
			0, size.x, 0, size.y, 0.1f, 100.0f);

		ImGui::NewFrame();
	}

	void DebugGUI::SetupCamera()
	{
		_renderer->SetTransform(RT_VIEW, Matrix4::Identity);
		_renderer->SetTransform(RT_WORLD, Matrix4::Identity);
		_renderer->SetTransform(RT_PROJECTION, _matProj);
	}

	void DebugGUI::Draw() const
	{
		ImGui::Render();
	}

	bool DebugGUI::Button(const String& title)
	{
		return ImGui::Button(title);
	}

	void DebugGUI::Label(const String& text)
	{
		ImGui::Text(text);
	}

	float DebugGUI::FloatSlider(float value, float minValue, float maxValue)
	{
		float f = value;
		if (ImGui::SliderFloat("", &f, minValue, maxValue))
			return f;

		return value;
	}

	///////////////////////////////////////////////////////////////////////////
	void DebugGUI::RenderDrawLists(ImDrawData* draw_data)
	{
		if (!_vb || _vbSize < draw_data->TotalVtxCount)
		{
			_vbSize = draw_data->TotalVtxCount + 5000;
			_vb = _renderer->CreateVertexBuffer(sizeof(UIVertex)*_vbSize);
		}

		if (!_ib || _ibSize < draw_data->TotalIdxCount)
		{
			_ibSize = draw_data->TotalIdxCount + 10000;
			_ib = _renderer->CreateIndexBuffer(sizeof(ImDrawIdx)*_ibSize, sizeof(ImDrawIdx) == 2 ? false : true);
		}

		const Vector2 size = _renderer->GetScreenSize();

		UIVertex* vtx_dst;
		ImDrawIdx* idx_dst;
		vtx_dst = static_cast<UIVertex*>(_vb->Lock(draw_data->TotalVtxCount*sizeof(UIVertex)));
		idx_dst = static_cast<ImDrawIdx*>(_ib->Lock(draw_data->TotalIdxCount*sizeof(ImDrawIdx)));
		for (int n = 0; n < draw_data->CmdListsCount; n++)
		{
			const ImDrawList* cmd_list = draw_data->CmdLists[n];
			const ImDrawVert* vtx_src = &cmd_list->VtxBuffer[0];
			for (int i = 0; i < cmd_list->VtxBuffer.size(); i++)
			{
				vtx_dst->x = vtx_src->pos.x;
				vtx_dst->y = size.y - vtx_src->pos.y;
				vtx_dst->z = 10.0f;
				vtx_dst->col = (vtx_src->col & 0xFF00FF00) | ((vtx_src->col & 0xFF0000) >> 16) | ((vtx_src->col & 0xFF) << 16);     // RGBA --> ARGB for DirectX9
				vtx_dst->tx = vtx_src->uv.x;
				vtx_dst->ty = vtx_src->uv.y;
				vtx_dst++;
				vtx_src++;
			}
			memcpy(idx_dst, &cmd_list->IdxBuffer[0], cmd_list->IdxBuffer.size() * sizeof(ImDrawIdx));
			idx_dst += cmd_list->IdxBuffer.size();
		}
		_vb->Unlock();
		_ib->Unlock();

		_renderer->SetState(_renderState);
		_renderer->SetVertexBuffer(_vb, sizeof(UIVertex));
		_renderer->SetIndexBuffer(_ib);
		_renderer->SetVertexDeclaration(_vd);

		// Render command lists
		int vtx_offset = 0;
		int idx_offset = 0;
		for (int n = 0; n < draw_data->CmdListsCount; n++)
		{
			const ImDrawList* cmd_list = draw_data->CmdLists[n];
			for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.size(); cmd_i++)
			{
				const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
				if (pcmd->UserCallback)
				{
					pcmd->UserCallback(cmd_list, pcmd);
				}
				else
				{
					//const RECT r = { (LONG)pcmd->ClipRect.x, (LONG)pcmd->ClipRect.y, (LONG)pcmd->ClipRect.z, (LONG)pcmd->ClipRect.w };
					_renderer->SetTexture(0, static_cast<Texture2D*>(pcmd->TextureId));
					_renderer->SetScissorRect(
						IntRect::FromLBRT((int)pcmd->ClipRect.x, (int)pcmd->ClipRect.w, (int)pcmd->ClipRect.z, (int)pcmd->ClipRect.y));
					_renderer->DrawIndexedPrimitive(Topology::TrinagleList,
						vtx_offset, 0, cmd_list->VtxBuffer.size(), idx_offset, pcmd->ElemCount / 3);
				}
				idx_offset += pcmd->ElemCount;
			}
			vtx_offset += cmd_list->VtxBuffer.size();
		}

		_renderer->SetVertexBuffer(nullptr, 0);
		_renderer->SetIndexBuffer(nullptr);
		_renderer->SetVertexDeclaration(nullptr);
		_renderer->SetTexture(0, nullptr);
	}

	void DebugGUI::StaticRenderDrawLists(ImDrawData* draw_data)
	{
		auto module = static_cast<DebugGUI*>(ImGui::GetIO().UserData);
		module->RenderDrawLists(draw_data);
	}
}
