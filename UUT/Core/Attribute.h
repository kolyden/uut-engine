#pragma once
#include <Core/Object.h>
#include <Core/Collections/Dictionary.h>
#include <Core/EnumFlags.h>
/*
namespace uut
{
#define UUT_ATTRIBUTE_USAGE(targets, allowMultiple) \
	public: \
		const AttributeUsage& GetUsage() const override { return GetUsageStatic(); } \
		static const AttributeUsage& GetUsageStatic() { static AttributeUsage usage(targets, allowMultiple); return usage; } \
	private: \

	enum class AttributeTarget
	{
		None = 0,
		Method = 1,
		Class = 2,
		Property = 4,
		Event = 8,
		Attribute = 16,
		All = Method | Class | Property | Event | Attribute,
	};
	UUT_ENUMFLAG(uut, AttributeTargets, AttributeTarget)

	struct AttributeUsage
	{
		AttributeTargets targets;
		bool allowMultiple;

		constexpr AttributeUsage(AttributeTargets _targets, bool _allowMultiple)
			: targets(_targets)
			, allowMultiple(_allowMultiple)
		{}
	};

	class Attribute : public Object
	{
		UUT_OBJECT(uut, Attribute, Object)
	public:
		virtual const AttributeUsage& GetUsage() const = 0;
	};
}*/