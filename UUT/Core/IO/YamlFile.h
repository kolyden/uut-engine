#pragma once
#include <Resources/Resource.h>
#include <Resources/ResourceLoader.h>
#include <Resources/ResourceSaver.h>
#include "YamlNode.h"

namespace uut
{
	class YamlFile : public Resource
	{
		UUT_OBJECT(uut, YamlFile, Resource)
	public:
		YamlFile();
		virtual ~YamlFile();

		bool CreateFromString(const char* str, int size);

		YamlNode GetRoot();
		YamlNode GetNode(int index);
		int GetNodeCount() const;

		YamlNode AddScalar(const char* scalar, yaml_scalar_style_e style = YAML_ANY_SCALAR_STYLE, const char* tag = 0);
		YamlNode AddSequence(yaml_sequence_style_e style = YAML_ANY_SEQUENCE_STYLE, const char* tag = 0);
		YamlNode AddMapping(yaml_mapping_style_e style = YAML_ANY_MAPPING_STYLE, const char* tag = 0);
// 		YamlNode AddVariant(const engVariant& data, const char* tag = 0);

		void Clear();

		yaml_document_t* GetDocument() { return &_document; }
		const yaml_document_t* GetDocument() const { return &_document; }

	protected:
		yaml_document_t _document;

		friend class YamlFileLoader;
	};

	//////////////////////////////////////////////////////////////////////////
	class YamlFileLoader : public ResourceLoaderImpl<YamlFile>
	{
		UUT_OBJECT(uut, YamlFileLoader, ResourceLoader)
	public:
		virtual SharedPtr<Resource> Load(const SharedPtr<Stream>& stream) override;
	};

	//////////////////////////////////////////////////////////////////////////
	class YamlFileSaver : public ResourceSaverImpl<YamlFile>
	{
		UUT_OBJECT(uut, YamlFileSaver, ResourceSaver)
	public:
		virtual bool Save(const SharedPtr<Resource>& resource, const SharedPtr<Stream>& stream) override;

		static int WriteHandler(void *data, unsigned char *buffer, size_t size);
	};
}