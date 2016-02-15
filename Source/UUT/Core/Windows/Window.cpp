#include "Window.h"

namespace uut
{
	Window::Window()
		: _data(nullptr)
		, _size(320, 200)
	{
	}

	Window::~Window()
	{
		Destroy();
	}

	bool Window::Create()
	{
		if (IsCreated())
			return true;

		_data = SDL_CreateWindow(_title,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			_size.x, _size.y,
			SDL_WINDOW_OPENGL);

		if (_data == nullptr)
		{
			printf("Could not create window: %s\n", SDL_GetError());
			return false;
		}

		return true;
	}

	void Window::Destroy()
	{
		if (!IsCreated())
			return;

		SDL_DestroyWindow(_data);
		_data = nullptr;
	}

	bool Window::IsCreated() const
	{
		return _data != nullptr;
	}

	void Window::PoolEvent()
	{
		SDL_Event evt;
		while (SDL_PollEvent(&evt))
		{

		}
	}

	void Window::SetTitle(const String& title)
	{
		if (_title == title)
			return;

		_title = title;
		if (_data != nullptr)
			SDL_SetWindowTitle(_data, _title);
	}

	const String& Window::GetTitle() const
	{
		return _title;
	}

	void Window::SetSize(const IntVector2& size)
	{
		if (_size == size)
			return;

		_size = size;
		if (_data != nullptr)
			SDL_SetWindowSize(_data, _size.x, _size.y);
	}

	const IntVector2& Window::GetSize() const
	{
		return _size;
	}

	uintptr_t Window::GetInternalHandle() const
	{
		return (uintptr_t)_data;
	}
}