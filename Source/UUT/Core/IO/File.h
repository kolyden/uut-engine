#pragma once
#include "FileMode.h"
#include "Path.h"
#include <Core/Ptr.h>

namespace uut
{
	class FileStream;

	class File
	{
	public:
		static bool Exists(const Path& path);

		static SharedPtr<FileStream> Open(const Path& path, FileMode mode);

		static SharedPtr<FileStream> OpenRead(const Path& path);
		static SharedPtr<FileStream> OpenWrite(const Path& path);

// 		static SharedPtr<BinaryData> ReadAllBytes(const Path& path);
		static List<String> ReadAllLines(const Path& path);

	protected:
		File() = delete;
	};
}
