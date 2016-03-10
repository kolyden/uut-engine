#pragma once
#include "Core/Object.h"

namespace uut
{
	enum class SeekMethod
	{
		Begin,
		Current,
		End,
	};

	class Stream : public Object
	{
	public:
		virtual bool CanRead() const = 0;
		virtual bool CanWrite() const = 0;
		virtual bool CanSeek() const = 0;
		virtual bool IsOpened() const = 0;
		virtual bool IsEOF() const = 0;

		virtual void SetPosition(unsigned position) = 0;
		virtual unsigned GetPosition() const = 0;
		virtual unsigned GetLength() const = 0;

		bool Seek(SeekMethod method, int offset);

		virtual int Read(void* buffer, unsigned size) = 0;
		virtual int Write(const void* buffer, unsigned size) = 0;
	};
}