#include "DX9Plugin.h"
#include <Core/Context.h>
#include "DX9Command.h"
#include "DX9CommandList.h"
#include "DX9VertexBuffer.h"
#include "DX9IndexBuffer.h"
#include "DX9Texture2D.h"
#include "DX9Renderer.h"
#include "DX9PipelineState.h"

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
		UUT_REGISTER_OBJECT(DX9CommandList);
		UUT_REGISTER_OBJECT(DX9Texture2D);
		UUT_REGISTER_OBJECT(DX9PipelineState);

		UUT_REGISTER_MODULE(DX9Renderer);
	}

	void DX9Plugin::OnUnregister()
	{
	}
}