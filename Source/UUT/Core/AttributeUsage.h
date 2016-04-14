#pragma once
#include "Attribute.h"

namespace uut
{
	enum class AttributeTarget
	{
		Method,
	};

	class AttributeUsage : public Attribute
	{
	public:

	protected:
		AttributeTarget _targets;
		bool _allowMultiple;
		bool _inherited;
	};
}
