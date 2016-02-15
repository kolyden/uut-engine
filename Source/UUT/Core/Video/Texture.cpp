#include "Texture.h"

namespace uut
{
	Texture::Texture()
		: _data(0)
		, _size(0)
		, _access(TextureAccess::Static)
	{
	}

	Texture::~Texture()
	{
		Destroy();
	}

	void Texture::Destroy()
	{
		if (_data == nullptr)
			return;

		SDL_DestroyTexture(_data);
		_data = nullptr;
	}

	bool Texture::IsCreated() const
	{
		return _data != nullptr;
	}

	void* Texture::Lock()
	{
		if (!IsCreated())
			return nullptr;

		void* buf;
		int pitch;
		if (SDL_LockTexture(_data, nullptr, &buf, &pitch) != 0)
			return nullptr;

		return buf;
	}

	void Texture::Unlock()
	{
		if (_data != nullptr)
		SDL_UnlockTexture(_data);
	}
}