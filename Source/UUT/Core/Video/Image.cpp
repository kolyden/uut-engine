#include "Image.h"

namespace uut
{
	Image::Image()
		: _data(nullptr)
	{
	}

	Image::~Image()
	{
		Destroy();
	}

	bool Image::Create(const IntVector2& size)
	{
		if (_size == size)
			return true;

		Destroy();
		_data = SDL_CreateRGBSurface(0,
			_size.x, _size.y, 32, 0, 0, 0, 0);
		return IsCreated();
	}

	void Image::Destroy()
	{
		if (!IsCreated())
			return;

		SDL_FreeSurface(_data);
		_data = nullptr;
	}

	bool Image::IsCreated() const
	{
		return _data != nullptr;
	}

	uintptr_t Image::GetInternalHandle() const
	{
		return reinterpret_cast<uintptr_t>(_data);
	}
}