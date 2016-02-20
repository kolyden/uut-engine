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
	{
	}

	DX9Renderer::~DX9Renderer()
	{
		if (_d3ddev) _d3ddev->Release();
		if (_d3d) _d3d->Release();
	}

	void DX9Renderer::ResetStates()
	{
		_d3ddev->SetPixelShader(nullptr);
		_d3ddev->SetVertexShader(nullptr);
		_d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		_d3ddev->SetRenderState(D3DRS_LIGHTING, false);
		_d3ddev->SetRenderState(D3DRS_ZENABLE, false);
		_d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		_d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		_d3ddev->SetRenderState(D3DRS_ALPHATESTENABLE, false);
		_d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		_d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		_d3ddev->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
// 		_d3ddev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
// 		_d3ddev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
		_d3ddev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		_d3ddev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		_d3ddev->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		_d3ddev->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		_d3ddev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
// 		_d3ddev->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
// 		_d3ddev->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
// 		_d3ddev->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

		D3DXMATRIX matWorld;
		D3DXMatrixIdentity(&matWorld);
		_d3ddev->SetTransform(D3DTS_WORLD, &matWorld);

		D3DXMATRIX matView;
		D3DXMatrixIdentity(&matView);
		_d3ddev->SetTransform(D3DTS_VIEW, &matView);

		D3DXMATRIX matProjection;     // the projection transform matrix
		D3DXMatrixIdentity(&matProjection);
// 		D3DXMatrixOrthoOffCenterLH(&matProjection,
// 			0, static_cast<float>(_screenSize.x),
// 			0, static_cast<float>(_screenSize.y),
// 			0.1f, 100.0f);
		_d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);
	}

	void DX9Renderer::SetState(RenderState state, bool enabled)
	{
		switch (state)
		{
		case RenderState::AlphaBlend:
			_d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, enabled);
			break;

		case RenderState::AlphaTest:
			_d3ddev->SetRenderState(D3DRS_ALPHATESTENABLE, enabled);
			break;

		case RenderState::ScissorTest:
			_d3ddev->SetRenderState(D3DRS_SCISSORTESTENABLE, enabled);
			break;

		case RenderState::Lightning:
			_d3ddev->SetRenderState(D3DRS_LIGHTING, enabled);
			break;
		}
	}

	void DX9Renderer::SetScissorRect(const IntRect& rect)
	{
		const RECT r{ rect.GetLeft(),rect.GetTop(),rect.GetRight(),rect.GetBottom() };
		_d3ddev->SetScissorRect(&r);
	}

	bool DX9Renderer::SetTransform(RenderTransform type, const Matrix4& mat)
	{
		HRESULT ret = _d3ddev->SetTransform(Convert(type), (D3DMATRIX*)&mat);
		return TestReturnCode(ret);
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
		HRESULT ret = _d3ddev->DrawPrimitive(Convert(topology), offset, primitiveCount);
		return ret == D3D_OK;
	}

	bool DX9Renderer::DrawIndexedPrimitive(Topology topology, int BaseVertexIndex, uint32_t MinVertexIndex, uint32_t NumVertices, uint32_t startIndex, uint32_t primitiveCount)
	{
		HRESULT ret = _d3ddev->DrawIndexedPrimitive(Convert(topology),
			BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primitiveCount);
		return TestReturnCode(ret);
	}

	bool DX9Renderer::Clear(const Color& color, float z, uint32_t stencil)
	{
		const int flags = D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER;
		HRESULT ret = _d3ddev->Clear(0, nullptr, flags, color.ToInt(), z, stencil);
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
		if (ret != D3D_OK)
		{
			d3d->Release();
			Debug::LogError("Can't create D3D9 Device");
			return SharedPtr<DX9Renderer>::EMPTY;
		}

		return renderer;
	}

	///////////////////////////////////////////////////////////////////////////
	bool DX9Renderer::TestReturnCode(HRESULT ret) const
	{
		if (ret != D3D_OK)
		{
			Debug::LogError("DirectX9: %s - %s",
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
		case VertexElement::DT_COLOR32: return D3DDECLTYPE_D3DCOLOR;
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
}