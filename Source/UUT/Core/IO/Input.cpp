#include "Input.h"
#include "SDL2/SDL.h"

namespace uut
{
	static Input* g_this = nullptr;

	Input::Input()
		: _mousePos(0)
		, _kbState(nullptr)
		, _kbMod(0)
	{
		g_this = this;
		_mouseButton[0] = false;
		_mouseButton[1] = false;
		_mouseButton[2] = false;
	}
	
	bool Input::IsMouseButton(int button)
	{
		return g_this ? g_this->_mouseButton[button] : false;
	}

	const IntVector2& Input::GetMousePos()
	{
		return g_this? g_this->_mousePos : IntVector2::ZERO;
	}

	bool Input::IsKey(int key)
	{
		return g_this && g_this->_kbState ? g_this->_kbState[key] > 0 : false;
	}

	void Input::UpdateState()
	{
		const int buttons = SDL_GetMouseState(&_mousePos.x, &_mousePos.y);
		_mouseButton[0] = (buttons & SDL_BUTTON_LMASK) == SDL_BUTTON_LMASK;
		_mouseButton[1] = (buttons & SDL_BUTTON_RMASK) == SDL_BUTTON_RMASK;
		_mouseButton[2] = (buttons & SDL_BUTTON_MMASK) == SDL_BUTTON_MMASK;
		_kbState = SDL_GetKeyboardState(nullptr);
		_kbMod = SDL_GetModState();
	}
}