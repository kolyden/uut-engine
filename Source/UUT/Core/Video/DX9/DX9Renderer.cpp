#include "DX9Renderer.h"
#include "Core/Windows/Window.h"
#include "DX9Texture2D.h"
#include "DX9VertexBuffer.h"
#include "DX9IndexBuffer.h"
#include "DX9VertexDeclaration.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_syswm.h"
#include <Core/Debug.h>

#include <d3dx9.h>
#include <DxErr.h>
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxerr.lib")

namespace uut
{
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

	void DX9Renderer::ResetStates()
	{
		SetState(_state, true);

		_matWorld = Matrix4::Identity;
		_matView = Matrix4::Identity;
		_matProj = Matrix4::Perspective(
			static_cast<float>(_screenSize.x),
			static_cast<float>(_screenSize.y),
			0.001f, 1000.0f);
		_d3ddev->SetTransform(D3DTS_WORLD, (D3DMATRIX*)&_matWorld);
		_d3ddev->SetTransform(D3DTS_VIEW, (D3DMATRIX*)&_matView);
		_d3ddev->SetTransform(D3DTS_PROJECTION, (D3DMATRIX*)&_matProj);
	}

	template<typename T>
	static bool CheckState(RenderState& state, const RenderState& check, T (RenderState::*var), bool force)
	{
		if (force || (state.*var) != (check.*var))
		{
			(state.*var) = (check.*var);
			return true;
		}

		return false;
	}

	template<typename T>
	static bool CheckState(RenderTextureStageState& state, const RenderTextureStageState& check, T(RenderTextureStageState::*var), bool force)
	{
		if (force || (state.*var) != (check.*var))
		{
			(state.*var) = (check.*var);
			return true;
		}

		return false;
	}

	template<typename T>
	static bool CheckState(RenderSamplerState& state, const RenderSamplerState& check, T(RenderSamplerState::*var), bool force)
	{
		if (force || (state.*var) != (check.*var))
		{
			(state.*var) = (check.*var);
			return true;
		}

		return false;
	}

	void DX9Renderer::SetState(const RenderState& state, bool force)
	{
		if (CheckState(_state, state, &RenderState::zbuffer, force))
			_d3ddev->SetRenderState(D3DRS_ZENABLE, Convert(_state.zbuffer));
		if (CheckState(_state, state, &RenderState::zwriteEnable, force))
			_d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, _state.zwriteEnable);
		if (CheckState(_state, state, &RenderState::zfunc, force))
			_d3ddev->SetRenderState(D3DRS_ZFUNC, Convert(_state.zfunc));

		if (CheckState(_state, state, &RenderState::alphaBlend, force))
			_d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, _state.alphaBlend);
		if (CheckState(_state, state, &RenderState::alphaTest, force))
			_d3ddev->SetRenderState(D3DRS_ALPHATESTENABLE, _state.alphaTest);
		if (CheckState(_state, state, &RenderState::alphaRef, force))
			_d3ddev->SetRenderState(D3DRS_ALPHAREF, _state.alphaRef);
		if (CheckState(_state, state, &RenderState::alphaFunc, force))
			_d3ddev->SetRenderState(D3DRS_ALPHAFUNC, Convert(_state.alphaFunc));

		if (CheckState(_state, state, &RenderState::blendOp, force))
			_d3ddev->SetRenderState(D3DRS_BLENDOP, Convert(_state.blendOp));
		if (CheckState(_state, state, &RenderState::srcBlend, force))
			_d3ddev->SetRenderState(D3DRS_SRCBLEND, Convert(_state.srcBlend));
		if (CheckState(_state, state, &RenderState::destBlend, force))
			_d3ddev->SetRenderState(D3DRS_DESTBLEND, Convert(_state.destBlend));
		if (CheckState(_state, state, &RenderState::blendOpAlpha, force))
			_d3ddev->SetRenderState(D3DRS_BLENDOPALPHA, Convert(_state.blendOpAlpha));
		if (CheckState(_state, state, &RenderState::srcBlendAlpha, force))
			_d3ddev->SetRenderState(D3DRS_SRCBLENDALPHA, Convert(_state.srcBlendAlpha));
		if (CheckState(_state, state, &RenderState::destBlendAlpha, force))
			_d3ddev->SetRenderState(D3DRS_DESTBLENDALPHA, Convert(_state.destBlendAlpha));

		if (CheckState(_state, state, &RenderState::lightning, force))
			_d3ddev->SetRenderState(D3DRS_LIGHTING, _state.lightning);
		if (CheckState(_state, state, &RenderState::ambientColor, force))
			_d3ddev->SetRenderState(D3DRS_AMBIENT, _state.ambientColor.ToInt());

		if (CheckState(_state, state, &RenderState::fogEnabled, force))
			_d3ddev->SetRenderState(D3DRS_FOGENABLE, _state.fogEnabled);
		if (CheckState(_state, state, &RenderState::fogColor, force))
			_d3ddev->SetRenderState(D3DRS_FOGCOLOR, _state.fogColor.ToInt());
		if (CheckState(_state, state, &RenderState::fogMode, force))
			_d3ddev->SetRenderState(D3DRS_FOGTABLEMODE, Convert(_state.fogMode));
		if (CheckState(_state, state, &RenderState::fogDensity, force))
			_d3ddev->SetRenderState(D3DRS_FOGDENSITY, *((DWORD*)(&_state.fogDensity)));
		if (CheckState(_state, state, &RenderState::fogStart, force))
			_d3ddev->SetRenderState(D3DRS_FOGSTART, *((DWORD*)(&_state.fogStart)));
		if (CheckState(_state, state, &RenderState::fogEnd, force))
			_d3ddev->SetRenderState(D3DRS_FOGEND, *((DWORD*)(&_state.fogEnd)));
		if (CheckState(_state, state, &RenderState::fogRangeEnabled, force))
			_d3ddev->SetRenderState(D3DRS_RANGEFOGENABLE, _state.fogRangeEnabled);

		if (CheckState(_state, state, &RenderState::fillMode, force))
			_d3ddev->SetRenderState(D3DRS_FILLMODE, Convert(_state.fillMode));
		if (CheckState(_state, state, &RenderState::shadeMode, force))
			_d3ddev->SetRenderState(D3DRS_SHADEMODE, Convert(_state.shadeMode));
		if (CheckState(_state, state, &RenderState::cullMode, force))
			_d3ddev->SetRenderState(D3DRS_CULLMODE, Convert(_state.cullMode));
		if (CheckState(_state, state, &RenderState::scissorTest, force))
			_d3ddev->SetRenderState(D3DRS_SCISSORTESTENABLE, _state.scissorTest);

		for (int i = 0; i < RenderState::TEXTURE_STAGE_COUNT; i++)
		{
			if (CheckState(_state.textureStage[i], state.textureStage[i], &RenderTextureStageState::colorOp, force))
				_d3ddev->SetTextureStageState(i, D3DTSS_COLOROP, Convert(_state.textureStage[i].colorOp));

			if (CheckState(_state.textureStage[i], state.textureStage[i], &RenderTextureStageState::colorArg1, force))
				_d3ddev->SetTextureStageState(i, D3DTSS_COLORARG1, Convert(_state.textureStage[i].colorArg1));

			if (CheckState(_state.textureStage[i], state.textureStage[i], &RenderTextureStageState::colorArg2, force))
				_d3ddev->SetTextureStageState(i, D3DTSS_COLORARG2, Convert(_state.textureStage[i].colorArg2));

			if (CheckState(_state.textureStage[i], state.textureStage[i], &RenderTextureStageState::alphaOp, force))
				_d3ddev->SetTextureStageState(i, D3DTSS_ALPHAOP, Convert(_state.textureStage[i].alphaOp));

			if (CheckState(_state.textureStage[i], state.textureStage[i], &RenderTextureStageState::alphaArg1, force))
				_d3ddev->SetTextureStageState(i, D3DTSS_ALPHAARG1, Convert(_state.textureStage[i].alphaArg1));

			if (CheckState(_state.textureStage[i], state.textureStage[i], &RenderTextureStageState::alphaArg2, force))
				_d3ddev->SetTextureStageState(i, D3DTSS_ALPHAARG2, Convert(_state.textureStage[i].alphaArg2));
		}

		for (int i = 0; i < RenderState::SAMPLER_COUNT; i++)
		{
			if (CheckState(_state.sampler[i], state.sampler[i], &RenderSamplerState::addressu, force))
				_d3ddev->SetSamplerState(i, D3DSAMP_ADDRESSU, Convert(_state.sampler[i].addressu));

			if (CheckState(_state.sampler[i], state.sampler[i], &RenderSamplerState::addressv, force))
				_d3ddev->SetSamplerState(i, D3DSAMP_ADDRESSV, Convert(_state.sampler[i].addressv));

			if (CheckState(_state.sampler[i], state.sampler[i], &RenderSamplerState::addressw, force))
				_d3ddev->SetSamplerState(i, D3DSAMP_ADDRESSW, Convert(_state.sampler[i].addressw));

			if (CheckState(_state.sampler[i], state.sampler[i], &RenderSamplerState::borderColor, force))
				_d3ddev->SetSamplerState(i, D3DSAMP_BORDERCOLOR, _state.sampler[i].borderColor.ToInt());

			if (CheckState(_state.sampler[i], state.sampler[i], &RenderSamplerState::minFilter, force))
				_d3ddev->SetSamplerState(i, D3DSAMP_MINFILTER, Convert(_state.sampler[i].minFilter));

			if (CheckState(_state.sampler[i], state.sampler[i], &RenderSamplerState::magFilter, force))
				_d3ddev->SetSamplerState(i, D3DSAMP_MAGFILTER, Convert(_state.sampler[i].magFilter));

			if (CheckState(_state.sampler[i], state.sampler[i], &RenderSamplerState::mipFilter, force))
				_d3ddev->SetSamplerState(i, D3DSAMP_MIPFILTER, Convert(_state.sampler[i].mipFilter));
		}
	}

	void DX9Renderer::SetScissorRect(const IntRect& rect)
	{
		const RECT r{ rect.GetLeft(),rect.GetTop(),rect.GetRight(),rect.GetBottom() };
		_d3ddev->SetScissorRect(&r);
	}

	const RendererStatistics& DX9Renderer::GetStatistics() const
	{
		return _statistics;
	}

	void DX9Renderer::SetViewport(const Viewport& viewport)
	{
		_viewport = viewport;
		D3DVIEWPORT9 vp
		{
			_viewport.x, _viewport.y,
			_viewport.width, _viewport.height,
			_viewport.minZ, _viewport.maxZ 
		};
		_d3ddev->SetViewport(&vp);
	}

	const Viewport& DX9Renderer::GetViewport() const
	{
		return _viewport;
	}

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
		return TestReturnCode(ret);
	}

	void DX9Renderer::EndScene()
	{
		_d3ddev->EndScene();
	}

	bool DX9Renderer::SetTexture(int stage, Texture2D* texture)
	{
		HRESULT ret;
		if (texture == nullptr)
			ret = _d3ddev->SetTexture(stage, nullptr);
		else
		{
			auto data = texture ? reinterpret_cast<LPDIRECT3DTEXTURE9>(texture->GetNativeHandle()) : nullptr;
			ret = _d3ddev->SetTexture(stage, data);
		}
	
		return TestReturnCode(ret);
	}

	bool DX9Renderer::SetVertexBuffer(VertexBuffer* buffer, uint16_t stride, uint32_t offset)
	{
		auto data = buffer ? reinterpret_cast<LPDIRECT3DVERTEXBUFFER9>(buffer->GetInternalHandle()) : nullptr;
		HRESULT ret = _d3ddev->SetStreamSource(0, data, offset, stride);
		return TestReturnCode(ret);
	}

	bool DX9Renderer::SetIndexBuffer(IndexBuffer* buffer)
	{
		auto data = buffer ? reinterpret_cast<LPDIRECT3DINDEXBUFFER9>(buffer->GetInternalHandle()) : nullptr;
		HRESULT ret = _d3ddev->SetIndices(data);
		return TestReturnCode(ret);
	}

	bool DX9Renderer::SetVertexDeclaration(VertexDeclaration* declare)
	{
		HRESULT ret;
		if (declare == nullptr)
			ret = _d3ddev->SetVertexDeclaration(nullptr);
		else
		{
			auto data = reinterpret_cast<LPDIRECT3DVERTEXDECLARATION9>(declare->GetInternalHandle());
			ret = _d3ddev->SetVertexDeclaration(data);
		}

		return TestReturnCode(ret);
	}

	bool DX9Renderer::DrawPrimitive(Topology topology, uint32_t primitiveCount, uint32_t offset)
	{
		_statistics.drawCall++;
		_statistics.verticesCount += 0;

		HRESULT ret = _d3ddev->DrawPrimitive(Convert(topology), offset, primitiveCount);
		return TestReturnCode(ret);
	}

	bool DX9Renderer::DrawIndexedPrimitive(Topology topology, int BaseVertexIndex, uint32_t MinVertexIndex, uint32_t NumVertices, uint32_t startIndex, uint32_t primitiveCount)
	{
		_statistics.drawCall++;
		_statistics.verticesCount += 0;

		HRESULT ret = _d3ddev->DrawIndexedPrimitive(Convert(topology),
			BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primitiveCount);
		return TestReturnCode(ret);
	}

	bool DX9Renderer::Clear(const Color32& color, float z, uint32_t stencil)
	{
		_statistics.drawCall = 0;
		_statistics.verticesCount = 0;

		bool change = false;
		if (_state.scissorTest)
		{
			change = true;
			_d3ddev->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
		}

		HRESULT ret = _d3ddev->Clear(0, nullptr,
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color.ToInt(), z, stencil);

		if (change)
			_d3ddev->SetRenderState(D3DRS_SCISSORTESTENABLE, TRUE);
		return TestReturnCode(ret);
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
			return SharedPtr<Texture2D>::EMPTY;

		SharedPtr<DX9Texture2D> tex(new DX9Texture2D());
		tex->_data = data;
		tex->_size = size;

		return DynamicCast<Texture2D>(tex);
	}

	SharedPtr<VertexBuffer> DX9Renderer::CreateVertexBuffer(uint32_t size)
	{
		if (size == 0)
			return SharedPtr<VertexBuffer>::EMPTY;

		LPDIRECT3DVERTEXBUFFER9 data;
		HRESULT ret = _d3ddev->CreateVertexBuffer(size,
			D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &data, nullptr);
		if (!TestReturnCode(ret))
			return SharedPtr<VertexBuffer>::EMPTY;

		SharedPtr<DX9VertexBuffer> vb(new DX9VertexBuffer());
		vb->_data = data;
		vb->_size = size;

		return DynamicCast<VertexBuffer>(vb);
	}

	SharedPtr<IndexBuffer> DX9Renderer::CreateIndexBuffer(uint32_t size, bool use32)
	{
		if (size == 0)
			return SharedPtr<IndexBuffer>::EMPTY;

		LPDIRECT3DINDEXBUFFER9 data;
		D3DFORMAT format = use32 ? D3DFMT_INDEX32 : D3DFMT_INDEX16;
		HRESULT ret = _d3ddev->CreateIndexBuffer(size,
			D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, format, D3DPOOL_DEFAULT, &data, nullptr);
		if (!TestReturnCode(ret))
			return SharedPtr<IndexBuffer>::EMPTY;

		SharedPtr<DX9IndexBuffer> vb(new DX9IndexBuffer());
		vb->_data = data;
		vb->_size = size;

		return DynamicCast<IndexBuffer>(vb);
	}

	SharedPtr<VertexDeclaration> DX9Renderer::CreateVertexDeclaration(const List<VertexElement>& elements)
	{
		const int count = elements.Count();
		if (count == 0)
			return SharedPtr<VertexDeclaration>::EMPTY;

		auto declare = new D3DVERTEXELEMENT9[count + 1];
		for (int i = 0; i < count;i++)
		{
			auto it = elements[i];
			declare[i].Stream = it.stream;
			declare[i].Offset = it.offset;
			declare[i].Type = static_cast<BYTE>(Convert(it.type));
			declare[i].Method = D3DDECLMETHOD_DEFAULT;
			declare[i].Usage = static_cast<BYTE>(Convert(it.usage));
			declare[i].UsageIndex = it.usageIndex;
		}
		declare[count] = D3DDECL_END();// { 0xFF, 0, D3DDECLTYPE_UNUSED, 0, 0, 0 };
		LPDIRECT3DVERTEXDECLARATION9 data;
		HRESULT ret = _d3ddev->CreateVertexDeclaration(declare, &data);
		delete[] declare;
		if (!TestReturnCode(ret))
			return SharedPtr<VertexDeclaration>::EMPTY;

		SharedPtr<DX9VertexDeclaration> vd(new DX9VertexDeclaration());
		vd->_elements = elements;
		vd->_data = data;
		return DynamicCast<VertexDeclaration>(vd);
	}

	///////////////////////////////////////////////////////////////////////////
	SharedPtr<DX9Renderer> DX9Renderer::Create(Window* window)
	{
		if (window == nullptr || !window->IsCreated())
			return SharedPtr<DX9Renderer>::EMPTY;
		
		SDL_SysWMinfo sdlInfo;
		SDL_VERSION(&sdlInfo.version);
		auto sdlWindow = reinterpret_cast<SDL_Window*>(window->GetInternalHandle());
		if (!SDL_GetWindowWMInfo(sdlWindow, &sdlInfo))
		{
			Debug::LogError("Couldn't get window information: %s", SDL_GetError());
			return SharedPtr<DX9Renderer>::EMPTY;
		}

		LPDIRECT3D9 d3d = Direct3DCreate9(D3D_SDK_VERSION);
		if (d3d == nullptr)
			return SharedPtr<DX9Renderer>::EMPTY;

		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		SharedPtr<DX9Renderer> renderer(new DX9Renderer());
		
		renderer->_window = window;
		renderer->_d3d = d3d;
		renderer->_screenSize = window->GetSize();
		HRESULT ret = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
			sdlInfo.info.win.window, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &renderer->_d3ddev);
		if (!TestReturnCode(ret))
		{
			d3d->Release();
			Debug::LogError("Can't create D3D9 Device");
			return SharedPtr<DX9Renderer>::EMPTY;
		}

		D3DVIEWPORT9 vp;
		renderer->_d3ddev->GetViewport(&vp);
		renderer->_viewport.x = vp.X;
		renderer->_viewport.y = vp.Y;
		renderer->_viewport.width = vp.Width;
		renderer->_viewport.height = vp.Height;
		renderer->_viewport.minZ = vp.MinZ;
		renderer->_viewport.maxZ = vp.MaxZ;

		return renderer;
	}

	///////////////////////////////////////////////////////////////////////////
	bool DX9Renderer::TestReturnCode(HRESULT ret)
	{
		if (ret != D3D_OK)
		{
			Debug::LogError("D3D9: %s - %s",
				DXGetErrorStringA(ret),
				DXGetErrorDescriptionA(ret));
			return false;
		}

		return true;
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
		case Topology::TrinagleList: return D3DPT_TRIANGLELIST;
		case Topology::TrinagleStrip: return D3DPT_TRIANGLESTRIP;
		case Topology::TrinagleFan: return D3DPT_TRIANGLEFAN;
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

	D3DBLENDOP DX9Renderer::Convert(RenderState::BlendOp op)
	{
		switch (op)
		{
		case RenderState::BLENDOP_ADD: return D3DBLENDOP_ADD;
		case RenderState::BLENDOP_SUB: return D3DBLENDOP_SUBTRACT;
		case RenderState::BLENDOP_REVSUB: return D3DBLENDOP_REVSUBTRACT;
		case RenderState::BLENDOP_MIN: return D3DBLENDOP_MIN;
		case RenderState::BLENDOP_MAX: return D3DBLENDOP_MAX;
		}

		return D3DBLENDOP_ADD;
	}

	D3DBLEND DX9Renderer::Convert(RenderState::Blend blend)
	{
		switch (blend)
		{
		case RenderState::BLEND_ZERO: return D3DBLEND_ZERO;
		case RenderState::BLEND_ONE: return D3DBLEND_ONE;
		case RenderState::BLEND_SRCCOLOR: return D3DBLEND_SRCCOLOR;
		case RenderState::BLEND_INVSRCCOLOR: return D3DBLEND_INVSRCCOLOR;
		case RenderState::BLEND_SRCALPHA: return D3DBLEND_SRCALPHA;
		case RenderState::BLEND_INVSRCALPHA: return D3DBLEND_INVSRCALPHA;
		case RenderState::BLEND_DESTCOLOR: return D3DBLEND_DESTCOLOR;
		case RenderState::BLEND_INVDESTCOLOR: return D3DBLEND_INVDESTCOLOR;
		case RenderState::BLEND_DESTALPHA: return D3DBLEND_DESTALPHA;
		case RenderState::BLEND_INVDESTALPHA: return D3DBLEND_INVDESTALPHA;
		case RenderState::BLEND_SRCALPHASAT: return D3DBLEND_SRCALPHASAT;
		case RenderState::BLEND_BOTHSRCALPHA: return D3DBLEND_BOTHSRCALPHA;
		case RenderState::BLEND_INVBOTHSRCALPHA: return D3DBLEND_BOTHINVSRCALPHA;
		case RenderState::BLEND_BLENDFACTOR: return D3DBLEND_BLENDFACTOR;
		case RenderState::BLEND_INVBLENDFACTOR: return D3DBLEND_INVBLENDFACTOR;
		}

		return D3DBLEND_ZERO;
	}
}
