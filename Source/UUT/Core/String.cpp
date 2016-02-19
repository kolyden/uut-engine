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

	String::String(const std::string& str)
		: _data(str)
	{
	}

	String::String(std::string&& str)
	{
		std::swap(_data, str);
	}

	bool String::Equals(const char* str) const
	{
		return _data.compare(str) == 0;
	}

	bool String::Equals(const String& str) const
	{
		return _data.compare(str._data) == 0;
	}
	
	String& String::operator=(const char* str)
	{
		_data = str;
		return *this;
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

	String& String::operator+=(const char* str)
	{
		_data.append(str);
		return *this;
	}

	String& String::operator+=(const String& str)
	{
		_data.append(str._data);
		return *this;
	}

	String String::operator + (const char* str) const
	{
		return _data + str;
	}

	String String::operator + (const String& str) const
	{
		return _data + str._data;
	}
}