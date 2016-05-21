#pragma once
#include "Stream.h"

namespace uut
{
	class MemoryStream : public Stream
	{
		UUT_OBJECT(MemoryStream, Stream)
	public:
		MemoryStream();
		virtual ~MemoryStream();

		bool Open(const void* data, unsigned size, bool freeData = false);
		void Close();

		virtual bool CanRead() const override;
		virtual bool CanWrite() const override;
		virtual bool CanSeek() const override;
		virtual bool IsOpened() const override;
		virtual bool IsEOF() const override;
		virtual const Path& GetPath() const override;

		virtual void SetPosition(unsigned position) override;
		virtual unsigned GetPosition() const override;
		virtual unsigned GetLength() const override;

		virtual int Read(void* buffer, unsigned size) override;
		virtual int Write(const void* buffer, unsigned size) override;

		const uint8_t* GetData() const { return _data; }

	protected:
		const uint8_t* _data;
		bool _owner;
		unsigned _position;
		unsigned _size;
	};
}