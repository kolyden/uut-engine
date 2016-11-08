#include "YamlFile.h"
#include <Resources/ResourceCache.h>
#include <Core/Debug.h>

#include "FileStream.h"
#include "MemoryStream.h"

namespace uut
{
	static int ReadFromStreamHandler(void *data, unsigned char *buffer, size_t size, size_t *size_read)
	{
		auto file = (Stream*)data;
		*size_read = file->Read(buffer, size);
		return 1;
	}

	static void ParserLogError(yaml_parser_t* parser)
	{
		switch (parser->error)
		{
		case YAML_MEMORY_ERROR:
			Debug::LogError("Memory error: Not enough memory for parsing");
			break;

		case YAML_READER_ERROR:/** Cannot read or decode the input stream. */
			if (parser->problem_value != -1)
			{
				Debug::LogError("Reader error: %s: #%X at %d\n",
					parser->problem, parser->problem_value, parser->problem_offset);
			}
			else {
				Debug::LogError("Reader error: %s at %d\n",
					parser->problem, parser->problem_offset);
			}
			break;

		case YAML_SCANNER_ERROR:/** Cannot scan the input stream. */
			if (parser->context) {
				Debug::LogError("Scanner error: %s at line %d, column %d\n"
					"%s at line %d, column %d\n", parser->context,
					parser->context_mark.line + 1, parser->context_mark.column + 1,
					parser->problem, parser->problem_mark.line + 1,
					parser->problem_mark.column + 1);
			}
			else {
				Debug::LogError("Scanner error: %s at line %d, column %d\n",
					parser->problem, parser->problem_mark.line + 1,
					parser->problem_mark.column + 1);
			}
			break;

		case YAML_PARSER_ERROR:/** Cannot parse the input stream. */
			if (parser->context) {
				Debug::LogError("Parser error: %s at line %d, column %d\n"
					"%s at line %d, column %d\n", parser->context,
					parser->context_mark.line + 1, parser->context_mark.column + 1,
					parser->problem, parser->problem_mark.line + 1,
					parser->problem_mark.column + 1);
			}
			else {
				Debug::LogError("Parser error: %s at line %d, column %d\n",
					parser->problem, parser->problem_mark.line + 1,
					parser->problem_mark.column + 1);
			}
			break;

		case YAML_COMPOSER_ERROR:/** Cannot compose a YAML document. */
			if (parser->context) {
				Debug::LogError("Composer error: %s at line %d, column %d\n"
					"%s at line %d, column %d\n", parser->context,
					parser->context_mark.line + 1, parser->context_mark.column + 1,
					parser->problem, parser->problem_mark.line + 1,
					parser->problem_mark.column + 1);
			}
			else {
				Debug::LogError("Composer error: %s at line %d, column %d\n",
					parser->problem, parser->problem_mark.line + 1,
					parser->problem_mark.column + 1);
			}
			break;

		case YAML_WRITER_ERROR:/** Cannot write to the output stream. */
			Debug::LogError("Cannot write to the output stream");
			break;

		case YAML_EMITTER_ERROR:/** Cannot emit a YAML stream. */
			Debug::LogError("Cannot emit a YAML stream.");

			break;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	UUT_OBJECT_IMPLEMENT(YamlFile)
	{}

	//////////////////////////////////////////////////////////////////////////
	YamlFile::YamlFile()
	{
		memset(&_document, 0, sizeof(_document));
		yaml_document_initialize(&_document, NULL, NULL, NULL, 0, 0);
	}

	YamlFile::~YamlFile()
	{
		yaml_document_delete(&_document);
	}

	bool YamlFile::CreateFromString(const char* str, int size)
	{
		if (str == nullptr || size <= 0)
			return false;

		auto stream = SharedPtr<MemoryStream>::Make();
		if (!stream && !stream->Open(str, size))
			return false;

		yaml_parser_t parser;
		memset(&parser, 0, sizeof(parser));

		if (!yaml_parser_initialize(&parser))
		{
			ParserLogError(&parser);
			return false;
		}

		yaml_parser_set_input(&parser, &ReadFromStreamHandler, stream.Get());

		auto data = SharedPtr<YamlFile>::Make();
		if (yaml_parser_load(&parser, &_document) == 0)
		{
			ParserLogError(&parser);
			return false;
		}

		auto root = yaml_document_get_root_node(&_document);
		if (root == 0)
			return false;

		yaml_parser_delete(&parser);

		return true;
	}

	YamlNode YamlFile::GetRoot()
	{
		return YamlNode(1, GetSharedThis());
	}

	YamlNode YamlFile::GetNode(int index)
	{
		return YamlNode(index + 1, GetSharedThis());
	}

	int YamlFile::GetNodeCount() const
	{
		return _document.nodes.top - _document.nodes.start;
	}

	YamlNode YamlFile::AddScalar(const char* scalar, yaml_scalar_style_e style /* = YAML_ANY_SCALAR_STYLE */, const char* tag /* = 0 */)
	{
		if (!scalar)
			return YamlNode::Empty;

		const int index = yaml_document_add_scalar(&_document, (yaml_char_t*)tag,
			(yaml_char_t*)scalar, strlen(scalar), style);
		return index > 0 ? YamlNode(index, GetSharedThis()) : YamlNode::Empty;
	}

	YamlNode YamlFile::AddSequence(yaml_sequence_style_e style /* = YAML_ANY_SEQUENCE_STYLE */, const char* tag /* = 0 */)
	{
		const int index = yaml_document_add_sequence(&_document, (yaml_char_t*)tag, style);
		return index > 0 ? YamlNode(index, GetSharedThis()) : YamlNode::Empty;
	}

	YamlNode YamlFile::AddMapping(yaml_mapping_style_e style /* = YAML_ANY_MAPPING_STYLE */, const char* tag /* = 0 */)
	{
		const int index = yaml_document_add_mapping(&_document, (yaml_char_t*)tag, style);
		return index > 0 ? YamlNode(index, GetSharedThis()) : YamlNode::Empty;
	}

// 	YamlNode YamlFile::AddVariant(const engVariant& data, const char* tag /* = 0 */)
// 	{
// 		if (!data.is_valid())
// 			return YamlNode::Empty;
// 
// 		if (data.type() == engVariantData::TYPE_POINTER)
// 		{
// 			auto obj = (Object*)data.data().get_ptr();
// 			auto res = dynamic_cast<Resource*>(obj);
// 			if (res)
// 			{
// 				const Path& path = res->GetResourcePath();
// 				if (!path.IsEmpty())
// 					return AddScalar(path.ToUtf8(), YAML_ANY_SCALAR_STYLE, tag);
// 			}
// 
// 			return YamlNode::Empty;
// 		}
// 
// 		String str;
// 		if (!data.get(&str))
// 			return YamlNode::Empty;
// 
// 		if (data.is_array())
// 		{
// 			const auto& arr = data.data().get_array();
// 			auto seq = AddSequence(str.Count() > 40 ? YAML_BLOCK_SEQUENCE_STYLE : YAML_FLOW_SEQUENCE_STYLE, tag);
// 
// 			foreach(i, arr)
// 			{
// 				if (!Variant2Data<String>::Get(&arr[i], &str))
// 					str.Clear();
// 
// 				seq.AppendSequence(AddScalar(str));
// 			}
// 
// 			return seq;
// 		}
// 
// 		return AddScalar(str, data.type() == engVariantData::TYPE_STRING ? YAML_SINGLE_QUOTED_SCALAR_STYLE : YAML_PLAIN_SCALAR_STYLE);
// 	}

	void YamlFile::Clear()
	{
		yaml_document_delete(&_document);
		yaml_document_initialize(&_document, NULL, NULL, NULL, 0, 0);
	}

	//////////////////////////////////////////////////////////////////////////
	UUT_OBJECT_IMPLEMENT(YamlFileLoader)
	{}

	SharedPtr<Resource> YamlFileLoader::Load(const SharedPtr<Stream>& stream)
	{
		yaml_parser_t parser;
		memset(&parser, 0, sizeof(parser));

		if(!yaml_parser_initialize(&parser))
		{
			ParserLogError(&parser);
			return nullptr;
		}

		yaml_parser_set_input(&parser, &ReadFromStreamHandler, stream.Get());

		auto data = SharedPtr<YamlFile>::Make();
		if (yaml_parser_load(&parser, &data->_document) == 0)
		{
			ParserLogError(&parser);
			return nullptr;
		}

		auto root = yaml_document_get_root_node(&data->_document);
		if (root == 0)
			return nullptr;

		yaml_parser_delete(&parser);

		return DynamicCast<Resource>(data);
	}

	//////////////////////////////////////////////////////////////////////////
	UUT_OBJECT_IMPLEMENT(YamlFileSaver)
	{}

	bool YamlFileSaver::Save(const SharedPtr<Resource>& resource, const SharedPtr<Stream>& stream)
	{
		auto yaml = DynamicCast<YamlFile>(resource);
		if (!yaml)
			return false;

// 		auto clone = DynamicCast<YamlFile>(yaml->Clone());
// 		if (!clone)
// 			return false;

		yaml_emitter_t emitter;
		yaml_emitter_initialize(&emitter);
		yaml_emitter_set_unicode(&emitter, 1);
		yaml_emitter_set_encoding(&emitter, YAML_UTF8_ENCODING);
		yaml_emitter_set_output(&emitter, &WriteHandler, stream.Get());

		yaml_emitter_dump(&emitter, yaml->GetDocument());
		yaml_emitter_flush(&emitter);

		yaml_emitter_delete(&emitter);

		return true;
	}

	int YamlFileSaver::WriteHandler(void *data, unsigned char *buffer, size_t size)
	{
		auto file = (Stream*)data;
		file->Write(buffer, size);
		return 1;
	}
}