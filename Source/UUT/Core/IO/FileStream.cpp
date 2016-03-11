#include "FileStream.h"

namespace uut
{
	FileStream::FileStream()
		: _handle(nullptr)
	{
	}

	FileStream::~FileStream()
	{
		Close();
	}

	bool FileStream::Open(const Path& path, FileMode mode)
	{
		Close();

		switch (mode)
		{
		case FileMode::OpenRead:
			_handle = SDL_RWFromFile(path.ToUtf8(), "r");
			break;

		case FileMode::Create:
			_handle = SDL_RWFromFile(path.ToUtf8(), "w");
			break;

		case FileMode::Append:
			_handle = SDL_RWFromFile(path.ToUtf8(), "a");
			break;
		}

		if (_handle == nullptr)
			return false;

		_fileMode = mode;
		return true;
	}

	void FileStream::Close()
	{
		if (_handle == nullptr)
			return;

		SDL_RWclose(_handle);
		_handle = nullptr;
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
}