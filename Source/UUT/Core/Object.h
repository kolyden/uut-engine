#pragma once
#include <Core/IEquatable.h>
#include <Core/String.h>
#include <Core/Reflection/Type.h>
#include "RefCounted.h"

namespace uut
{
#define UUT_OBJECT(typeName, parentType) UUT_TYPE(typeName, parentType)
#define UUT_OBJECT_IMPLEMENT(type) UUT_TYPE_IMPLEMENT(type)

	class Object : public IEquatable, public RefCounted
	{
		UUT_OBJECT(Object, Object)
	public:
		virtual ~Object() {}

		virtual bool Equals(const Object* obj) const override;
		virtual String ToString();
	};
}