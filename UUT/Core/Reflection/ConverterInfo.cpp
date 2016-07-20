#include "ConverterInfo.h"

namespace uut
{
	MemberType IConverterInfo::GetMemberType() const
	{
		return MemberType::Converter;
	}

	const String& IConverterInfo::GetName() const
	{
		static const String name("Converter");
		return name;
	}
}