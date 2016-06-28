#include "DX9Plugin.h"
#include "Core/Context.h"
#include "DX9VertexBuffer.h"
#include "DX9IndexBuffer.h"
#include "DX9VertexDeclaration.h"
#include "DX9Texture2D.h"
#include "DX9Renderer.h"

namespace uut
{
	DX9Plugin::DX9Plugin()
		: Plugin("DirectX9", Version(0, 1))
	{
	}

	void DX9Plugin::OnRegister()
	{
		UUT_REGISTER_OBJECT(DX9VertexBuffer);
		UUT_REGISTER_OBJECT(DX9IndexBuffer);
		UUT_REGISTER_OBJECT(DX9VertexDeclaration);
		UUT_REGISTER_OBJECT(DX9Texture2D);

		UUT_REGISTER_MODULE(DX9Renderer);
	}

	void DX9Plugin::OnUnregister()
	{
	}
}