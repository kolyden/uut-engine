#include "Input.h"
#include "SDL2/SDL.h"

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

		memset(_prevKbState, 0, KEYS_COUNT);
		memset(_kbState, 0, KEYS_COUNT);
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
		return g_this && g_this->_kbState ? g_this->_kbState[key] > 0 : false;
	}

	bool Input::IsKeyDown(int key)
	{
		if (g_this == nullptr || g_this->_kbState == nullptr)
			return false;

		return g_this->_prevKbState[key] == 0 && g_this->_kbState[key] > 0;
	}

	bool Input::IsKeyUp(int key)
	{
		if (g_this == nullptr || g_this->_kbState == nullptr)
			return false;

		return g_this->_prevKbState[key] > 0 && g_this->_kbState[key] == 0;
	}

	void Input::UpdateState()
	{
		const int buttons = SDL_GetMouseState(&_mousePos.x, &_mousePos.y);
		_mouseButton[0] = (buttons & SDL_BUTTON_LMASK) == SDL_BUTTON_LMASK;
		_mouseButton[1] = (buttons & SDL_BUTTON_RMASK) == SDL_BUTTON_RMASK;
		_mouseButton[2] = (buttons & SDL_BUTTON_MMASK) == SDL_BUTTON_MMASK;

		if (_kbState != nullptr)
		{
			for (int i = 0; i < KEYS_COUNT; i++)
				_prevKbState[i] = _kbState[i];
		}

		auto state = SDL_GetKeyboardState(nullptr);
		for (int i = 0; i < KEYS_COUNT; i++)
			_kbState[i] = state[i];
		_kbMod = SDL_GetModState();
	}
}