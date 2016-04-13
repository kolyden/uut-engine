#include "Window.h"
#include <Core/Debug.h>
#include <Core/Video/Image.h>
#include "SDL2/SDL.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(Window)
	{
	}

	Window::Window()
		: _size(320, 200)
		, _data(nullptr)
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

		const int flags = SDL_WINDOW_SHOWN;
		_data = SDL_CreateWindow(_title,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			_size.x, _size.y,
			flags);
		if (_data == nullptr)
		{
			Debug::LogError("Could not create window: %s", SDL_GetError());
			//printf("Could not create window: %s\n", SDL_GetError());
			return false;
		}

		SDL_SetWindowData(_data, "__handle__", this);

		if (_icon)
			SDL_SetWindowIcon(_data, reinterpret_cast<SDL_Surface*>(_icon->GetInternalHandle()));		

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

	void Window::SetIcon(Image* icon)
	{
		if (_icon == icon || (icon != nullptr && !icon->IsCreated()))
			return;

		_icon = icon;
		if (IsCreated())
			SDL_SetWindowIcon(_data, reinterpret_cast<SDL_Surface*>(_icon->GetInternalHandle()));
	}

	Image* Window::GetIcon() const
	{
		return _icon;
	}

	bool Window::IsMouseFocused() const
	{
		return IsCreated() ? SDL_GetMouseFocus() == _data : false;
	}

	Window* Window::GetFocusedWindow()
	{
		auto window = SDL_GetMouseFocus();
		if (window == nullptr)
			return nullptr;

		return reinterpret_cast<Window*>(SDL_GetWindowData(window, "__handle__"));
	}

	uintptr_t Window::GetInternalHandle() const
	{
		return reinterpret_cast<uintptr_t>(_data);
	}
}
