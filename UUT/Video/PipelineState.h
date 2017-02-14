#pragma once
#include <Core/Object.h>
#include "PipelineStateDesc.h"

namespace uut
{
	class PipelineState : public Object
	{
		UUT_OBJECT(uut, PipelineState, Object)
	public:

		const PipelineStateDesc& GetDesc() const { return _desc; }

	protected:
		PipelineStateDesc _desc;
	};
}