#pragma once
#include <stdint.h>
#include <Core/Object.h>

namespace uut
{
	class Stream;

	class BinaryReader : public Object
	{
		UUT_OBJECT(BinaryReader, Object)
	public:
		BinaryReader();
		explicit BinaryReader(Stream* source);

		unsigned ReadBytes(unsigned count, void* buffer) const;
		unsigned ReadBytes(unsigned count, List<uint8_t>& bytes) const;
		unsigned ReadChars(unsigned count, List<char>& chars) const;
		void SkipBytes(unsigned count) const;

		bool ReadBoolean() const;
		String ReadStringNT() const;

		int8_t  ReadInt8() const;
		int16_t ReadInt16() const;
		int32_t ReadInt32() const;
		int64_t ReadInt64() const;

		uint8_t  ReadUint8() const;
		uint16_t ReadUint16() const;
		uint32_t ReadUint32() const;
		uint64_t ReadUint64() const;

		bool IsEOF() const;

	protected:
		SharedPtr<Stream> _source;
	};
}