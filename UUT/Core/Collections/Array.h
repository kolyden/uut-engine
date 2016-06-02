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

		void Set(const T& value)
		{
			for (uint i = 0; i < N; i++)
				_data[i] = value;
		}

		void Clear() { Set(GetDefault<T>()); }

		static uint Count() { return N; }

	protected:
		T _data[N];
	};
}