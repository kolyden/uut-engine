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

#include <d3d9.h>
//#include <DxErr.h>
//#pragma comment(lib, "d3dx9.lib")
//#pragma comment(lib, "dxerr.lib")

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

	SharedPtr<PipelineState> DX9Renderer::CreateRenderState(const PipelineStateDesc& desc)
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
			declare[i].Type = static_cast<BYTE>(Convert(it.type));
			declare[i].Method = D3DDECLMETHOD_DEFAULT;
			declare[i].Usage = static_cast<BYTE>(Convert(it.usage));
			declare[i].UsageIndex = it.usageIndex;
		}
		declare[count] = D3DDECL_END();// { 0xFF, 0, D3DDECLTYPE_UNUSED, 0, 0, 0 };
		LPDIRECT3DVERTEXDECLARATION9 vd;
		HRESULT ret = _d3ddev->CreateVertexDeclaration(declare, &vd);
		delete[] declare;
		if (!TestReturnCode(ret))
			return nullptr;

		auto state = SharedPtr<DX9PipelineState>::Make();
		state->_desc = desc;
		state->_vd = vd;

		return state;
	}

	template<typename T>
	static bool CheckState(const PipelineStateDesc& state, const PipelineStateDesc& check, T (PipelineStateDesc::*var), bool force)
	{
		if (force || (state.*var) != (check.*var))
			return true;

		return false;
	}

	template<typename T>
	static bool CheckState(const RenderTextureStageState& state, const RenderTextureStageState& check, T(RenderTextureStageState::*var), bool force)
	{
		if (force || (state.*var) != (check.*var))
			return true;

		return false;
	}

	template<typename T>
	static bool CheckState(const RenderSamplerState& state, const RenderSamplerState& check, T(RenderSamplerState::*var), bool force)
	{
		if (force || (state.*var) != (check.*var))
			return true;

		return false;
	}

	void DX9Renderer::SetPipeline(const PipelineStateDesc& state, bool force)
	{
		const PipelineStateDesc& newDesc = state;
		const PipelineStateDesc& oldDesc = _state;

		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::zbuffer, force))
			_d3ddev->SetRenderState(D3DRS_ZENABLE, Convert(oldDesc.zbuffer));
		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::zwriteEnable, force))
			_d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, oldDesc.zwriteEnable);
		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::zfunc, force))
			_d3ddev->SetRenderState(D3DRS_ZFUNC, Convert(oldDesc.zfunc));

		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::alphaBlend, force))
			_d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, oldDesc.alphaBlend);
		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::alphaTest, force))
			_d3ddev->SetRenderState(D3DRS_ALPHATESTENABLE, oldDesc.alphaTest);
		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::alphaRef, force))
			_d3ddev->SetRenderState(D3DRS_ALPHAREF, oldDesc.alphaRef);
		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::alphaFunc, force))
			_d3ddev->SetRenderState(D3DRS_ALPHAFUNC, Convert(oldDesc.alphaFunc));

		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::blendOp, force))
			_d3ddev->SetRenderState(D3DRS_BLENDOP, Convert(oldDesc.blendOp));
		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::srcBlend, force))
			_d3ddev->SetRenderState(D3DRS_SRCBLEND, Convert(oldDesc.srcBlend));
		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::destBlend, force))
			_d3ddev->SetRenderState(D3DRS_DESTBLEND, Convert(oldDesc.destBlend));
		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::blendOpAlpha, force))
			_d3ddev->SetRenderState(D3DRS_BLENDOPALPHA, Convert(oldDesc.blendOpAlpha));
		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::srcBlendAlpha, force))
			_d3ddev->SetRenderState(D3DRS_SRCBLENDALPHA, Convert(oldDesc.srcBlendAlpha));
		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::destBlendAlpha, force))
			_d3ddev->SetRenderState(D3DRS_DESTBLENDALPHA, Convert(oldDesc.destBlendAlpha));

		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::lightning, force))
			_d3ddev->SetRenderState(D3DRS_LIGHTING, oldDesc.lightning);
		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::ambientColor, force))
			_d3ddev->SetRenderState(D3DRS_AMBIENT, oldDesc.ambientColor.ToInt());

		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::fogEnabled, force))
			_d3ddev->SetRenderState(D3DRS_FOGENABLE, oldDesc.fogEnabled);
		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::fogColor, force))
			_d3ddev->SetRenderState(D3DRS_FOGCOLOR, oldDesc.fogColor.ToInt());
		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::fogMode, force))
			_d3ddev->SetRenderState(D3DRS_FOGTABLEMODE, Convert(oldDesc.fogMode));
		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::fogDensity, force))
			_d3ddev->SetRenderState(D3DRS_FOGDENSITY, *((DWORD*)(&oldDesc.fogDensity)));
		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::fogStart, force))
			_d3ddev->SetRenderState(D3DRS_FOGSTART, *((DWORD*)(&oldDesc.fogStart)));
		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::fogEnd, force))
			_d3ddev->SetRenderState(D3DRS_FOGEND, *((DWORD*)(&oldDesc.fogEnd)));
		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::fogRangeEnabled, force))
			_d3ddev->SetRenderState(D3DRS_RANGEFOGENABLE, oldDesc.fogRangeEnabled);

		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::fillMode, force))
			_d3ddev->SetRenderState(D3DRS_FILLMODE, Convert(oldDesc.fillMode));
		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::shadeMode, force))
			_d3ddev->SetRenderState(D3DRS_SHADEMODE, Convert(oldDesc.shadeMode));
		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::cullMode, force))
			_d3ddev->SetRenderState(D3DRS_CULLMODE, Convert(oldDesc.cullMode));
		if (CheckState(oldDesc, newDesc, &PipelineStateDesc::scissorTest, force))
			_d3ddev->SetRenderState(D3DRS_SCISSORTESTENABLE, oldDesc.scissorTest);

		for (int i = 0; i < PipelineStateDesc::TEXTURE_STAGE_COUNT; i++)
		{
			if (CheckState(oldDesc.textureStage[i], newDesc.textureStage[i], &RenderTextureStageState::colorOp, force))
				_d3ddev->SetTextureStageState(i, D3DTSS_COLOROP, Convert(oldDesc.textureStage[i].colorOp));

			if (CheckState(oldDesc.textureStage[i], newDesc.textureStage[i], &RenderTextureStageState::colorArg1, force))
				_d3ddev->SetTextureStageState(i, D3DTSS_COLORARG1, Convert(oldDesc.textureStage[i].colorArg1));

			if (CheckState(oldDesc.textureStage[i], newDesc.textureStage[i], &RenderTextureStageState::colorArg2, force))
				_d3ddev->SetTextureStageState(i, D3DTSS_COLORARG2, Convert(oldDesc.textureStage[i].colorArg2));

			if (CheckState(oldDesc.textureStage[i], newDesc.textureStage[i], &RenderTextureStageState::alphaOp, force))
				_d3ddev->SetTextureStageState(i, D3DTSS_ALPHAOP, Convert(oldDesc.textureStage[i].alphaOp));

			if (CheckState(oldDesc.textureStage[i], newDesc.textureStage[i], &RenderTextureStageState::alphaArg1, force))
				_d3ddev->SetTextureStageState(i, D3DTSS_ALPHAARG1, Convert(oldDesc.textureStage[i].alphaArg1));

			if (CheckState(oldDesc.textureStage[i], newDesc.textureStage[i], &RenderTextureStageState::alphaArg2, force))
				_d3ddev->SetTextureStageState(i, D3DTSS_ALPHAARG2, Convert(oldDesc.textureStage[i].alphaArg2));
		}

		for (int i = 0; i < PipelineStateDesc::SAMPLER_COUNT; i++)
		{
			if (CheckState(oldDesc.sampler[i], newDesc.sampler[i], &RenderSamplerState::addressu, force))
				_d3ddev->SetSamplerState(i, D3DSAMP_ADDRESSU, Convert(oldDesc.sampler[i].addressu));

			if (CheckState(oldDesc.sampler[i], newDesc.sampler[i], &RenderSamplerState::addressv, force))
				_d3ddev->SetSamplerState(i, D3DSAMP_ADDRESSV, Convert(oldDesc.sampler[i].addressv));

			if (CheckState(oldDesc.sampler[i], newDesc.sampler[i], &RenderSamplerState::addressw, force))
				_d3ddev->SetSamplerState(i, D3DSAMP_ADDRESSW, Convert(oldDesc.sampler[i].addressw));

			if (CheckState(oldDesc.sampler[i], newDesc.sampler[i], &RenderSamplerState::borderColor, force))
				_d3ddev->SetSamplerState(i, D3DSAMP_BORDERCOLOR, oldDesc.sampler[i].borderColor.ToInt());

			if (CheckState(oldDesc.sampler[i], newDesc.sampler[i], &RenderSamplerState::minFilter, force))
				_d3ddev->SetSamplerState(i, D3DSAMP_MINFILTER, Convert(oldDesc.sampler[i].minFilter));

			if (CheckState(oldDesc.sampler[i], newDesc.sampler[i], &RenderSamplerState::magFilter, force))
				_d3ddev->SetSamplerState(i, D3DSAMP_MAGFILTER, Convert(oldDesc.sampler[i].magFilter));

			if (CheckState(oldDesc.sampler[i], newDesc.sampler[i], &RenderSamplerState::mipFilter, force))
				_d3ddev->SetSamplerState(i, D3DSAMP_MIPFILTER, Convert(oldDesc.sampler[i].mipFilter));
		}

		_state = state;
	}

	const RendererStatistics& DX9Renderer::GetStatistics() const
	{
		return _statistics;
	}

// 	void DX9Renderer::SetViewport(const Viewport& viewport)
// 	{
// 		_viewport = viewport;
// 		D3DVIEWPORT9 vp
// 		{
// 			_viewport.x, _viewport.y,
// 			_viewport.width, _viewport.height,
// 			_viewport.minZ, _viewport.maxZ 
// 		};
// 		_d3ddev->SetViewport(&vp);
// 	}

	bool DX9Renderer::SetTransform(RenderTransform type, const Matrix4& mat)
	{
		HRESULT ret = _d3ddev->SetTransform(Convert(type), (D3DMATRIX*)&mat);
		switch (type)
		{
		case RT_VIEW: _matView = mat; break;
		case RT_WORLD: _matWorld = mat; break;
		case RT_PROJECTION: _matProj = mat; break;
		}
		return TestReturnCode(ret);
	}

	const Matrix4& DX9Renderer::GetTransform(RenderTransform type) const
	{
		switch (type)
		{
		case RT_VIEW: return _matView;
		case RT_WORLD: return _matWorld;
		case RT_PROJECTION: return _matProj;
		}

		return Matrix4::Identity;
	}

	bool DX9Renderer::BeginScene()
	{
		HRESULT ret = _d3ddev->BeginScene();

		SetPipeline(_state, true);

		_matWorld = Matrix4::Identity;
		_matView = Matrix4::Identity;
		_matProj = Matrix4::Perspective(
			static_cast<float>(_screenSize.x),
			static_cast<float>(_screenSize.y),
			0.001f, 1000.0f);
		_d3ddev->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&_matWorld);
		_d3ddev->SetTransform(D3DTS_VIEW, (D3DMATRIX*)&_matView);
		_d3ddev->SetTransform(D3DTS_PROJECTION, (D3DMATRIX*)&_matProj);

		return TestReturnCode(ret);
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

	SharedPtr<Texture2D> DX9Renderer::CreateTexture(const IntVector2& size, TextureAccess access)
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

		renderer->SetPipeline(renderer->_state, true);
		return renderer;
	}

	void DX9Renderer::Execute(const SharedPtr<CommandList>& commandList)
	{
		if (!commandList  || commandList->GetType() != DX9CommandList::GetTypeStatic())
			return;

		auto dx9cmdList = DynamicCast<DX9CommandList>(commandList);
		auto state = dx9cmdList->_state;
		SetPipeline(state->GetDesc(), false);

		HRESULT ret = _d3ddev->SetVertexDeclaration(state->_vd);
		TestReturnCode(ret);

		auto& rect = dx9cmdList->_scissorRect;
		const RECT r{ rect.GetLeft(),rect.GetTop(),rect.GetRight(),rect.GetBottom() };
		_d3ddev->SetScissorRect(&r);

		auto& viewport = dx9cmdList->_viewport;
		D3DVIEWPORT9 vp
		{
			viewport.x, viewport.y,
			viewport.width, viewport.height,
			viewport.minZ, viewport.maxZ
		};
		_d3ddev->SetViewport(&vp);

		for (auto& command : dx9cmdList->_commands)
		{
			HRESULT result = command->Execute(_d3ddev);
			TestReturnCode(result);
		}
	}

	SharedPtr<CommandList> DX9Renderer::CreateCommandList()
	{
		auto list = SharedPtr<DX9CommandList>::Make();

		D3DVIEWPORT9 vp;
		_d3ddev->GetViewport(&vp);
		list->_viewport.x = vp.X;
		list->_viewport.y = vp.Y;
		list->_viewport.width = vp.Width;
		list->_viewport.height = vp.Height;
		list->_viewport.minZ = vp.MinZ;
		list->_viewport.maxZ = vp.MaxZ;

		return list;
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

	D3DTRANSFORMSTATETYPE DX9Renderer::Convert(RenderTransform type)
	{
		switch (type)
		{
		case RenderTransform::RT_VIEW: return D3DTS_VIEW;
		case RenderTransform::RT_PROJECTION: return D3DTS_PROJECTION;
		case RenderTransform::RT_WORLD: return D3DTS_WORLD;
		}

		return D3DTS_FORCE_DWORD;
	}

	D3DPRIMITIVETYPE DX9Renderer::Convert(Topology topology)
	{
		switch (topology)
		{
		case Topology::PointList: return D3DPT_POINTLIST;
		case Topology::LineList: return D3DPT_LINELIST;
		case Topology::LineStrip: return D3DPT_LINESTRIP;
		case Topology::TriangleList: return D3DPT_TRIANGLELIST;
		case Topology::TriangleStrip: return D3DPT_TRIANGLESTRIP;
		case Topology::TriangleFan: return D3DPT_TRIANGLEFAN;
		}

		return D3DPT_POINTLIST;
	}

	D3DDECLTYPE DX9Renderer::Convert(VertexElement::DeclareType type)
	{
		switch (type)
		{
		case VertexElement::DT_FLOAT1: return D3DDECLTYPE_FLOAT1;
		case VertexElement::DT_FLOAT2: return D3DDECLTYPE_FLOAT2;
		case VertexElement::DT_FLOAT3: return D3DDECLTYPE_FLOAT3;
		case VertexElement::DT_FLOAT4: return D3DDECLTYPE_FLOAT4;
		case VertexElement::DT_DWORD: return D3DDECLTYPE_D3DCOLOR;
		case VertexElement::DT_UBYTE4: return D3DDECLTYPE_UBYTE4;
		}

		return D3DDECLTYPE_UNUSED;
	}

	D3DDECLUSAGE DX9Renderer::Convert(VertexElement::UsageType usage)
	{
		switch (usage)
		{
		case VertexElement::UT_POSITION: return D3DDECLUSAGE_POSITION;
		case VertexElement::UT_NORMAL: return D3DDECLUSAGE_NORMAL;
		case VertexElement::UT_TEXCOORD: return D3DDECLUSAGE_TEXCOORD;
		case VertexElement::UT_COLOR: return D3DDECLUSAGE_COLOR;
		}

		return D3DDECLUSAGE_POSITION;
	}

	D3DZBUFFERTYPE DX9Renderer::Convert(ZBufferMode type)
	{
		switch (type)
		{
		case ZBufferMode::Disable: return D3DZB_FALSE;
		case ZBufferMode::ZBuffer: return D3DZB_TRUE;
		case ZBufferMode::WBuffer: return D3DZB_USEW;
		}

		return D3DZB_FALSE;
	}

	D3DFILLMODE DX9Renderer::Convert(FillMode mode)
	{
		switch (mode)
		{
		case FillMode::Point: return D3DFILL_POINT;
		case FillMode::Wireframe: return D3DFILL_WIREFRAME;
		case FillMode::Solid: return D3DFILL_SOLID;
		}

		return D3DFILL_SOLID;
	}

	D3DSHADEMODE DX9Renderer::Convert(ShadeMode mode)
	{
		switch (mode)
		{
		case ShadeMode::Flat: return D3DSHADE_FLAT;
		case ShadeMode::Gourand: return D3DSHADE_GOURAUD;
		case ShadeMode::Phong: return D3DSHADE_PHONG;
		}

		return D3DSHADE_GOURAUD;
	}

	D3DCULL DX9Renderer::Convert(CullMode mode)
	{
		switch (mode)
		{
		case CullMode::Clockwise: return D3DCULL_CW;
		case CullMode::ConterClockwise: return D3DCULL_CCW;
		}

		return D3DCULL_NONE;
	}

	D3DCMPFUNC DX9Renderer::Convert(CompareFunc func)
	{
		switch (func)
		{
		case CompareFunc::Never: return D3DCMP_NEVER;
		case CompareFunc::Less: return D3DCMP_LESS;
		case CompareFunc::Equal: return D3DCMP_EQUAL;
		case CompareFunc::LessEqual: return D3DCMP_LESSEQUAL;
		case CompareFunc::Greater: return D3DCMP_GREATER;
		case CompareFunc::NotEqual: return D3DCMP_NOTEQUAL;
		case CompareFunc::GreaterEqual: return D3DCMP_GREATEREQUAL;
		case CompareFunc::Always: return D3DCMP_ALWAYS;
		}

		return D3DCMP_LESSEQUAL;
	}

	D3DFOGMODE DX9Renderer::Convert(FogMode mode)
	{
		switch (mode)
		{
		case FogMode::None: return D3DFOG_NONE;
		case FogMode::Exp: return D3DFOG_EXP;
		case FogMode::Exp2: return D3DFOG_EXP2;
		case FogMode::Linear: return D3DFOG_LINEAR;
		}

		return D3DFOG_NONE;
	}

	D3DTEXTUREOP DX9Renderer::Convert(TextureOperation op)
	{
		switch (op)
		{
		case TextureOperation::Disable: return D3DTOP_DISABLE;
		case TextureOperation::SelectArg1: return D3DTOP_SELECTARG1;
		case TextureOperation::SelectArg2: return D3DTOP_SELECTARG2;
		case TextureOperation::Modulate: return D3DTOP_MODULATE;
		case TextureOperation::Modulate2x: return D3DTOP_MODULATE2X;
		case TextureOperation::Modulate4x: return D3DTOP_MODULATE4X;
		case TextureOperation::Add: return D3DTOP_ADD;
		case TextureOperation::AddSigned: return D3DTOP_ADDSIGNED;
		case TextureOperation::AddSigned2x: return D3DTOP_ADDSIGNED2X;
		case TextureOperation::Substract: return D3DTOP_SUBTRACT;
		case TextureOperation::AddSmooth: return D3DTOP_ADDSMOOTH;
		case TextureOperation::BlendDiffuseAlpha: return D3DTOP_BLENDDIFFUSEALPHA;
		case TextureOperation::BlendTextureAlpha: return D3DTOP_BLENDTEXTUREALPHA;
		case TextureOperation::BlendFactorAlpha: return D3DTOP_BLENDFACTORALPHA;
		case TextureOperation::BlendTextureAlphaPM: return D3DTOP_BLENDTEXTUREALPHAPM;
		case TextureOperation::BlendCurrentAlpha: return D3DTOP_BLENDCURRENTALPHA;
		case TextureOperation::PreModulate: return D3DTOP_PREMODULATE;
		case TextureOperation::ModulateAlphaAddColor: return D3DTOP_MODULATEALPHA_ADDCOLOR;
		case TextureOperation::ModulateColorAddAlpha: return D3DTOP_MODULATECOLOR_ADDALPHA;
		case TextureOperation::BumpEnvMap: return D3DTOP_BUMPENVMAP;
		case TextureOperation::BumpEnvMapLuminance: return D3DTOP_BUMPENVMAPLUMINANCE;
		case TextureOperation::DotProduct3: return D3DTOP_DOTPRODUCT3;
		case TextureOperation::MultiplyAdd: return D3DTOP_MULTIPLYADD;
		case TextureOperation::Lerp: return D3DTOP_LERP;
		}

		return D3DTOP_ADD;
	}

	DWORD DX9Renderer::Convert(TextureArgument arg)
	{
		switch (arg)
		{
		case TextureArgument::Constant: return D3DTA_CONSTANT;
		case TextureArgument::Current: return D3DTA_CURRENT;
		case TextureArgument::Diffuse: return D3DTA_DIFFUSE;
		case TextureArgument::SelectMask: return D3DTA_SELECTMASK;
		case TextureArgument::Specular: return D3DTA_SPECULAR;
		case TextureArgument::Temp: return D3DTA_TEMP;
		case TextureArgument::Texture: return D3DTA_TEXTURE;
		case TextureArgument::TextureFactor: return D3DTA_TFACTOR;
		}

		return D3DTA_TEXTURE;
	}

	D3DTEXTUREFILTERTYPE DX9Renderer::Convert(TextureFilter filter)
	{
		switch (filter)
		{
		case TextureFilter::NoFilter: return D3DTEXF_NONE;
		case TextureFilter::Point: return D3DTEXF_POINT;
		case TextureFilter::Linear: return D3DTEXF_LINEAR;
		case TextureFilter::Anisotropic: return D3DTEXF_ANISOTROPIC;
		case TextureFilter::PyramidalQuad: return D3DTEXF_PYRAMIDALQUAD;
		case TextureFilter::GaussianQuad: return D3DTEXF_GAUSSIANQUAD;
		}

		return D3DTEXF_LINEAR;
	}

	D3DTEXTUREADDRESS DX9Renderer::Convert(TextureAddress address)
	{
		switch (address)
		{
		case TextureAddress::Wrap: return D3DTADDRESS_WRAP;
		case TextureAddress::Mirror: return D3DTADDRESS_MIRROR;
		case TextureAddress::Clamp: return D3DTADDRESS_CLAMP;
		case TextureAddress::Border: return D3DTADDRESS_BORDER;
		case TextureAddress::MirrorOnce: return D3DTADDRESS_MIRRORONCE;
		}

		return D3DTADDRESS_WRAP;
	}

	D3DBLENDOP DX9Renderer::Convert(BlendOperation op)
	{
		switch (op)
		{
		case BlendOperation::Add: return D3DBLENDOP_ADD;
		case BlendOperation::Sub: return D3DBLENDOP_SUBTRACT;
		case BlendOperation::RevSub: return D3DBLENDOP_REVSUBTRACT;
		case BlendOperation::Min: return D3DBLENDOP_MIN;
		case BlendOperation::Max: return D3DBLENDOP_MAX;
		}

		return D3DBLENDOP_ADD;
	}

	D3DBLEND DX9Renderer::Convert(BlendFactor blend)
	{
		switch (blend)
		{
		case BlendFactor::Zero: return D3DBLEND_ZERO;
		case BlendFactor::One: return D3DBLEND_ONE;
		case BlendFactor::SrcColor: return D3DBLEND_SRCCOLOR;
		case BlendFactor::InvSrcColor: return D3DBLEND_INVSRCCOLOR;
		case BlendFactor::SrcAlpha: return D3DBLEND_SRCALPHA;
		case BlendFactor::InvSrcAlpha: return D3DBLEND_INVSRCALPHA;
		case BlendFactor::DestColor: return D3DBLEND_DESTCOLOR;
		case BlendFactor::InvDestColor: return D3DBLEND_INVDESTCOLOR;
		case BlendFactor::DestAlpha: return D3DBLEND_DESTALPHA;
		case BlendFactor::InvDestAlpha: return D3DBLEND_INVDESTALPHA;
		case BlendFactor::SrcAlphaSat: return D3DBLEND_SRCALPHASAT;
		case BlendFactor::BothSrcAlpha: return D3DBLEND_BOTHSRCALPHA;
		case BlendFactor::InvBothSrcAlpha: return D3DBLEND_BOTHINVSRCALPHA;
		case BlendFactor::Factor: return D3DBLEND_BLENDFACTOR;
		case BlendFactor::InvFactor: return D3DBLEND_INVBLENDFACTOR;
		}

		return D3DBLEND_ZERO;
	}
}