#include "FileStream.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(FileStream)
	{}

	FileStream::FileStream()
		: _handle(nullptr)
		, _fileMode(FileMode::OpenRead)
	{
	}

	FileStream::~FileStream()
	{
		Close();
	}

	bool FileStream::Open(const Path& path, FileMode mode)
	{
		Close();

		String fullPath = path.GetFullPath();
		switch (mode)
		{
		case FileMode::OpenRead:
			_handle = SDL_RWFromFile(fullPath, "rb");
			break;

		case FileMode::Create:
			_handle = SDL_RWFromFile(fullPath, "wb");
			break;

		case FileMode::Append:
			_handle = SDL_RWFromFile(fullPath, "ab");
			break;
		}

		if (_handle == nullptr)
			return false;

		_path = path;
		_fileMode = mode;
		return true;
	}

	void FileStream::Close()
	{
		if (_handle == nullptr)
			return;

		SDL_RWclose(_handle);
		_handle = nullptr;
		_path = Path::Empty;
	}


	bool FileStream::CanRead() const
	{
		return IsOpened();
	}

	bool FileStream::CanWrite() const
	{
		return IsOpened() && _fileMode != FileMode::OpenRead;
	}

	bool FileStream::CanSeek() const
	{
		return IsOpened();
	}

	bool FileStream::IsOpened() const
	{
		return _handle != nullptr;
	}

	bool FileStream::IsEOF() const
	{
		if (!IsOpened())
			return true;

		return GetPosition() == GetLength();
	}

	const Path& FileStream::GetPath() const
	{
		return _path;
	}

	void FileStream::SetPosition(unsigned position)
	{
		if (IsOpened())
			SDL_RWseek(_handle, position, RW_SEEK_SET);
	}

	unsigned FileStream::GetPosition() const
	{
		if (!IsOpened())
			return 0;

		auto ret = SDL_RWtell(_handle);
		return ret >= 0 ? static_cast<unsigned int>(ret) : 0;
	}

	unsigned FileStream::GetLength() const
	{
		if (!IsOpened())
			return 0;

		auto ret = SDL_RWsize(_handle);
		return ret >= 0 ? static_cast<unsigned int>(ret) : 0;
	}

	int FileStream::Read(void* buffer, unsigned size)
	{
		if (!CanRead())
			return 0;

		return SDL_RWread(_handle, buffer, 1, size);
	}

	int FileStream::Write(const void* buffer, unsigned size)
	{
		if (!CanWrite())
			return 0;

		return SDL_RWwrite(_handle, buffer, 1, size);
	}

	SharedPtr<FileStream> FileStream::OpenStatic(const Path& path, FileMode mode)
	{
		String fullPath = path.GetFullPath();
		SDL_RWops* handle = nullptr;
		switch (mode)
		{
		case FileMode::OpenRead:
			handle = SDL_RWFromFile(fullPath, "rb");
			break;

		case FileMode::Create:
			handle = SDL_RWFromFile(fullPath, "wb");
			break;

		case FileMode::Append:
			handle = SDL_RWFromFile(fullPath, "ab");
			break;
		}

		if (handle == nullptr)
			return nullptr;

		auto file = MakeShared<FileStream>();
		file->_handle = handle;
		file->_path = path;
		file->_fileMode = mode;
		return file;
	}
}