#pragma once

namespace uut
{
	template<typename T>
	class BitArray
	{
	public:
		
		template<int bit>
		static void Set(T& flag) { flag |= 1 << bit; }

		template<int bit>
		static void Clear(T& flag) { flag &= ~(1 << bit); }

		template<int bit>
		static void Set(T& flag, bool value) { value ? Set(flag) : Clear(flag); }

		template<int bit>
		static void Toggle(T& flag) { flag ^= 1 << bit; }

		template<int bit>
		static bool Check(const T& flag) { return (flag >> bit) & 1; }
	};
}