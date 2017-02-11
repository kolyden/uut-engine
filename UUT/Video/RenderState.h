#pragma once
#include <Core/Object.h>
#include "RenderStateDesc.h"

namespace uut
{
	class RenderState : public Object
	{
		UUT_OBJECT(uut, RenderState, Object)
	public:

		const RenderStateDesc& GetDesc() const { return _desc; }

	protected:
		RenderStateDesc _desc;
	};
}