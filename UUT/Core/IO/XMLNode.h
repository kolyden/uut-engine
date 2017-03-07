#pragma once
#include <Core/ValueType.h>
#include <Core/String.h>
#include <TinyXML2/tinyxml2.h>

namespace uut
{
	class XMLAttribute
	{
	public:
		XMLAttribute() : _data(nullptr) {}
		XMLAttribute(const tinyxml2::XMLAttribute* data) : _data(data) {}

		String GetName() const { return _data ? _data->Name() : String::Empty; }
		String GetValue() const { return _data ? _data->Value() : String::Empty; }

		bool Valid() const { return _data != nullptr; }

		XMLAttribute Next()
		{
			return XMLAttribute(_data ? _data->Next() : nullptr);
		}

		bool operator == (const XMLAttribute& attr) const { return _data == attr._data; }
		bool operator != (const XMLAttribute& attr) const { return _data != attr._data; }

		static const XMLAttribute Empty;

	protected:
		const tinyxml2::XMLAttribute* _data;
	};

	class XMLNode : public ValueType
	{
		UUT_VALUETYPE(uut, XMLNode, ValueType)
	public:
		XMLNode();
		XMLNode(tinyxml2::XMLElement* node);

		bool Valid() const;

		void SetName(const String& name);
		String GetName() const;

		void SetText(const String& text);
		String GetText() const;

		XMLNode Find(const String& name);
		const XMLNode Find(const String& name) const;

		XMLNode Begin();
		const XMLNode Begin() const;

		XMLNode End();
		const XMLNode End() const;

		XMLAttribute FirstAttribute();
		const XMLAttribute FirstAttribute() const;

		bool operator == (const XMLNode& node) const;
		bool operator != (const XMLNode& node) const;

		static const XMLNode Empty;

	protected:
		tinyxml2::XMLElement* _data;
	};
}