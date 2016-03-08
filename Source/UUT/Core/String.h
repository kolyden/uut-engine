#pragma once
#include <string>
#include "Collections/List.h"

namespace uut
{
	enum class StringComparison
	{
		Ordinal,
		OrdinalIgnoreCase,
	};

	class String
	{
	public:
		typedef std::string DataType;
		typedef DataType::iterator Iterator;
		typedef DataType::const_iterator CIterator;

		String();
		String(const char* str);
		String(const String& str);
		String(String&& str);
		String(const std::string& str);
		String(std::string&& str);

		bool EndsWith(const String& ends) const;
		bool EndsWith(const String& ends, StringComparison comparisonType) const;

		int IndexOf(char value) const;
		int IndexOf(char value, StringComparison comparisonType) const;

		int IndexOf(const String& value) const;
		int IndexOf(const String& value, StringComparison comparisonType) const;
		int IndexOf(const String& value, int startIndex, StringComparison comparisonType) const;

		void Insert(int index, const String& value);

		int LastIndexOf(char value) const;
		int LastIndexOf(char value, StringComparison comparisonType) const;

		int LastIndexOf(const String& value) const;
		int LastIndexOf(const String& value, StringComparison comparisonType) const;

		void Remove(int startIndex);
		void Remove(int startIndex, int length);

		int Replace(char oldChar, char newChar);
		int Replace(const String& oldValue, const String& newValue);

		int Split(char c, List<String>& out) const;
		List<String> Split(char c) const;

		String Substring(int startIndex) const;
		String Substring(int startIndex, int length) const;

		bool Equals(const String& str) const;
		bool Equals(const String& str, StringComparison comparisonType) const;

		int Count() const { return static_cast<int>(_data.size()); }

		operator const char*() const { return _data.c_str(); }

		bool operator == (const char* str) const { return Equals(str); }
		bool operator != (const char* str) const { return !Equals(str); }

		bool operator == (const String& str) const { return Equals(str); }
		bool operator != (const String& str) const { return !Equals(str); }

		String& operator = (const char* str);
		String& operator = (const String& str);
		String& operator = (String&& str);

		String& operator += (char c);
		String& operator += (const char* str);
		String& operator += (const String& str);

		String operator + (const char* str) const;
		String operator + (const String& str) const;

		static String Join(const List<String>& list, const String& str);

		Iterator Begin() { return _data.begin(); }
		Iterator End() { return _data.begin(); }

		CIterator Begin() const { return _data.begin(); }
		CIterator End() const { return _data.begin(); }

		static const String EMPTY;

	protected:
		std::string _data;

		static int CompareChar(char a, char b, StringComparison comparisonType = StringComparison::Ordinal);
		static int Compare(const String& a, const String& b, StringComparison comparisonType = StringComparison::Ordinal);
	};

	template<class T> String::Iterator begin(String& str) { return str.Begin(); }
	template<class T> String::Iterator end(String& str) { return str.End(); }

	template<class T> String::CIterator begin(const String& str) { return str.Begin(); }
	template<class T> String::CIterator end(const String& str) { return str.End(); }
}
