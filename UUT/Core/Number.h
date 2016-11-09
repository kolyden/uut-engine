#pragma once
#include "String.h"

namespace uut
{
	class Number
	{
	public:
		template<typename T>
		static String ToString(T value) { return std::to_string(value); }

		template<typename T>
		static T ToNumeric(const String& value)
		{
			return (T)std::stoi(value.GetData(), nullptr, 10);
		}
	};
}