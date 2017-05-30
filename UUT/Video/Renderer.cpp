#include "Renderer.h"
#include "Core/Windows/Window.h"
#include <Resources/ResourceCache.h>

namespace uut
{
	UUT_MODULE_IMPLEMENT(Renderer)
	{}

	Renderer::Renderer()
		: _screenSize(0)
	{
	}

	Renderer::~Renderer()
	{
	}

	//////////////////////////////////////////////////////////////////////////////
	bool Renderer::OnInit()
	{
		if (!Super::OnInit())
			return false;

		ModuleInstance<ResourceCache> cache;
		cache->AddResource(CreateMonoTexture(Color32::White), "white");
		cache->AddResource(CreateMonoTexture(Color32::Black), "black");

		return true;
	}

	void Renderer::OnDone()
	{
	}

	SharedPtr<Texture2D> Renderer::CreateMonoTexture(const Color32& color)
	{
		auto tex = CreateTexture(Vector2i(1), TextureAccess::Static);
		uint32_t* buf = static_cast<uint32_t*>(tex->Lock());
		if (buf == nullptr)
			return nullptr;

		buf[0] = color.ToInt();
		tex->Unlock();

		return tex;
	}
}
