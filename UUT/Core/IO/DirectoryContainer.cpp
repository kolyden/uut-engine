#include "DirectoryContainer.h"
#include "Directory.h"
#include "FileStream.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(DirectoryContainer)
	{}

	DirectoryContainer::DirectoryContainer(const Path& directory)
		: _directory(directory)
	{
	}

	SharedPtr<Stream> DirectoryContainer::Open(const Path& path, FileMode mode)
	{
		return FileStream::OpenStatic(Path::Combine(_directory, path), mode);
	}

	bool DirectoryContainer::Exist(const Path& path) const
	{
		return Directory::Exist(Path::Combine(_directory, path));
	}
}