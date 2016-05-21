#pragma once
#include "Core/Platform.h"
#include "Core/Debug.h"

namespace uut
{
	template<typename T, uint N>
	class Array
	{
	public:
		T& operator[] (uint index) { return _data[index]; }
		const T& operator[] (uint index) const { return _data[index]; }

		static uint Count() { return N; }

	protected:
		T _data[N];
	};
}