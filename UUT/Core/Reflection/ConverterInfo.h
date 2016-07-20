#pragma once
#include "MemberInfo.h"
#include "FunctionUtils.h"

namespace uut
{
	class IConverterInfo : public IMemberInfo
	{
	public:
		virtual MemberType GetMemberType() const override;
		virtual const String& GetName() const override;

		virtual const Type* GetResultType() const = 0;
		virtual bool Convert(const ValueType& source, ValueType& result) const = 0;
	};

	//////////////////////////////////////////////////////////////////////////
	template<typename TIn, typename TOut>
	class ConverterInfo : public IConverterInfo
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

	//////////////////////////////////////////////////////////////////////////
	template<typename TIn, typename TOut>
	class ConverterInfoFunc : public IConverterInfo
	{
	public:
		typedef std::function<TOut(const TIn&)> Func;

		explicit ConverterInfoFunc(Func function)
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

#define UUT_REGISTER_CONVERTER_DEFAULT(type) internalType->AddMember(new ConverterInfo<ClassName, type>());
#define UUT_REGISTER_CONVERTER_FUNC(type, func) \
	internalType->AddMember(new ConverterInfoFunc<ClassName, type>(bind(&ClassName::func, std::placeholders::_1)));
}