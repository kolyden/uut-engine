#pragma once
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

		T& operator[] (int index) { return _data[index]; }
		const T& operator[] (int index) const { return _data[index]; }

		int Count() const { return _count; }

	protected:
		T* _data;
		int _count;
	};
}