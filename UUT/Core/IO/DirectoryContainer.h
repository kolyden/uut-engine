#pragma once
#include "StreamContainer.h"

namespace uut
{
	class DirectoryContainer : public StreamContainer
	{
		UUT_OBJECT(uut, DirectoryContainer, StreamContainer)
	public:
		explicit DirectoryContainer(const Path& directory);

		SharedPtr<Stream> Open(const Path& path, FileMode mode) override;
		bool Exist(const Path& path) const override;

	protected:
		Path _directory;
	};
}