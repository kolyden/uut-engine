#pragma once
#include <Resources/Resource.h>
#include <Resources/ResourceLoader.h>
#include <JSON/libjson.h>

namespace uut
{
	class JsonNode
	{
	public:
		JsonNode();
		JsonNode(JSONNODE* node);

		int Type() const;
		int Count() const;

		JsonNode GetAt(int index) const;
		JsonNode Get(const String& name) const;

		JsonNode operator[](const char* name) const { return Get(name); }

		inline bool IsNull() const { return Type() == JSON_NULL; }
		inline bool IsString() const { return Type() == JSON_STRING; }
		inline bool IsNumber() const { return Type() == JSON_NUMBER; }
		inline bool IsBool() const { return Type() == JSON_BOOL; }
		inline bool IsArray() const { return Type() == JSON_ARRAY; }
		inline bool IsNode() const { return Type() == JSON_NODE; }

		String ToString() const;

		int ToInt() const;
		float ToFloat() const;
		bool ToBool() const;

		template<class T>
		T To(const T& defVal) const { return ToVariant().forceGet(defVal); }

		int ToEnum(const char* types[], int count, int defVal = 0) const;

		template<class T>
		T ToEnum(T defVal = (T)0) const { return (T)Enum<T>::Parse(ToString(), defVal); }

	protected:
		JSONNODE* _node;
	};

	//////////////////////////////////////////////////////////////////////////
	class JsonFile : public Resource
	{
		UUT_OBJECT(uut, JsonFile, Resource)
	public:
		JsonFile();
		virtual ~JsonFile();

		void Clear();
		const JsonNode& GetRoot() const;

	protected:
		JSONNODE* _data;
		JsonNode _root;

		friend class JsonFileLoader;
	};

	//////////////////////////////////////////////////////////////////////////
	class JsonFileLoader : public ResourceLoaderImpl<JsonFile>
	{
		UUT_OBJECT(uut, JsonFileLoader, ResourceLoader);
	public:
		virtual SharedPtr<Resource> Load(const SharedPtr<Stream>& stream) override;
	};
}