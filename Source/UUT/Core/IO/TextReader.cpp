#include "TextReader.h"
#include "Stream.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(TextReader)
	{}

	TextReader::TextReader(Stream* source)
	{
		if (source != nullptr && source->CanRead())
			_source = source;
	}

	TextReader::~TextReader()
	{		
	}

	unsigned TextReader::Read(char* buffer, unsigned count) const
	{
		if (!_source || count == 0 || buffer == nullptr)
			return 0;

		unsigned pos = 0;
		for (unsigned i = 0; i < count; i++)
		{
			char c;
			if (_source->Read(&c, 1) != 1)
				break;

			if (c == 13) continue;
			if (c == '\n') break;

			buffer[pos++] = c;
		}

		return pos;
	}

	bool TextReader::ReadLine(String& line) const
	{
		if (!_source)
			return 0;

		unsigned pos = 0;
		char c;
		int total = 0;
		while (_source->Read(&c, 1) == 1)
		{
			if (c == 13) continue;
			if (c == '\n') break;

			line += c;
			total++;
		}

		return total > 0;
	}

	bool TextReader::ReadToEnd(String& str) const
	{
		if (!_source || !_source->CanRead())
			return false;

		const unsigned int size = _source->GetLength();
		char* buf = new char[size + 1];
		_source->Read(buf, size);
		buf[size] = 0;

		str = buf;
		delete[] buf;

		return true;
	}

	bool TextReader::IsEOF() const
	{
		return _source ? _source->IsEOF() : true;
	}
}