#include "SDLInput.h"
#include <Core/Numeric.h>
#include <Core/Boolean.h>
#include <SDL2/SDL_events.h>

namespace uut
{
	UUT_MODULE_IMPLEMENT(SDLInput)
	{
	}

	SDLInput::SDLInput()
		: _mousePos(0)
		, _mouseDelta(0)
		, _kbMod(0)
	{
		_mouseButton[0] = false;
		_mouseButton[1] = false;
		_mouseButton[2] = false;

		_prevKbState.Clear();
		_kbState.Clear();
	}

	void SDLInput::NewFrame()
	{
		_mouseDelta = 0;
	}

	void SDLInput::AddEvent(const SDL_KeyboardEvent& evt, bool pressed)
	{
		_prevKbState[evt.keysym.scancode] = _kbState[evt.keysym.scancode];
		_kbState[evt.keysym.scancode] = pressed;
	}

	void SDLInput::AddEvent(const SDL_MouseButtonEvent& evt, bool pressed)
	{
		switch (evt.button)
		{
		case SDL_BUTTON_LEFT: _mouseButton[0] = pressed; break;
		case SDL_BUTTON_RIGHT: _mouseButton[1] = pressed; break;
		case SDL_BUTTON_MIDDLE: _mouseButton[2] = pressed; break;
		}		
	}

	void SDLInput::AddEvent(const SDL_MouseMotionEvent& evt)
	{
		_mousePos = IntVector2(evt.x, evt.y);
	}

	void SDLInput::AddEvent(const SDL_MouseWheelEvent& evt)
	{
		_mouseDelta = evt.y;
	}

	bool SDLInput::IsMouseButton(int button) const
	{
		return _mouseButton[button];
	}

	const uut::IntVector2& SDLInput::GetMousePos() const
	{
		return _mousePos;
	}

	float SDLInput::GetMouseDelta() const
	{
		return _mouseDelta;
	}

	bool SDLInput::IsKey(Scancode key) const
	{
		return _kbState[(int)key];
	}

	bool SDLInput::IsKeyDown(Scancode key) const
	{
		return !_prevKbState[(int)key] && _kbState[(int)key];
	}

	bool SDLInput::IsKeyUp(Scancode key) const
	{
		return _prevKbState[(int)key] && !_kbState[(int)key];
	}
}