#pragma once
#include "Platform.h"

namespace uut
{
	class Timer
	{
	public:
		Timer();

		void Start();
		void Update();

		float GetElapsedTime() const { return _elapsedTime; }
		float GetDeltaTime() const { return _deltaTime; }
		
	protected:
		uint32_t _prevTime;
		float _elapsedTime;
		float _deltaTime;

		friend class Application;
	};
}