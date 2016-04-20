#pragma once
#include <Core/Reflection/Type.h>
#include <Core/Platform.h>

namespace uut
{
	class ValueType
	{
	public:
		virtual ~ValueType();

	protected:
		static Type& GetTypeInternal();
		static void _RegisterInternal();

		template<typename T>friend const Type* typeof();
	};
}