#pragma once
#include <Core/Object.h>
#include <Core/IO/Path.h>

namespace uut
{
	class Path;

	enum class SeekMethod
	{
		Begin,
		Current,
		End,
	};

	class Stream : public Object
	{
		UUT_OBJECT(uut, Stream, Object)
	public:
		Stream();
		virtual ~Stream();

		virtual bool CanRead() const = 0;
		virtual bool CanWrite() const = 0;
		virtual bool CanSeek() const = 0;
		virtual bool IsOpened() const = 0;
		virtual bool IsEOF() const = 0;
		virtual const Path& GetPath() const = 0;

		virtual void SetPosition(unsigned position) = 0;
		virtual unsigned GetPosition() const = 0;
		virtual unsigned GetLength() const = 0;

		bool Seek(SeekMethod method, int offset);

		virtual int Read(void* buffer, unsigned size) = 0;
		virtual int Write(const void* buffer, unsigned size) = 0;
	};
}