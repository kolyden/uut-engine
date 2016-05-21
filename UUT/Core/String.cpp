#include "String.h"
#include "Math/Math.h"

namespace uut
{
	UUT_STRUCT_IMPLEMENT(String)
	{}

	const String String::Empty;

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

	bool String::EndsWith(const String& ends) const
	{
		return EndsWith(ends, StringComparison::Ordinal);
	}

	bool String::EndsWith(const String& ends, StringComparison comparisonType) const
	{
		const int endsCount = ends.Count();
		if (endsCount == 0)
			return false;

		const int strCount = Count();
		if (strCount < endsCount)
			return false;

		const int start = strCount - endsCount;
		for (int i = start; i < strCount; i++)
		{
			if (CompareChar(_data[i], ends[i - start], comparisonType) != 0)
				return false;
		}

		return true;
	}

	int String::IndexOf(char value) const
	{
		return IndexOf(value, StringComparison::Ordinal);
	}

	int String::IndexOf(char value, StringComparison comparisonType) const
	{
		const int strCount = Count();
		if (strCount == 0)
			return -1;

		for (int i = 0; i < strCount; i++)
		{
			if (CompareChar(_data[i], value, comparisonType) == 0)
				return i;
		}

		return -1;
	}

	int String::IndexOf(const String& value) const
	{
		return IndexOf(value, 0, StringComparison::Ordinal);
	}

	int String::IndexOf(const String& value, StringComparison comparisonType) const
	{
		return IndexOf(value, 0, comparisonType);
	}

	int String::IndexOf(const String& value, int startIndex, StringComparison comparisonType) const
	{
		const int strCount = Count();
		const int valCount = value.Count();
		if (strCount == 0 || valCount == 0)
			return -1;

		for (int i = startIndex; i < strCount - valCount + 1; i++)
		{
			bool found = true;
			for (int j = 0; j < valCount; j++)
			{
				if (CompareChar(_data[i + j], value[j], comparisonType) == 0)
					continue;

				found = false;
				break;
			}

			if (found)
				return i;
		}

		return -1;
	}

	void String::Insert(int index, const String& value)
	{
		_data.insert(index, value);
	}

	int String::LastIndexOf(char value) const
	{
		return LastIndexOf(value, StringComparison::Ordinal);
	}

	int String::LastIndexOf(char value, StringComparison comparisonType) const
	{
		const int strCount = Count();
		if (strCount == 0)
			return -1;

		for (int i = strCount - 1; i >= 0; i--)
		{
			if (CompareChar(_data[i], value, comparisonType) == 0)
				return i;
		}

		return -1;
	}

	int String::LastIndexOf(const String& value) const
	{
		return LastIndexOf(value, StringComparison::Ordinal);
	}

	int String::LastIndexOf(const String& value, StringComparison comparisonType) const
	{
		const int strCount = Count();
		const int valCount = value.Count();
		if (strCount == 0 || valCount == 0)
			return -1;

		for (int i = strCount - valCount; i >= 0; i--)
		{
			bool found = true;
			for (int j = 0; j < valCount; j++)
			{
				if (CompareChar(_data[i + j], value[j], comparisonType) == 0)
					continue;

				found = false;
				break;
			}

			if (found)
				return i;
		}

		return -1;
	}

	void String::Remove(int startIndex)
	{
		_data.erase(startIndex);
	}

	void String::Remove(int startIndex, int length)
	{
		_data.erase(startIndex, length);
	}

	int String::Replace(char oldChar, char newChar)
	{
		int count = 0;
		for (uint i = 0; i < Count(); i++)
		{
			if (CompareChar(_data[i], oldChar) != 0)
				continue;

			_data[i] = newChar;
			count++;
		}

		return count;
	}

	int String::Replace(const String& oldValue, const String& newValue)
	{
		int count = 0;
		int prev = 0, pos;
		while ((pos = IndexOf(oldValue, prev, StringComparison::Ordinal)) >= 0)
		{
			_data.replace(pos, oldValue.Count(), newValue);
			prev = pos + newValue.Count();
			count++;
		}
		return count;
	}

	int String::Split(char c, List<String>& out) const
	{
		int count = 0;
		int pos = 0;
		DataType str = _data;
		while ((pos = static_cast<int>(str.find(c))) >= 0)
		{
			DataType word = str.substr(0, pos);
			str.erase(0, pos + 1);
			if (!word.empty())
			{
				out << word;
				count++;
			}
		}

		if (!str.empty())
		{
			out << str;
			count++;
		}

		return count;
	}

	List<String> String::Split(char c) const
	{
		List<String> ret;
		Split(c, ret);
		return ret;
	}

	String String::Substring(int startIndex) const
	{
		return _data.substr(startIndex);
	}

	String String::Substring(int startIndex, int length) const
	{
		return _data.substr(startIndex, length);
	}

	bool String::Equals(const String& str) const
	{
		return Equals(str, StringComparison::Ordinal);
	}

	bool String::Equals(const String& str, StringComparison comparisonType) const
	{
		return Compare(*this, str, comparisonType) == 0;
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

	String& String::operator+=(char c)
	{
		_data.append(1, c);
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

	String String::Join(const List<String>& list, const String& str)
	{
		if (list.IsEmpty())
			return Empty;

		if (list.Count() == 1)
			return list[0];

		String text = list[0];
		for (uint i = 1; i < list.Count(); i++)
		{
			text += str;
			text += list[i];
		}

		return text;
	}

	String String::Format(const char* format, ...)
	{
		const int buf_size = 512;
		char buf[buf_size];

		va_list args;
		va_start(args, format);
		vsprintf_s(buf, buf_size, format, args);
		va_end(args);

		return buf;
	}

	int String::CompareChar(char a, char b, StringComparison comparisonType)
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

	int String::Compare(const String& a, const String& b, StringComparison comparisonType)
	{
		const int lng_a = a.Count();
		const int lng_b = b.Count();
		const int lng = Math::Min(lng_a, lng_b);

		for (int i = 0; i < lng; i++)
		{
			const int ret = CompareChar(a[i], b[i], comparisonType);
			if (ret != 0)
				return ret;
		}

		return  Math::Compare(lng_a, lng_b);
	}
}