#pragma once
#include <Core/IO/InputSystem.h>
#include <SDL2/SDL_events.h>
#include <Core/Collections/Array.h>

namespace uut
{
	class SDLInput : public InputSystem
	{
		UUT_MODULE(uut, SDLInput, InputSystem)
	public:
		SDLInput();

		void NewFrame();
		void AddEvent(const SDL_KeyboardEvent& evt, bool pressed);
		void AddEvent(const SDL_MouseButtonEvent& evt, bool pressed);
		void AddEvent(const SDL_MouseMotionEvent& evt);
		void AddEvent(const SDL_MouseWheelEvent& evt);

		virtual bool IsMouseButton(int button) const override;
		virtual const IntVector2& GetMousePos() const override;
		virtual float GetMouseDelta() const override;

		virtual bool IsKey(Scancode key) const override;
		virtual bool IsKeyDown(Scancode key) const override;
		virtual bool IsKeyUp(Scancode key) const override;

	private:
		static const int KEYS_COUNT = 512;

		IntVector2 _mousePos;
		float _mouseDelta;
		Array<uint8_t, KEYS_COUNT> _prevKbState;
		Array<uint8_t, KEYS_COUNT> _kbState;

		int _kbMod;
		bool _mouseButton[3];
	};
}