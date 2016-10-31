#include "JSONFile.h"
#include <Core/IO/Stream.h>

namespace uut
{
	JsonNode::JsonNode() : _node(0) {}

	JsonNode::JsonNode(JSONNODE* node)
		: _node(node)
	{
	}

	int JsonNode::Type() const
	{
		return _node != 0 ? json_type(_node) : JSON_NULL;
	}

	int JsonNode::Count() const
	{
		return _node != 0 ? json_size(_node) : 0;
	}

	JsonNode JsonNode::GetAt(int index) const
	{
		return _node != 0 ? JsonNode(json_at(_node, index)) : JsonNode();
	}

	JsonNode JsonNode::Get(const String& name) const
	{
		return _node != 0 ? JsonNode(json_get(_node, name)) : JsonNode();
	}

	String JsonNode::ToString() const
	{
		return _node != 0 ? json_as_string(_node) : String::Empty;
	}

	int JsonNode::ToInt() const
	{
		return _node != 0 ? json_as_int(_node) : 0;
	}

	float JsonNode::ToFloat() const
	{
		return _node != 0 ? json_as_float(_node) : 0;
	}

	bool JsonNode::ToBool() const
	{
		return _node != 0 ? (json_as_bool(_node) != 0) : false;
	}

	int JsonNode::ToEnum(const char* types[], int count, int defVal /* = -1 */) const
	{
		const String str = ToString();
		if (str.IsEmpty())
			return defVal;

		for (int i = 0; i < count; i++)
		{
			if (String::Compare(str, types[i], StringComparison::OrdinalIgnoreCase) == 0)
				return i;
		}

		return defVal;
	}

	//////////////////////////////////////////////////////////////////////////
	UUT_OBJECT_IMPLEMENT(JsonFile)
	{
	}

	JsonFile::JsonFile()
		: _root(0)
	{
	}

	JsonFile::~JsonFile()
	{
		Clear();
	}

	void JsonFile::Clear()
	{
		if (_data == 0)
			return;

		json_free(_data);
		_data = 0;
		_root = JsonNode();
	}

	const JsonNode& JsonFile::GetRoot() const
	{
		return _root;
	}

	//////////////////////////////////////////////////////////////////////////
	UUT_OBJECT_IMPLEMENT(JsonFileLoader)
	{
	}

	SharedPtr<Resource> JsonFileLoader::Load(const SharedPtr<Stream>& stream)
	{
		const int size = stream->GetLength();
		if (size == 0)
			return nullptr;

		char* buffer = new char[size + 1];
		if (stream->Read(buffer, size) != size)
		{
			delete[] buffer;
			return nullptr;
		}

		buffer[size] = 0;

		auto json = SharedPtr<JsonFile>::Make();
		json->_data = json_parse(buffer);
		json->_root = JsonNode(json->_data);
		delete[] buffer;

		return DynamicCast<Resource>(json);
	}
}