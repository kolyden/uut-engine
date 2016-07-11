#pragma once
#include <functional>

namespace uut
{
	template<typename T>
	static size_t GetHashCode(const T& value)
	{
		static std::hash<T> hash_fn;
		return hash_fn(value);
	}

#define UUT_DEFINE_HASH(type, hash) \
	template<> static size_t GetHashCode<type>(const type& value) \
	{ return hash; }

	struct Hash
	{
		template<typename Ret, typename... Args>
		static Ret Make(Args... args)
		{
			Ret hash = 2166136261;
			_make<Ret>(hash, args...);
			return hash;
		}

	protected:
		template<typename Ret, typename T>
		static void _make(Ret& hash, T value)
		{
			hash = (hash * 16777619) ^ value;
		}

		template<typename Ret, typename T, typename... Args>
		static void _make(Ret& hash, T value, Args... args)
		{
			hash = (hash * 16777619) ^ value;
			_MakeHash<Ret>(hash, args...);
		}
	};
}