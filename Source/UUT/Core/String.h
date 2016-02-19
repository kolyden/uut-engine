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
		String(const std::string& str);
		String(std::string&& str);

		bool Equals(const char* str) const;
		bool Equals(const String& str) const;

		int Count() const { return static_cast<int>(_data.size()); }

		operator const char*() const { return _data.c_str(); }

		bool operator == (const char* str) const { return Equals(str); }
		bool operator != (const char* str) const { return !Equals(str); }

		bool operator == (const String& str) const { return Equals(str); }
		bool operator != (const String& str) const { return !Equals(str); }

		String& operator = (const char* str);
		String& operator = (const String& str);
		String& operator = (String&& str);

		String& operator += (const char* str);
		String& operator += (const String& str);

		String operator + (const char* str) const;
		String operator + (const String& str) const;

	protected:
		std::string _data;
	};
}