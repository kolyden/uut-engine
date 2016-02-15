#include "Object.h"

namespace uut
{
	bool Object::Equals(const Object* obj) const
	{
		return obj == this;
	}

	String Object::ToString()
	{
		return "Object";
	}
}