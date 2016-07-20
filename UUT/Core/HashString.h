#pragma once
#include <string>

namespace uut
{
	class HashString
	{
	public:
		HashString();
		HashString(const char* str);
		HashString(const HashString& str);
		HashString(HashString&& str);

		void Clear();
		bool IsEmpty() const { return _hash == 0; }

		const char* GetData() const { return _data.c_str(); }
		size_t GetHash() const { return _hash; }

		bool Equals(const HashString& str) const;
		int Compare(const HashString& str) const;

		operator const size_t() const { return _hash; }

		HashString& operator=(const char* str);
		HashString& operator=(const HashString& str);
		HashString& operator=(HashString&& str);

		bool operator == (const HashString& str) const { return Equals(str); }
		bool operator != (const HashString& str) const { return !Equals(str); }
		bool operator <= (const HashString& str) const { return _hash <= str._hash; }
		bool operator >= (const HashString& str) const { return _hash >= str._hash; }
		bool operator < (const HashString& str) const { return _hash < str._hash; }
		bool operator > (const HashString& str) const { return _hash > str._hash; }

		static const HashString Empty;

	protected:
		std::string _data;
		size_t _hash;

		static size_t CalcHash(const std::string& str);
	};
}