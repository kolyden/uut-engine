#pragma once
#include "Platform.h"
#include "String.h"
#include "Ptr.h"

namespace uut
{
	class Object;

	enum class VariantType
	{
		Empty,
		Boolean,
		Numeric,
		String,
		List,
		Object,
	};

	class Variant
	{
	public:
		Variant();
		~Variant();

		void Clear();

		VariantType GetVariantType() const { return _type; }

	protected:
		VariantType _type;
		union UnionType
		{
			bool _bool;
			int64_t _numeric;
			double _real;
			int _numericArr[4];
			float _realArr[4];
			String _str;
			List<Variant> _list;
			SharedPtr<Object> _shared;
		};
	};
}