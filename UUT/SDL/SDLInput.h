#pragma once
#include <Core/IO/InputSystem.h>
#include <Core/Collections/Array.h>

struct SDL_KeyboardEvent;
struct SDL_MouseButtonEvent;
struct SDL_MouseMotionEvent;
struct SDL_MouseWheelEvent;

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
		virtual const Vector2i& GetMousePos() const override;
		virtual float GetMouseDelta() const override;

		virtual bool IsKey(Scancode key) const override;
		virtual bool IsKeyDown(Scancode key) const override;
		virtual bool IsKeyUp(Scancode key) const override;

	private:
		static const int KEYS_COUNT = 512;

		Vector2i _mousePos;
		float _mouseDelta;
		Array<bool, KEYS_COUNT> _prevKbState;
		Array<bool, KEYS_COUNT> _kbState;

		int _kbMod;
		bool _mouseButton[3];
	};
}