#include "MemoryStream.h"
#include <Core/Math/Math.h>

namespace uut
{
	UUT_OBJECT_IMPLEMENT(MemoryStream)
	{}

	MemoryStream::MemoryStream()
		: _data(nullptr)
		, _owner(false)
		, _position(0)
		, _size(0)
	{
	}

	MemoryStream::~MemoryStream()
	{
		Close();
	}

	bool MemoryStream::Open(const void* data, unsigned size, bool freeData /*= false*/)
	{
		Close();

		if (data == nullptr || size == 0)
			return false;

		_data = (uint8_t*)data;
		_owner = freeData;
		_size = size;
		_position = 0;
		return true;
	}

	void MemoryStream::Close()
	{
		if (!IsOpened())
			return;

		if (_owner)
			delete[] _data;
		_data = nullptr;
		_position = 0;
		_size = 0;
	}

	bool MemoryStream::CanRead() const
	{
		return IsOpened();
	}

	bool MemoryStream::CanWrite() const
	{
		return false;
	}

	bool MemoryStream::CanSeek() const
	{
		return IsOpened();
	}

	bool MemoryStream::IsOpened() const
	{
		return _data != nullptr;
	}

	bool MemoryStream::IsEOF() const
	{
		return !IsOpened() || _position >= _size;
	}

	void MemoryStream::SetPosition(unsigned position)
	{
		if (IsOpened())
			_position = Math::Min(position, _size - 1);
	}

	unsigned MemoryStream::GetPosition() const
	{
		return _position;
	}

	unsigned MemoryStream::GetLength() const
	{
		return _size;
	}

	int MemoryStream::Read(void* buffer, unsigned size)
	{
		if (!CanRead())
			return 0;

		const auto count = Math::Min(size, _size - _position);
		memcpy(buffer, &_data[_position], count);
		return count;
	}

	int MemoryStream::Write(const void* buffer, unsigned size)
	{
		return 0;
	}
}