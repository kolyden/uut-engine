#include "Variant.h"
#include "Object.h"
#include "Reflection/MemberInfo.h"
#include "Reflection/ConstructorInfo.h"
#include "Reflection/ConverterInfo.h"

namespace uut
{
	const Variant Variant::Empty;

	Variant::Variant()
		: _type(VariantType::Empty)
		, _dataType(nullptr)
	{
	}

	Variant::Variant(nullptr_t)
		: _type(VariantType::Empty)
		, _dataType(nullptr)
	{}

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
		if (_type == VariantType::Struct)
			_dataType->PlacementDtor(_data.data());
		_shared = nullptr;
		_dataType = nullptr;
		_data.clear();
		_type = VariantType::Empty;
	}

	const ValueType* Variant::GetStruct(const Type* type) const
	{
		if (type == nullptr || !IsValueType())
			return nullptr;

		if (!_dataType->CanConvert(type))
			return nullptr;

		return reinterpret_cast<const ValueType*>(_data.data());
	}

	bool Variant::TryCastStruct(const Type* type, ValueType& value) const
	{
		if (!IsValueType() || type == nullptr)
			return false;

		auto value_type = reinterpret_cast<const ValueType*>(_data.data());
		if (_dataType == type)
		{			
			value = *value_type;
			return true;
		}

		if (_dataType->Convert(*value_type, type, value))
			return true;

// 		for (auto info : _dataType->GetMembers())
// 		{
// 			if (info->GetMemberType() != MemberType::Converter)
// 				continue;
// 
// 			auto converter = static_cast<const ConverterInfo*>(info);
// 			if (converter->GetResultType() != type)
// 				continue;
// 
// 			if (converter->Convert(*value_type, value))
// 				return true;
// 		}

// 		for (auto info : type->GetMembers())
// 		{
// 			if (info->GetMemberType() != MemberType::Constructor)
// 				continue;
// 
// 			auto ctor = static_cast<const ConstructorInfo*>(info);
// 			auto& argTypes = ctor->GetArgsTypes();
// 			if (argTypes.Count() != 1 || argTypes[0] != _dataType)
// 				continue;
// 
// 			if (ctor->Call(&value, { Variant(_dataType, *value_type) }))
// 				return true;
// 		}

		return false;
	}

	SharedPtr<Object> Variant::GetObject() const
	{
		return IsObject() ? _shared : nullptr;
	}

	SharedPtr<Object> Variant::GetObject(const Type* type) const
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

	void Variant::SetObject(const Type* type, const SharedPtr<Object>& obj)
	{
		_type = VariantType::Object;
		_dataType = type;
		_shared = obj;
	}
}