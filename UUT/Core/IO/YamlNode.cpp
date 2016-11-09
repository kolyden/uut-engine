#include "YamlNode.h"
#include "YamlFile.h"
#include "YamlSerializer.h"

namespace uut
{
	UUT_VALUETYPE_IMPLEMENT(YamlNode)
	{}

	const YamlNode YamlNode::Empty;

	YamlNode::YamlNode()
		: _index(0)
	{
	}

	YamlNode::YamlNode(int index, const SharedPtr<YamlFile>& document)
		: _index(index)
		, _yaml(document)
	{
	}

// 	yaml_node_t* YamlNode::Node() const
// 	{
// 		if (auto yaml = _yaml.Lock())
// 			return yaml_document_get_node(yaml->GetDocument(), _index);
// 
// 		return nullptr;
// 	}

	String YamlNode::Scalar() const
	{
		if (auto yaml = _yaml.Lock())
		{
			auto node = yaml_document_get_node(yaml->GetDocument(), _index);
			if (node->type == YAML_SCALAR_NODE)
				return (const char*)node->data.scalar.value;
		}

		return String::Empty;
	}

	YamlType YamlNode::NodeType() const
	{
		if (auto yaml = _yaml.Lock())
		{
			auto node = yaml_document_get_node(yaml->GetDocument(), _index);
			if (node)
			{
				switch (node->type)
				{
				case YAML_SCALAR_NODE: return YamlType::Scalar;
				case YAML_SEQUENCE_NODE: return YamlType::Sequence;
				case YAML_MAPPING_NODE: return YamlType::Mapping;
				}
			}
		}

		return YamlType::Null;
	}

	String YamlNode::Tag() const
	{
		if (auto yaml = _yaml.Lock())
		{
			auto node = yaml_document_get_node(yaml->GetDocument(), _index);
			return node != 0 && node->tag != 0 ? String((char*)node->tag) : String::Empty;
		}

		return String::Empty;
	}

	SharedPtr<YamlFile> YamlNode::Document() const
	{
		return _yaml.Lock();
	}

	/*void YamlNode::SetScalarStyle(yaml_scalar_style_e style)
	{
		auto node = Node();
		if (node && node->type == YAML_SCALAR_NODE)
			node->data.scalar.style = style;
	}

	yaml_scalar_style_e YamlNode::GetScalarStyle() const
	{
		auto node = Node();
		return node && node->type == YAML_SCALAR_NODE ? node->data.scalar.style : YAML_ANY_SCALAR_STYLE;
	}

	void YamlNode::SetSequenceStyle(yaml_sequence_style_e style)
	{
		auto node = Node();
		if (node && node->type == YAML_SEQUENCE_NODE)
			node->data.sequence.style = style;
	}

	yaml_sequence_style_e YamlNode::GetSequenceStyle() const
	{
		auto node = Node();
		return node && node->type == YAML_SCALAR_NODE ? node->data.sequence.style : YAML_ANY_SEQUENCE_STYLE;
	}

	void YamlNode::SetMappingStyle(yaml_mapping_style_e style)
	{
		auto node = Node();
		if (node && node->type == YAML_MAPPING_NODE)
			node->data.mapping.style = style;
	}

	yaml_mapping_style_e YamlNode::GetMappingStyle() const
	{
		auto node = Node();
		return node && node->type == YAML_MAPPING_NODE ? node->data.mapping.style : YAML_ANY_MAPPING_STYLE;
	}*/

	String YamlNode::ToString() const
	{
		return Scalar();
	}

	int YamlNode::ToInt() const
	{
		return Int32::Parse(Scalar());
	}

	float YamlNode::ToFloat() const
	{
		return (float)atof(Scalar());
	}

	bool YamlNode::ToBool() const
	{
		return ToInt() > 0;
	}

	int YamlNode::Count() const
	{
		if (auto yaml = _yaml.Lock())
		{
			auto node = yaml_document_get_node(yaml->GetDocument(), _index);
			if (node->type == YAML_SEQUENCE_NODE)
				return node->data.sequence.items.top - node->data.sequence.items.start;
		}

		return 0;
	}

	YamlNode YamlNode::GetAt(int index) const
	{
		if (auto yaml = _yaml.Lock())
		{
			auto node = yaml_document_get_node(yaml->GetDocument(), _index);
			if (!node || node->type != YAML_SEQUENCE_NODE)
				return Empty;

			if (index >= 0 && index < node->data.sequence.items.top - node->data.sequence.items.start)
				return YamlNode(node->data.sequence.items.start[index], _yaml.Lock());
		}

		return Empty;
	}

	YamlNode YamlNode::Get(const char* name) const
	{
		if (!name)
			return Empty;

		if (auto yaml = _yaml.Lock())
		{
			auto node = yaml_document_get_node(yaml->GetDocument(), _index);
			if (!node || node->type != YAML_MAPPING_NODE)
				return Empty;

			for (auto it = node->data.mapping.pairs.start; it < node->data.mapping.pairs.top; it++)
			{
				auto child = yaml_document_get_node(yaml->GetDocument(), it->key);
				if (child->type != YAML_SCALAR_NODE)
					continue;

				if (String::Compare((char*)child->data.scalar.value, name, StringComparison::OrdinalIgnoreCase) != 0)
					continue;

				return YamlNode(it->value, yaml);
			}
		}

		return Empty;
	}

	void YamlNode::GetKeys(List<HashString>& keys) const
	{
		if (auto yaml = _yaml.Lock())
		{
			auto node = yaml_document_get_node(yaml->GetDocument(), _index);
			if (!node || node->type != YAML_MAPPING_NODE)
				return;

			for (auto it = node->data.mapping.pairs.start; it < node->data.mapping.pairs.top; it++)
			{
				auto child = yaml_document_get_node(yaml->GetDocument(), it->key);
				if (child->type != YAML_SCALAR_NODE)
					continue;

				keys << (char*)child->data.scalar.value;
			}
		}
	}

	YamlNode YamlNode::AppendSequence(const YamlNode& item)
	{
		if (item.IsNull())
			return Empty;

		if (auto yaml = _yaml.Lock())
		{
			auto node = yaml_document_get_node(yaml->GetDocument(), _index);
			if (!node || node->type != YAML_SEQUENCE_NODE)
				return YamlNode::Empty;

			if (!yaml_document_append_sequence_item(yaml->GetDocument(), _index, item._index))
				return Empty;

			return item;
		}

		return Empty;
	}

	YamlNode YamlNode::AppendSequence(const Variant& data)
	{
		return AppendSequence(YamlSerializer::SerializeVariant(Document(), data));
	}

	YamlNode YamlNode::AppendMapping(const char* key, const YamlNode& item)
	{
		if (!key || item.IsNull())
			return Empty;

		if (auto yaml = _yaml.Lock())
		{
			auto node = yaml_document_get_node(yaml->GetDocument(), _index);
			if (!node || node->type != YAML_MAPPING_NODE)
				return Empty;

			const int keyIndex = yaml_document_add_scalar(yaml->GetDocument(),
				NULL, (yaml_char_t*)key, strlen(key), YAML_PLAIN_SCALAR_STYLE);
			if (keyIndex < 1)
				return YamlNode::Empty;

			if (!yaml_document_append_mapping_pair(
				yaml->GetDocument(), _index, keyIndex, item._index))
				return Empty;

			return item;
		}

		return Empty;
	}

	YamlNode YamlNode::AppendMapping(const char* key, const Variant& data)
	{
		if (!key)
			return Empty;

		return AppendMapping(key, YamlSerializer::SerializeVariant(Document(), data));
	}

// 	YamlNode YamlNode::AppendSequence(const engVariant& data)
// 	{
// 		if (!data.is_valid())
// 			return YamlNode::Empty;
// 
// 		auto node = Node();
// 		if (!node || node->type != YAML_SEQUENCE_NODE)
// 			return YamlNode::Empty;
// 
// 		auto item = _yaml->AddVariant(data);
// 		if (!yaml_document_append_sequence_item(
// 			_yaml->GetDocument(), _index, item._index))
// 			return YamlNode::Empty;
// 
// 		return item;
// 	}
// 
// 	YamlNode YamlNode::AppendMapping(const char* key, const engVariant& data)
// 	{
// 		if (!key || !data.is_valid())
// 			return YamlNode::Empty;
// 
// 		auto node = Node();
// 		if (!node || node->type != YAML_MAPPING_NODE)
// 			return YamlNode::Empty;
// 
// 		const int keyIndex = yaml_document_add_scalar(_yaml->GetDocument(),
// 			NULL, (yaml_char_t*)key, strlen(key), YAML_PLAIN_SCALAR_STYLE);
// 		if (keyIndex < 1)
// 			return YamlNode::Empty;
// 
// 		auto item = _yaml->AddVariant(data);
// 		if (!yaml_document_append_mapping_pair(
// 			_yaml->GetDocument(), _index, keyIndex, item._index))
// 			return YamlNode::Empty;
// 
// 		return item;
// 	}
}