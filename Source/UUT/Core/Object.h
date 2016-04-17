#pragma once
#include <Core/IEquatable.h>
#include <Core/String.h>
#include <Core/Reflection/Type.h>
#include "RefCounted.h"

namespace uut
{
	class Object : public IEquatable, public RefCounted
	{
		UUT_OBJECT(Object, Object)
	public:
		virtual ~Object() {}

		virtual bool Equals(const Object* obj) const override;
		virtual String ToString();
	};
}