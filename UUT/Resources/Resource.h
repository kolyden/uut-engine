#pragma once
#include <Core/Object.h>

namespace uut
{
	class Resource : public Object
	{
		UUT_OBJECT(Resource, Object)
	public:
		Resource();
		virtual ~Resource();
	};
}