#pragma once
#include "MemberInfo.h"
#include "FunctionUtils.h"

namespace uut
{
	class ConverterInfo : public MemberInfo
	{
	public:
		virtual MemberType GetMemberType() const override { return MemberType::Converter; }
		virtual const String& GetName() const override { return  String::Empty; }

		virtual const Type* GetResultType() const = 0;
		virtual bool Convert(const ValueType& source, ValueType& result) const = 0;
	};

	//////////////////////////////////////////////////////////////////////////
	template<typename TIn, typename TOut>
	class ConverterInfoImpl : public ConverterInfo
	{
	public:
		typedef std::function<TOut(const TIn&)> Func;

		explicit ConverterInfoImpl(Func function)
			: _function(function)
		{}

		virtual const Type* GetResultType() const override
		{
			return TypeOf<TOut>();
		}

		virtual bool Convert(const ValueType& source, ValueType& result) const override
		{
			auto in = (const TIn*)&source;
			auto out = (TOut*)&result;

			*out = _function(*in);
			return true;
		}

	protected:
		Func _function;
	};

	//////////////////////////////////////////////////////////////////////////
	template<typename TIn, typename TOut>
	class DefaultConverterInfo : public ConverterInfo
	{
	public:
		virtual const Type* GetResultType() const override
		{
			return TypeOf<TOut>();
		}

		virtual bool Convert(const ValueType& source, ValueType& result) const override
		{
			auto in = (const TIn*)&source;
			auto out = (TOut*)&result;

			*out = (TOut)*in;
			return true;
		}
	};

#define UUT_REGISTER_CONVERTER_DEFAULT(type) internalType->AddMember(new DefaultConverterInfo<ClassName, type>());
#define UUT_REGISTER_CONVERTER_FUNC(type, func) \
	internalType->AddMember(new ConverterInfoImpl<ClassName, type>(bind(&ClassName::func, std::placeholders::_1)));
}