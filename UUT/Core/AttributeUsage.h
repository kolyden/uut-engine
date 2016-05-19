#pragma once
#include <Core/Attribute.h>

namespace uut
{
	enum class AttributeTarget
	{
		Method = 1,
		Class = 2,
		Property = 4,
		Event = 8,
		Attribute = 16,
		All = Method | Class | Property | Event | Attribute,
	};

	class AttributeUsage : public Attribute
	{
		UUT_OBJECT(AttributeUsage, Attribute)
	public:
		explicit AttributeUsage(AttributeTarget target, bool allowMultiple = false, bool inherited = true);

		bool IsAllowMultiple() const { return _allowMultiple; }
		bool IsInherited() const { return _inherited; }

	protected:
		AttributeTarget _target;
		bool _allowMultiple;
		bool _inherited;
	};
}