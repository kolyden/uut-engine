#include "XMLFileLoader.h"
#include "XMLFile.h"
#include "TextReader.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(XMLFileLoader)
	{}

	SharedPtr<Resource> XMLFileLoader::Load(const SharedPtr<Stream>& stream)
	{
		auto reader = SharedPtr<TextReader>::Make(stream);

		String xml, line;
		while (!reader->IsEOF())
		{
			line.Clear();
			reader->ReadLine(line);
			xml += line;
		}

		return SharedPtr<XMLFile>::Make(xml);
	}

	const Type* XMLFileLoader::GetResourceType() const
	{
		return XMLFile::GetTypeStatic();
	}
}