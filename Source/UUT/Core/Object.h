#pragma once
#include "Core/IEquatable.h"
#include "Core/String.h"
#include "Core/Ptr.h"

namespace uut
{
	class Object : public IEquatable, public RefCounted
	{
	public:
		virtual ~Object() {}

		virtual bool Equals(const Object* obj) const override;
		virtual String ToString();
	};
}