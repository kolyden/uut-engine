#pragma once
#include "Core/Platform.h"
#include "Core/Debug.h"

namespace uut
{
	template<typename T>
	class Array
	{
	public:
		Array() : _data(nullptr), _count(0) {}
		explicit Array(int count)
			: _count(count)
		{
			UUT_ASSERT(count > 0);
			_data = new T[_count];
		}

		virtual ~Array() { delete[] _data; }

		T& operator[] (uint index) { return _data[index]; }
		const T& operator[] (uint index) const { return _data[index]; }

		uint Count() const { return _count; }

	protected:
		T* _data;
        uint _count;
	};
}