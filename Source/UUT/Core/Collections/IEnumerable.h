#pragma once
#include "Core/Collections/Enumerator.h"

namespace uut
{
	template<typename T>
	class IEnumerable
	{
	public:
		virtual Enumerator<T> Begin() = 0;
		virtual Enumerator<T> End() = 0;
	};
}