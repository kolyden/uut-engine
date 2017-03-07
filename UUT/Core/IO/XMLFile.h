#pragma once
#include <Resources/Resource.h>
#include "XMLNode.h"

namespace uut
{
	class XMLFile : public Resource
	{
		UUT_OBJECT(uut, XMLFile, Resource)
	public:
		XMLFile();
		XMLFile(const String& xml);

		XMLNode GetRoot();

	protected:
		tinyxml2::XMLDocument _document;
	};
}