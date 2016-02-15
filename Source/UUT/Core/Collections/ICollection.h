#pragma once
#include "IEnumerable.h"

namespace uut
{
	template<typename T>
	class ICollection : public IEnumerable<T>
	{
	public:
	};
}