#pragma once
#include <Core/Object.h>
#include "Path.h"
#include "FileMode.h"

namespace uut
{
	class Stream;

	class StreamContainer : public Object
	{
		UUT_OBJECT(uut, StreamContainer, Object)
	public:
		virtual SharedPtr<Stream> Open(const Path& path, FileMode mode) = 0;
		virtual bool Exist(const Path& path) const = 0;
	};
}