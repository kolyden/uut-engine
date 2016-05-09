#include "Variant.h"
#include "Object.h"

namespace uut
{
	const Variant Variant::Empty;

	Variant::Variant()
		: _type(VariantType::Empty)
		, _dataType(nullptr)
	{
	}

	Variant::Variant(const Type* type)
		: _type(VariantType::Type)
		, _dataType(type)
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

	const ValueType* Variant::GetStruct(const Type* type) const
	{
		if (type == nullptr || !IsValueType())
			return nullptr;

		if (!_dataType->CanConvert(type))
			return nullptr;

		return reinterpret_cast<const ValueType*>(_data.data());
	}

	Object* Variant::GetObject() const
	{
		return IsObject() ? _shared.Get() : nullptr;
	}

	Object* Variant::GetObject(const Type* type) const
	{
		if (type == nullptr || !IsObject())
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