#include "Char.h"
#include <Core/Math/Math.h>
#include <Core/Reflection/ConverterInfo.h>

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(Char)
	{
		UUT_REGISTER_CONVERTER_DEFAULT(int);
		UUT_REGISTER_CONVERTER_DEFAULT(unsigned);
// 		UUT_REGISTER_CONVERTER_DEFAULT(wchar_t);
	}

	const List<char> Char::WhiteSpaces = { ' ', '\n', '\t' };

	int Char::Compare(char a, char b, StringComparison comparisonType /*= StringComparison::Ordinal*/)
	{
		switch (comparisonType)
		{
		case StringComparison::Ordinal: return Math::Compare(a, b);
		case StringComparison::OrdinalIgnoreCase:
			if (tolower(a) > tolower(b)) return +1;
			if (tolower(a) < tolower(b)) return -1;
			return 0;
		}

		return 0;
	}

	bool Char::IsWhiteSpace(char c)
	{
		for (auto& it : WhiteSpaces)
		{
			if (c == it)
				return true;
		}

		return false;
	}
}