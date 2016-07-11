#pragma once
#include <Core/Object.h>

namespace uut
{
	class Stream;

	class TextReader : public Object
	{
		UUT_OBJECT(TextReader, Object)
	public:
		explicit TextReader(const SharedPtr<Stream>& source);
		virtual ~TextReader();

// 		wchar_t Read();
		unsigned Read(char* buffer, unsigned count) const;
		bool ReadLine(String& line) const;
		bool ReadToEnd(String& str) const;

		bool IsEOF() const;

	protected:
		SharedPtr<Stream> _source;
	};
}
