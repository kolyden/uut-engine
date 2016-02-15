#include "String.h"

namespace uut
{
	String::String()
	{
	}

	String::String(const char* str)
		: _data(str)
	{
	}

	String::String(const String& str)
		: _data(str._data)
	{
	}

	String::String(String&& str)
	{
		std::swap(_data, str._data);
	}

	bool String::Equals(const String& str) const
	{
		return _data.compare(str._data) == 0;
	}

	String& String::operator=(const String& str)
	{
		_data = str._data;
		return *this;
	}

	String& String::operator=(String&& str)
	{
		std::swap(_data, str._data);
		return *this;
	}
}