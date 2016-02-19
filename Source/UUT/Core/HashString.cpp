#include "HashString.h"
#include <algorithm>

namespace uut
{
	HashString::HashString()
		: _hash(0)
	{
	}

	HashString::HashString(const char* str)
		: _data(str)
		, _hash(CalcHash(_data))
	{
	}

	HashString::HashString(const HashString& str)
		: _data(str._data)
		, _hash(str._hash)
	{
	}

	HashString::HashString(HashString&& str)
		: _hash(0)
	{
		std::swap(_hash, str._hash);
		std::swap(_data, str._data);
	}

	void HashString::Clear()
	{
		_data.clear();
		_hash = 0;
	}

	bool HashString::Equals(const HashString& str) const
	{
		return _hash == str._hash;
	}

	int HashString::Compare(const HashString& str) const
	{
		if (_hash < str._hash)
			return -1;
		if (_hash > str._hash)
			return +1;

		return 0;
	}

	HashString& HashString::operator=(const char* str)
	{
		_data = str;
		_hash = CalcHash(_data);
		return *this;
	}

	HashString& HashString::operator=(const HashString& str)
	{
		_data = str._data;
		_hash = str._hash;
		return *this;
	}

	HashString& HashString::operator=(HashString&& str)
	{
		std::swap(_data, str._data);
		std::swap(_hash, str._hash);
		return *this;
	}

	///////////////////////////////////////////////////////////////////////////
	int HashString::CalcHash(const std::string& str)
	{
		static std::hash<std::string> hashfn;

		return hashfn(str);
	}
}