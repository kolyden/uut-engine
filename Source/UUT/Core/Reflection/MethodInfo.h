#pragma once
#include "MemberInfo.h"
#include <Core/Collections/List.h>
#include <Core/Variant.h>
#include "MethodAttributes.h"
#include "FunctionUtils.h"
#include <tuple>

namespace uut
{
	class MethodInfo : public MemberInfo
	{
	public:
		typedef List<const Type*> ArgsTypes;

		explicit MethodInfo(const String& name, MethodAttributes attributes);

		virtual const ArgsTypes& GetArgsTypes() const = 0;
		virtual const Type* GetReturnType() const = 0;
		virtual bool Call(const List<Variant>& args) const = 0;
		virtual bool Call(const List<Variant>& args, Variant& result) const = 0;

		virtual MemberType GetMemberType() const override { return MemberType::Method; }
		virtual const String& GetName() const override { return _name; }

		bool IsPrivate() const { return _attributes.HasFlag(MethodAttribute::Private); }
		bool IsPublic() const { return _attributes.HasFlag(MethodAttribute::Public); }
		bool IsStatic() const { return _attributes.HasFlag(MethodAttribute::Static); }

	protected:
		String _name;
		MethodAttributes _attributes;
	};

	//////////////////////////////////////////////////////////////////////////
	template<typename Ret, typename... Args>
	class StaticFunctionInfo : public MethodInfo
	{
	public:
		using FuncType = Ret(*)(Args...);
		typedef std::tuple<typename TypeUnpack<Args>::type...> TUPLE;
		static const size_t ARGS_COUNT = sizeof...(Args);

		StaticFunctionInfo(const String& name, FuncType function)
			: MethodInfo(name, MethodAttribute::Static)
			, _function(function)
		{}

		virtual const ArgsTypes& GetArgsTypes() const override
		{
			static const List<const Type*> types{typeof<Args>()...};
			return types;
		}

		virtual const Type* GetReturnType() const override
		{
			return typeof<Ret>();
		}

		virtual bool Call(const List<Variant>& args) const override
		{
			TUPLE tuple;
			for (int i = 0; i < ARGS_COUNT; i++)
				UnpackTuple<TUPLE>::set(tuple, i, args[i]);

			CallSequence(typename TupleGens<sizeof...(Args)>::type(), tuple);
			return true;
		}

		virtual bool Call(const List<Variant>& args, Variant& result) const override
		{
			TUPLE tuple;
			for (int i = 0; i < ARGS_COUNT; i++)
				UnpackTuple<TUPLE>::set(tuple, i, args[i]);

			result = CallSequence(typename TupleGens<sizeof...(Args)>::type(), tuple);
			return true;
		}

	protected:
		FuncType _function;

		template<typename ARGS, int... S>
		Ret CallSequence(TupleSeq<S...>, ARGS params) const
		{
			return _function(std::get<S>(params)...);
		}
	};

	//////////////////////////////////////////////////////////////////////////
	template<class C, typename Ret, typename... Args>
	class MethodInfoImpl : public MethodInfo
	{
	public:
		using FuncType = Ret(C::*)(Args...);
		typedef std::tuple<typename TypeUnpack<Args>::type...> TUPLE;
		static const size_t ARGS_COUNT = sizeof...(Args);

		MethodInfoImpl(const String& name, FuncType function)
			: MethodInfo(name, MethodAttribute::Public)
			, _function(function)
		{}

		virtual const ArgsTypes& GetArgsTypes() const override
		{
			static const List<const Type*> types{ typeof<Args>()... };
			return types;
		}

		virtual const Type* GetReturnType() const override
		{
			return typeof<Ret>();
		}

		virtual bool Call(const List<Variant>& args) const override
		{
			TUPLE tuple;
			for (int i = 0; i < ARGS_COUNT; i++)
				UnpackTuple<TUPLE>::set(tuple, i, args[i]);

			CallSequence(typename TupleGens<sizeof...(Args)>::type(), tuple);
			return true;
		}

		virtual bool Call(const List<Variant>& args, Variant& result) const override
		{
			TUPLE tuple;
			for (int i = 0; i < ARGS_COUNT; i++)
				UnpackTuple<TUPLE>::set(tuple, i, args[i]);

			result = CallSequence(typename TupleGens<sizeof...(Args)>::type(), tuple);
			return true;
		}

	protected:
		FuncType _function;

		template<typename ARGS, int... S>
		Ret CallSequence(TupleSeq<S...>, ARGS params) const
		{
			return _function(std::get<S>(params)...);
		}
	}; }
