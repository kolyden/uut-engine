#include "XMLFile.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(XMLFile)
	{}

	XMLFile::XMLFile()
	{
	}

	XMLFile::XMLFile(const String& xml)
	{
		_document.Parse(xml, xml.Count());
	}

	XMLNode XMLFile::GetRoot()
	{
		return XMLNode(_document.RootElement());
	}
}