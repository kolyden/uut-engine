#pragma once
#include <Core/Module.h>
#include <Core/Math/IntVector2.h>

namespace uut
{
	class Input : public Module
	{
		UUT_MODULE(Input, Module)
	public:
		Input();
		virtual ~Input();

		static bool IsMouseButton(int button);
		static const IntVector2& GetMousePos();

		static bool IsKey(int key);
		static bool IsKeyDown(int key);
		static bool IsKeyUp(int key);

		void UpdateState();

	protected:
		static const int KEYS_COUNT = 512;

		IntVector2 _mousePos;
		uint8_t _prevKbState[KEYS_COUNT];
		uint8_t _kbState[KEYS_COUNT];

		int _kbMod;
		bool _mouseButton[3];
	};
}