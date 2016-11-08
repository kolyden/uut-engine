#pragma once
#include <Core/ValueType.h>
#include <Core/Collections/List.h>
#include <Core/HashString.h>
#include <Core/Variant.h>
#include <LibYAML/yaml.h>

namespace uut
{
	enum class YamlType
	{
		Null,
		Scalar,
		Sequence,
		Mapping,
	};

	class YamlFile;

	class YamlNode : public ValueType
	{
		UUT_VALUETYPE(uut, YamlNode, ValueType)
	public:
		YamlNode();
		YamlNode(int index, const SharedPtr<YamlFile>& document);

// 		yaml_node_t* Node() const;
		String Scalar() const;
		YamlType NodeType() const;
		String Tag() const;
		SharedPtr<YamlFile> Document() const;

// 		void SetScalarStyle(yaml_scalar_style_e style);
// 		yaml_scalar_style_e GetScalarStyle() const;
// 
// 		void SetSequenceStyle(yaml_sequence_style_e style);
// 		yaml_sequence_style_e GetSequenceStyle() const;
// 
// 		void SetMappingStyle(yaml_mapping_style_e style);
// 		yaml_mapping_style_e GetMappingStyle() const;

		inline bool IsNull() const { return NodeType() == YamlType::Null; }
		inline bool IsScalar() const { return NodeType() == YamlType::Scalar; }
		inline bool IsSequence() const { return NodeType() == YamlType::Sequence; }
		inline bool IsMapping() const { return NodeType() == YamlType::Mapping; }

		String ToString() const;
		int ToInt() const;
		float ToFloat() const;
		bool ToBool() const;

		int Count() const;
		YamlNode GetAt(int index) const;
		YamlNode Get(const char* name) const;
		void GetKeys(List<HashString>& keys) const;

		YamlNode operator[](const char* name) const { return Get(name); }

		YamlNode AppendSequence(const YamlNode& item);
		YamlNode AppendSequence(const Variant& data);

		YamlNode AppendMapping(const char* key, const YamlNode& item);
		YamlNode AppendMapping(const char* key, const Variant& data);

		static const YamlNode Empty;

	protected:
		int _index;
		WeakPtr<YamlFile> _yaml;
	};
}