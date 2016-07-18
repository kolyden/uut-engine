#pragma once
#include "Stream.h"
#include "FileMode.h"
#include "Path.h"

namespace uut
{
	class FileStream : public Stream
	{
		UUT_OBJECT(FileStream, Stream)
	public:
		FileStream();
		virtual ~FileStream();

		bool Open(const Path& path, FileMode mode);
		void Close();

		bool CanRead() const override;
		bool CanWrite() const override;
		bool CanSeek() const override;
		bool IsOpened() const override;
		bool IsEOF() const override;
		const Path& GetPath() const override;

		void SetPosition(unsigned position) override;
		unsigned GetPosition() const override;
		unsigned GetLength() const override;

		int Read(void* buffer, unsigned size) override;
		int Write(const void* buffer, unsigned size) override;

		static SharedPtr<FileStream> OpenStatic(const Path& path, FileMode mode);
		static SharedPtr<FileStream> OpenRead(const Path& path) { return OpenStatic(path, FileMode::OpenRead); }

	protected:
		SDL_RWops* _handle;
		FileMode _fileMode;
		Path _path;
	};
}