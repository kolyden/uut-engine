#include "XMLNode.h"

namespace uut
{
	const XMLNode XMLNode::Empty;

	UUT_VALUETYPE_IMPLEMENT(XMLNode)
	{}

	XMLNode::XMLNode()
		: _data(nullptr)
	{
	}

	XMLNode::XMLNode(tinyxml2::XMLElement* node)
		: _data(node)
	{
	}

	bool XMLNode::Valid() const
	{
		return _data != nullptr;
	}

	void XMLNode::SetName(const String& name)
	{
		if (_data) _data->SetName(name);
	}

	String XMLNode::GetName() const
	{
		return _data ? _data->Name() : String::Empty;
	}

	void XMLNode::SetText(const String& text)
	{
		if (_data) _data->SetText(text);
	}

	String XMLNode::GetText() const
	{
		return _data ? _data->GetText() : String::Empty;
	}

	XMLNode XMLNode::Find(const String& name)
	{
		return _data ? XMLNode(_data->FirstChildElement(name)) : Empty;
	}

	const XMLNode XMLNode::Find(const String& name) const
	{
		return _data ? XMLNode(_data->FirstChildElement(name)) : Empty;
	}

	XMLNode XMLNode::Begin()
	{
		return _data ? XMLNode(_data->FirstChildElement()) : Empty;
	}

	const XMLNode XMLNode::Begin() const
	{
		return _data ? XMLNode(_data->FirstChildElement()) : Empty;
	}

	XMLNode XMLNode::End()
	{
		return _data ? XMLNode(_data->LastChildElement()) : Empty;
	}

	const XMLNode XMLNode::End() const
	{
		return _data ? XMLNode(_data->LastChildElement()) : Empty;
	}

	XMLAttribute XMLNode::FirstAttribute()
	{
		return _data ? XMLAttribute(_data->FirstAttribute()) : XMLAttribute::Empty;
	}

	const XMLAttribute XMLNode::FirstAttribute() const
	{
		return _data ? XMLAttribute(_data->FirstAttribute()) : XMLAttribute::Empty;
	}

	bool XMLNode::operator==(const XMLNode& node) const
	{
		return _data == node._data;
	}

	bool XMLNode::operator!=(const XMLNode& node) const
	{
		return _data != node._data;
	}

	const XMLAttribute XMLAttribute::Empty;
}