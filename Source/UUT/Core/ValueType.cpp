#include "ValueType.h"

namespace uut
{
	ValueType::~ValueType()
	{
	}

	Type& ValueType::GetTypeInternal()
	{
		static Type t(TypeInfo::Struct, "ValueType", nullptr, &_RegisterInternal);
		return t;
	}

	void ValueType::_RegisterInternal()
	{
	}
}