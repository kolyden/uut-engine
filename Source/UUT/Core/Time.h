#pragma once
#include "Platform.h"

namespace uut
{
	class Time
	{
	public:
		static float GetElapsedTime() { return _elapsedTime; }
		static float GetDeltaTime() { return _deltaTime; }

	protected:
		static uint32_t _prevTime;
		static float _elapsedTime;
		static float _deltaTime;

		static void Initialize();
		static void BeginFrame();

		friend class Engine;
	};
}