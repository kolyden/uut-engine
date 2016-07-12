#pragma once
#include "MemberInfo.h"
#include <Core/Variant.h>
#include "FunctionUtils.h"

namespace uut
{
	class ConstructorInfo : public MemberInfo
	{
	public:
		typedef List<const Type*> ArgsTypes;

		MemberType GetMemberType() const override { return MemberType::Constructor; }
		const String& GetName() const override;

		virtual const ArgsTypes& GetArgsTypes() const = 0;
		virtual bool Call(void* ptr, const List<Variant>& args = List<Variant>::Empty) const = 0;
	};

	//////////////////////////////////////////////////////////////////////////
	template<class C>
	class DefaultCtorInfo : public ConstructorInfo
	{
	public:
		virtual const ArgsTypes& GetArgsTypes() const override
		{
			return ArgsTypes::Empty;
		}

		virtual bool Call(void* ptr, const List<Variant>& args = List<Variant>::Empty) const override
		{
			new (ptr) C();
			return true;
		}
	};

	//////////////////////////////////////////////////////////////////////////
	template<class C, typename... Args>
	class ConstructorInfoImpl : public ConstructorInfo
	{
	public:
		typedef std::tuple<typename TypeUnpack<Args>::type...> TUPLE;
		static const size_t ARGS_COUNT = sizeof...(Args);

		virtual const ArgsTypes& GetArgsTypes() const override
		{
			static const List<const Type*> types{ TypeOf<Args>()... };
			return types;
		}

		virtual bool Call(void* ptr, const List<Variant>& args = List<Variant>::Empty) const override
		{
			TUPLE tuple;
			for (int i = 0; i < ARGS_COUNT; i++)
				UnpackTuple<TUPLE>::set(tuple, i, args[i]);

			CallSequence(ptr, typename TupleGens<sizeof...(Args)>::type(), tuple);
			return true;
		}

	protected:
		template<typename ARGS, int... S>
		void CallSequence(void* ptr, TupleSeq<S...>, ARGS params) const
		{
			new (ptr) C(std::get<S>(params)...);
		}
	};

#define UUT_REGISTER_CTOR_DEFAULT() internalType->AddMember(new DefaultCtorInfo<ClassName>());
#define UUT_REGISTER_CTOR(...) internalType->AddMember(new ConstructorInfoImpl<ClassName, __VA_ARGS__>());
}