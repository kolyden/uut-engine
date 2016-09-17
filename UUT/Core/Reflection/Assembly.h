#pragma once
#include <Core/IO/Path.h>

namespace uut
{
	class Assembly
	{
	public:
		static const Assembly* Load(const Path& path);
	};
}