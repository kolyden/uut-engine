#include "Input.h"
#include "SDL2/SDL.h"
#include <Core/Numeric.h>
#include <Core/Math/Math.h>

namespace uut
{
	UUT_MODULE_IMPLEMENT(Input)
	{}

	static Input* g_this = nullptr;

	Input::Input()
		: _mousePos(0)
		, _kbMod(0)
	{
		g_this = this;
		_mouseButton[0] = false;
		_mouseButton[1] = false;
		_mouseButton[2] = false;

		_prevKbState.Clear();
		_kbState.Clear();
	}

	Input::~Input()
	{		
	}
	
	bool Input::IsMouseButton(int button)
	{
		return g_this ? g_this->_mouseButton[button] : false;
	}

	const IntVector2& Input::GetMousePos()
	{
		return g_this? g_this->_mousePos : IntVector2::Zero;
	}

	bool Input::IsKey(int key)
	{
		return g_this && g_this->_kbState[key] > 0;
	}

	bool Input::IsKeyDown(int key)
	{
		if (g_this == nullptr)
			return false;

		return g_this->_prevKbState[key] == 0 && g_this->_kbState[key] > 0;
	}

	bool Input::IsKeyUp(int key)
	{
		if (g_this == nullptr)
			return false;

		return g_this->_prevKbState[key] > 0 && g_this->_kbState[key] == 0;
	}

	void Input::UpdateState()
	{
		const int buttons = SDL_GetMouseState(&_mousePos.x, &_mousePos.y);
		_mouseButton[0] = (buttons & SDL_BUTTON_LMASK) == SDL_BUTTON_LMASK;
		_mouseButton[1] = (buttons & SDL_BUTTON_RMASK) == SDL_BUTTON_RMASK;
		_mouseButton[2] = (buttons & SDL_BUTTON_MMASK) == SDL_BUTTON_MMASK;

		for (int i = 0; i < KEYS_COUNT; i++)
			_prevKbState[i] = _kbState[i];

		int keysCount;
		auto state = SDL_GetKeyboardState(&keysCount);
		const int count = Math::Min(keysCount, KEYS_COUNT);
		for (int i = 0; i < count; i++)
			_kbState[i] = state[i];
		_kbMod = SDL_GetModState();
	}
}
