#pragma once
#include <Core/Variant.h>
#include <tuple>

namespace uut
{
	template<class T>
	struct TypeUnpack
	{
		typedef T type;
	};

	template<class T>
	struct TypeUnpack < const T >
	{
		typedef T type;
	};

	template<class T>
	struct TypeUnpack < const T* >
	{
		typedef T* type;
	};

	// because of return value for script
	// 	template<class T>
	// 	struct TypeUnpack < T& >
	// 	{
	// 		typename typedef T type;
	// 	};

	template<class T>
	struct TypeUnpack < const T& >
	{
		typedef T type;
	};

	template<class T>
	struct TypeUnpack < T&& >
	{
		typedef T type;
	};

	//////////////////////////////////////////////////////////////////////////
	template<int ...>
	struct TupleSeq {};

	template<int N, int... S>
	struct TupleGens : TupleGens<N - 1, N - 1, S...> {};

	template<int... S>
	struct TupleGens<0, S...>
	{
		typedef TupleSeq<S...> type;
	};

	//////////////////////////////////////////////////////////////////////////
	template <typename Tuple,
		size_t I = std::tuple_size<Tuple>::value - 1>
		class UnpackTuple
	{
	public:
		static bool set(Tuple & tuple, size_t index, const Variant& data)
		{
			if (index == I)
			{
				typename std::tuple_element<I, Tuple>::type val;
				if (!data.TryGet(val))
					return false;

				std::get<I>(tuple) = val;
				return true;
			}

			return UnpackTuple<Tuple, I - 1>::set(tuple, index, data);
		}
	};

	template <typename Tuple>
	class UnpackTuple < Tuple, 0 >
	{
	public:
		static bool set(Tuple & tuple, size_t index, const Variant& data)
		{
			if (index == 0)
			{
				typename std::tuple_element<0, Tuple>::type val;
				if (!data.TryGet(val))
					return false;

				std::get<0>(tuple) = val;
				return true;
			}

			return false;
		}
	};
}
