#pragma once
#include <Core/Object.h>

namespace uut
{
	class BaseTest : public Object
	{
		UUT_OBJECT(BaseTest, Object)
	public:
		BaseTest();
	};
}