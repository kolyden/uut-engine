#pragma once
#include "Stream.h"
#include "FileMode.h"
#include "Path.h"

namespace uut
{
	class FileStream : public Stream
	{
	public:
		FileStream();
		virtual ~FileStream();

		bool Open(const Path& path, FileMode mode);
		void Close();

		virtual bool CanRead() const override;
		virtual bool CanWrite() const override;
		virtual bool CanSeek() const override;
		virtual bool IsOpened() const override;
		virtual bool IsEOF() const override;

		virtual void SetPosition(unsigned position) override;
		virtual unsigned GetPosition() const override;
		virtual unsigned GetLength() const override;

		virtual int Read(void* buffer, unsigned size) override;
		virtual int Write(const void* buffer, unsigned size) override;

	protected:
		SDL_RWops* _handle;
		FileMode _fileMode;
	};
}