#include "Variant.h"
#include "Object.h"

namespace uut
{
	Variant::Variant()
		: _type(VariantType::Empty)
		, _dataType(nullptr)
	{
	}

	Variant::~Variant()
	{
		Clear();
	}

	void Variant::Clear()
	{		
		_type = VariantType::Empty;
		_dataType = nullptr;
		_shared = nullptr;
		_data.clear();
	}

	bool Variant::GetStruct(const Type* type, ValueType& value) const
	{
		if (type == nullptr || _dataType == nullptr)
			return false;

		if (!_dataType->CanConvert(value.GetType()))
			return false;

		auto data = reinterpret_cast<const ValueType*>(_data.data());
		memcpy(&value, data, _data.size());
		return true;
	}

	Object* Variant::GetObject(const Type* type) const
	{
		if (type == nullptr || IsEmpty())
			return nullptr;

		if (!_dataType->CanConvert(type))
			return nullptr;

		return _shared;
	}

	////////////////////////////////////////////////////////////////////
	void Variant::SetStruct(const Type* type, const ValueType& value, uint size)
	{
		_type = VariantType::Struct;
		_dataType = type;
		_data.resize(size);
		memcpy(_data.data(), &value, size);
	}

	void Variant::SetObject(const Type* type, Object* value)
	{
		_type = VariantType::Object;
		_dataType = type;
		_shared = value;
	}
}