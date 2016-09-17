#pragma once
#include <functional>

namespace uut
{
	typedef size_t HashValue;

	template<typename T>
	static HashValue GetHashCode(const T& value)
	{
		static std::hash<T> hash_fn;
		return hash_fn(value);
	}

#define UUT_DEFINE_HASH(type, hash) \
	template<> static HashValue GetHashCode<type>(const type& value) \
	{ return hash; }

	struct Hash
	{
		template<typename... Args>
		static HashValue Make(Args... args)
		{
			HashValue hash = 2166136261;
			_MakeHash(hash, args...);
			return hash;
		}

		template<>
		static HashValue Make()
		{
			return 0;
		}

	protected:
		template<typename T>
		static void _MakeHash(HashValue& hash, T value)
		{
			hash = (hash * 16777619) ^ GetHashCode(value);
		}

		template<typename T, typename... Args>
		static void _MakeHash(HashValue& hash, T value, Args... args)
		{
			hash = (hash * 16777619) ^ GetHashCode(value);
			_MakeHash(hash, args...);
		}
	};
}