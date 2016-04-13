#include "Object.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(Object)
	{}

	bool Object::Equals(const Object* obj) const
	{
		return obj == this;
	}

	String Object::ToString()
	{
		return GetType()->GetName().GetData();
	}
}