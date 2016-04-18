#pragma once
#include <Core/Collections/List.h>
#include <Core/Ptr.h>
#include <Core/String.h>

namespace uut
{
	class Object;

	enum class VariantType
	{
		Empty,
		Boolean,
		Integer,
		Real,
		Pointer,
		String,
		List,
		Struct,
		Object,
	};

	class Variant
	{
	public:
		Variant();
		Variant(const Variant& other);
		explicit Variant(bool value);
		explicit Variant(int value);
		explicit Variant(float value);
		explicit Variant(const String& value);
		explicit Variant(const List<Variant>& value);
		explicit Variant(Object* object);
		~Variant();

		void Clear();

		Variant& operator=(const Variant& other);

		VariantType GetVariantType() const { return _type; }

	protected:
		VariantType _type;
		union
		{
			bool _bool;
			int64_t _int;
			double _real;
			String _str;
			List<Variant> _list;
			SharedPtr<Object> _shared;
		};
	};
}