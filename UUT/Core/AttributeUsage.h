#pragma once
#include <Core/Attribute.h>
#include <Core/EnumFlags.h>

namespace uut
{
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

	class AttributeUsage : public Attribute
	{
		UUT_OBJECT(uut, AttributeUsage, Attribute)
	public:
		explicit AttributeUsage(AttributeTargets targets, bool allowMultiple = false, bool inherited = true);

		const AttributeTargets& GetTargets() const { return _targets; }
		bool IsAllowMultiple() const { return _allowMultiple; }
		bool IsInherited() const { return _inherited; }

		String ToString() override;

	protected:
		AttributeTargets _targets;
		bool _allowMultiple;
		bool _inherited;
	};
}