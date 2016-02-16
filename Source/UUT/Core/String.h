#pragma once
#include <string>

namespace uut
{
	class String
	{
	public:
		String();
		String(const char* str);
		String(const String& str);
		String(String&& str);

		bool Equals(const String& str) const;

		operator const char*() const { return _data.c_str(); }

		bool operator == (const String& str) const { return Equals(str); }
		bool operator != (const String& str) const { return !Equals(str); }

		String& operator = (const String& str);
		String& operator = (String&& str);

	protected:
		std::string _data;
	};
}