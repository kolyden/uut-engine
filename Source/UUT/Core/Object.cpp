#include "Object.h"

namespace uut
{
// 	UUT_OBJECT_IMPLEMENT(Object)
// 	{}

	uut::Type& Object::GetTypeInternal()
	{
		static uut::Type t(TypeInfo::Class, "Object", nullptr, &Object::_RegisterInternal); return t;
	}
	void Object::_RegisterInternal()
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