#include "File.h"
#include "FileStream.h"
#include <Windows.h>

namespace uut
{
	bool File::Exists(const Path& path)
	{
		auto ret = ::GetFileAttributesA(path.ToUtf8());
		if (ret == INVALID_FILE_ATTRIBUTES)
			return false;

		return (ret & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY;
	}

	SharedPtr<FileStream> File::Open(const Path& path, FileMode mode)
	{
		auto stream = SharedPtr<FileStream>(new FileStream());
		if (stream->Open(path, mode))
			return stream;

		return SharedPtr<FileStream>::Empty;
	}

	SharedPtr<FileStream> File::OpenRead(const Path& path)
	{
		return Open(path, FileMode::OpenRead);
	}

	SharedPtr<FileStream> File::OpenWrite(const Path& path)
	{
		return Open(path, FileMode::Create);
	}

// 	SharedPtr<BinaryData> File::ReadAllBytes(const Path& path)
// 	{
// 		auto stream = OpenRead(path);
// 		if (!stream)
// 			return SharedPtr<BinaryData>::Empty;
// 
// 		const unsigned size = stream->GetLength();
// 		if (size == 0)
// 			return SharedPtr<BinaryData>::Empty;
// 
// 		auto data = SharedPtr<BinaryData>::Make();
// 		data->Alloc(size);
// 		stream->Read(data->GetRawPtr(), size);
// 
// 		return data;
// 	}

	List<String> File::ReadAllLines(const Path& path)
	{
// 		auto stream = OpenRead(path);
// 		if (!stream)
			return List<String>::Empty;

// 		auto reader = SharedPtr<TextReader>::Make(stream);
	}
}