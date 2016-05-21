#pragma once
#include <Core/Attribute.h>
#include <Core/String.h>

namespace uut
{
	enum class TestCategory
	{
		Basic,
	};

	class TestItemAttribute : public Attribute
	{
		UUT_OBJECT(TestItemAttribute, Attribute)
	public:
		TestItemAttribute(TestCategory category, const String& title);

		TestCategory GetCategory() const { return _category; }
		const String& GetTitle() const { return _title; }

	protected:
		TestCategory _category;
		String _title;
	};
}