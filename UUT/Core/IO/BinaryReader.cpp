#include "BinaryReader.h"
#include "Stream.h"

namespace uut
{
	template<class T>
	static bool ReadType(Stream* source, T* data)
	{
		if (source == nullptr)
			return false;

		return source->Read(data, sizeof(T)) == sizeof(T);
	}

	UUT_OBJECT_IMPLEMENT(BinaryReader)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	BinaryReader::BinaryReader()
	{
	}

	BinaryReader::BinaryReader(const SharedPtr<Stream>& source)
		: _source(source)
	{
	}

	unsigned BinaryReader::ReadBytes(unsigned count, void* buffer) const
	{
		if (_source == nullptr)
			return 0;

		return _source->Read(buffer, count);
	}

	unsigned BinaryReader::ReadBytes(unsigned count, List<uint8_t>& bytes) const
	{
		if (_source == nullptr)
			return 0;

		unsigned i = 0;
		while (i < count)
		{
			uint8_t b;
			if (_source->Read(&b, 1) != 1)
				return i;

			bytes.Add(b);
			i++;
		}

		return count;
	}

	unsigned BinaryReader::ReadChars(unsigned count, List<char>& chars) const
	{
		if (_source == nullptr)
			return 0;

		unsigned i = 0;
		while (i < count)
		{
			char b;
			if (_source->Read(&b, 1) != 1)
				return i;

			chars.Add(b);
			i++;
		}

		return count;
	}

	void BinaryReader::SkipBytes(unsigned count) const
	{
		if (_source != nullptr)
			_source->Seek(SeekMethod::Current, count);
	}

	bool BinaryReader::ReadBoolean() const
	{
		bool data;
		return ReadType(_source, &data) ? data : false;
	}

	String BinaryReader::ReadStringNT() const
	{
		if (_source == nullptr)
			return String::Empty;

		String ret;
		char c;
		while (_source->Read(&c, 1) == 1)
		{
			if (c == 0)
				break;

			ret += c;
		}

		return ret;
	}

	int8_t BinaryReader::ReadInt8() const
	{
		int8_t data;
		return ReadType(_source, &data) ? data : 0;
	}

	int16_t BinaryReader::ReadInt16() const
	{
		int16_t data;
		return ReadType(_source, &data) ? data : 0;
	}

	int32_t BinaryReader::ReadInt32() const
	{
		int32_t data;
		return ReadType(_source, &data) ? data : 0;
	}

	int64_t BinaryReader::ReadInt64() const
	{
		int64_t data;
		return ReadType(_source, &data) ? data : 0;
	}

	uint8_t  BinaryReader::ReadUint8() const
	{
		uint8_t data;
		return ReadType(_source, &data) ? data : 0;
	}

	uint16_t BinaryReader::ReadUint16() const
	{
		uint16_t data;
		return ReadType(_source, &data) ? data : 0;
	}

	uint32_t BinaryReader::ReadUint32() const
	{
		uint32_t data;
		return ReadType(_source, &data) ? data : 0;
	}

	uint64_t BinaryReader::ReadUint64() const
	{
		uint64_t data;
		return ReadType(_source, &data) ? data : 0;
	}

	bool BinaryReader::IsEOF() const
	{
		if (_source == nullptr)
			return true;

		return _source->IsEOF();
	}
}