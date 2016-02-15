#include "Renderer.h"
#include "Core/Windows/Window.h"

namespace uut
{
	Renderer::Renderer()
		: _data(nullptr)
	{
	}

	Renderer::~Renderer()
	{
		Destroy();
	}

	bool Renderer::Create(Window* window)
	{
		if (IsCreated() || window == nullptr)
			return true;

		_window = window;
		auto win = (SDL_Window*)_window->GetInternalHandle();
		_data = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
		return IsCreated();
	}

	void Renderer::Destroy()
	{
		if (!IsCreated())
			return;

		_window = nullptr;
		SDL_DestroyRenderer(_data);
	}

	bool Renderer::IsCreated() const
	{
		return _data != nullptr;
	}

	void Renderer::SetColor(const Color32& color)
	{
		if (!IsCreated())
			return;

		SDL_SetRenderDrawColor(_data, color.r, color.g, color.b, color.a);
	}

	void Renderer::Clear()
	{
		if (IsCreated())
			SDL_RenderClear(_data);
	}

	void Renderer::Present()
	{
		if (IsCreated())
			SDL_RenderPresent(_data);
	}

	void Renderer::DrawTexture(Texture* tex, int x, int y)
	{
		DrawTexture(tex, IntVector2(x, y));
	}

	void Renderer::DrawTexture(Texture* tex, const IntVector2& pos)
	{
		if (!IsCreated())
			return;

		const IntVector2& size = tex->GetSize();
		const SDL_Rect dest{ pos.x, pos.y, size.x, size.y };
		SDL_RenderCopy(_data, tex->_data, nullptr, &dest);
	}

	SharedPtr<Texture> Renderer::CreateTexture(const IntVector2& size, TextureAccess access /* = TextureAccess::Static */)
	{
		if (!IsCreated())
			return SharedPtr<Texture>::EMPTY;

		int sdlAccess = 0;
		switch (access)
		{
		case uut::TextureAccess::Static:
			sdlAccess = SDL_TEXTUREACCESS_STATIC;
			break;

		case uut::TextureAccess::Streaming:
			sdlAccess = SDL_TEXTUREACCESS_STREAMING;
			break;

		case uut::TextureAccess::Target:
			sdlAccess = SDL_TEXTUREACCESS_TARGET;
			break;
		}

		auto data = SDL_CreateTexture(_data,
			SDL_PIXELFORMAT_RGBA8888, sdlAccess, size.x, size.y);
		if (data == nullptr)
			return SharedPtr<Texture>::EMPTY;

		SharedPtr<Texture> tex(new Texture());
		tex->_data = data;
		tex->_size = size;
		tex->_access = access;
		return tex;
	}
}