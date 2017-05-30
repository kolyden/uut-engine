#include "DX9Renderer.h"
#include "Core/Windows/Window.h"
#include "DX9Texture2D.h"
#include "DX9VertexBuffer.h"
#include "DX9IndexBuffer.h"
#include "DX9PipelineState.h"
#include "DX9CommandList.h"
#include "DX9Command.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"
#include <Core/Debug.h>

namespace uut
{
	UUT_MODULE_IMPLEMENT(DX9Renderer)
	{}

	DX9Renderer::DX9Renderer()
		: _d3d(nullptr)
		, _d3ddev(nullptr)
		, _statistics {0}
	{
	}

	DX9Renderer::~DX9Renderer()
	{
		if (_d3ddev) _d3ddev->Release();
		if (_d3d) _d3d->Release();
	}

	SharedPtr<PipelineState> DX9Renderer::CreatePipelineState(const PipelineStateDesc& desc)
	{
		// Vertex declaration
		const int count = desc.inputLayout.Count();
		if (count == 0)
		{
			Debug::LogError("No input layout");
			return nullptr;
		}

		auto declare = new D3DVERTEXELEMENT9[count + 1];
		for (int i = 0; i < count; i++)
		{
			auto it = desc.inputLayout[i];
			declare[i].Stream = it.stream;
			declare[i].Offset = it.offset;
			declare[i].Type = static_cast<BYTE>(dx9::Convert(it.type));
			declare[i].Method = D3DDECLMETHOD_DEFAULT;
			declare[i].Usage = static_cast<BYTE>(dx9::Convert(it.usage));
			declare[i].UsageIndex = it.usageIndex;
		}
		declare[count] = D3DDECL_END();// { 0xFF, 0, D3DDECLTYPE_UNUSED, 0, 0, 0 };
		LPDIRECT3DVERTEXDECLARATION9 vd;
		HRESULT ret = _d3ddev->CreateVertexDeclaration(declare, &vd);
		delete[] declare;
		TestReturnCode(ret);
			//return nullptr;

		auto state = SharedPtr<DX9PipelineState>::Make();
		state->_desc = desc;
		state->_vd = vd;

		return state;
	}

	static void CheckRenderState(LPDIRECT3DDEVICE9 dev, D3DRENDERSTATETYPE state, DWORD value)
	{
		DWORD old;
		if (dev->GetRenderState(state, &old) != D3D_OK || old != value)
			dev->SetRenderState(state, value);
	}

	static void SetTextureStageState(LPDIRECT3DDEVICE9 dev, DWORD stage, D3DTEXTURESTAGESTATETYPE state, DWORD value)
	{
		DWORD old;
		if (dev->GetTextureStageState(stage, state, &old) != D3D_OK || old != value)
			dev->SetTextureStageState(stage, state, value);
	}

	static void SetSamplerState(LPDIRECT3DDEVICE9 dev, DWORD sampler, D3DSAMPLERSTATETYPE state, DWORD value)
	{
		DWORD old;
		if (dev->GetSamplerState(sampler, state, &old) != D3D_OK || old != value)
			dev->SetSamplerState(sampler, state, value);
	}

	const RendererStatistics& DX9Renderer::GetStatistics() const
	{
		return _statistics;
	}

	bool DX9Renderer::BeginScene()
	{
		return TestReturnCode(_d3ddev->BeginScene());
	}

	void DX9Renderer::EndScene()
	{
		_d3ddev->EndScene();
	}

	bool DX9Renderer::Present()
	{
		HRESULT ret = _d3ddev->Present(nullptr, nullptr, nullptr, nullptr);
		return TestReturnCode(ret);
	}

	SharedPtr<Texture2D> DX9Renderer::CreateTexture(const Vector2i& size, TextureAccess access)
	{
		LPDIRECT3DTEXTURE9 data;
		HRESULT ret = _d3ddev->CreateTexture(size.x, size.y, 1,
			D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &data, nullptr);
		if (!TestReturnCode(ret))
			return nullptr;

		auto tex = SharedPtr<DX9Texture2D>::Make();
		tex->_data = data;
		tex->_size = size;
		return tex;
	}

	SharedPtr<VertexBuffer> DX9Renderer::CreateVertexBuffer(uint32_t size)
	{
		if (size == 0)
			return nullptr;

		LPDIRECT3DVERTEXBUFFER9 data;
		HRESULT ret = _d3ddev->CreateVertexBuffer(size,
			D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &data, nullptr);
		if (!TestReturnCode(ret))
			return nullptr;

		auto vb = SharedPtr<DX9VertexBuffer>::Make();
		vb->_data = data;
		vb->_size = size;
		return DynamicCast<VertexBuffer>(vb);
	}

	SharedPtr<IndexBuffer> DX9Renderer::CreateIndexBuffer(uint32_t size, bool use32)
	{
		if (size == 0)
			return nullptr;

		LPDIRECT3DINDEXBUFFER9 data;
		D3DFORMAT format = use32 ? D3DFMT_INDEX32 : D3DFMT_INDEX16;
		HRESULT ret = _d3ddev->CreateIndexBuffer(size,
			D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, format, D3DPOOL_DEFAULT, &data, nullptr);
		if (!TestReturnCode(ret))
			return nullptr;

		auto ib = SharedPtr<DX9IndexBuffer>::Make();
		ib->_data = data;
		ib->_size = size;
		return ib;
	}

	///////////////////////////////////////////////////////////////////////////
	SharedPtr<DX9Renderer> DX9Renderer::Create(const SharedPtr<Window>& window)
	{
		if (window == nullptr || !window->IsCreated())
			return nullptr;

		HMODULE libHandle = LoadLibrary(L"d3d9.dll");
		if (libHandle == nullptr)
			return nullptr;

		// Define a function pointer to the Direct3DCreate9Ex function.
		typedef LPDIRECT3D9 (WINAPI *LPDIRECT3DCREATE9)(UINT);

		// Obtain the address of the Direct3DCreate9Ex function. 
		auto createFuncPtr = (LPDIRECT3DCREATE9)GetProcAddress(libHandle, "Direct3DCreate9");
		if (createFuncPtr == nullptr)
		{
			FreeLibrary(libHandle);
			return nullptr;
		}
		
		SDL_SysWMinfo sdlInfo;
		SDL_VERSION(&sdlInfo.version);
		auto sdlWindow = reinterpret_cast<SDL_Window*>(window->GetInternalHandle());
		if (!SDL_GetWindowWMInfo(sdlWindow, &sdlInfo))
		{
			Debug::LogError("Couldn't get window information: %s", SDL_GetError());
			return nullptr;
		}

		LPDIRECT3D9 d3d = createFuncPtr(D3D_SDK_VERSION);
		if (d3d == nullptr)
			return nullptr;

		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		auto renderer = SharedPtr<DX9Renderer>::Make();
		
		renderer->_window = window;
		renderer->_d3d = d3d;
		renderer->_screenSize = window->GetSize();
		HRESULT ret = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
			sdlInfo.info.win.window, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &renderer->_d3ddev);
		if (!TestReturnCode(ret))
		{
			d3d->Release();
			Debug::LogError("Can't create D3D9 Device");
			return nullptr;
		}

		return renderer;
	}

	void DX9Renderer::Execute(const SharedPtr<CommandList>& commandList)
	{
		if (!commandList  || commandList->GetType() != DX9CommandList::GetTypeStatic())
			return;

		auto dx9cmdList = DynamicCast<DX9CommandList>(commandList);

		for (int i = 0; i < dx9cmdList->_commands.Count(); i++)
		{
			auto& command = dx9cmdList->_commands[i];
			HRESULT result = command.Execute(_d3ddev);
			TestReturnCode(result);
		}
	}

	SharedPtr<CommandList> DX9Renderer::CreateCommandList()
	{
		return SharedPtr<DX9CommandList>::Make();
	}

	///////////////////////////////////////////////////////////////////////////
	bool DX9Renderer::TestReturnCode(HRESULT code)
	{
		if (code == D3D_OK)
			return true;

// 		auto str = DXGetErrorStringA(code);
// 		Debug::LogError("D3D9 Error Code %d - \"%s\"", code, str);
// 		return false;

		const int size = 1024;
		static TCHAR buf[size];

		const DWORD flags = FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
		const DWORD ret = ::FormatMessage(flags, NULL, ERROR_BAD_EXE_FORMAT, 0, buf, size, NULL);
		if (FAILED(ret))
		{
			Debug::LogError("D3D9 Error Code %d", code);
			return false;
		}

		Debug::LogError("D3D9 Error Code %d - \"%s\"", code, buf);
		/*Debug::LogError("D3D9: %s - %s",
			DXGetErrorStringA(ret),
			DXGetErrorDescriptionA(ret));*/
		return false;
	}
}