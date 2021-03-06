#pragma once
#include "MemberInfo.h"
#include "FieldAttribute.h"
#include <Core/Variant.h>
#include <Core/BaseObject.h>

namespace uut
{
	class IPropertyInfo : public IMemberInfo
	{
	public:
		explicit IPropertyInfo(const String& name, FieldAttributes attributes);

		MemberType GetMemberType() const override;
		const String& GetName() const override;

		FieldAttributes GetAttributes() const { return _attributes; }

		bool IsPublic() const;
		bool IsPrivate() const;
		bool IsStatic() const;

		virtual bool CanSet() const = 0;

		virtual bool SetValue(BaseObject& object, const Variant& value) = 0;
		virtual Variant GetValue(const BaseObject* object) const = 0;

	protected:
		String _name;
		FieldAttributes _attributes;
	};

	////////////////////////////////////////////////////////////////////////////
	template<class C, typename T>
	class PropertyInfo : public IPropertyInfo
	{
	public:
		typedef std::function<void(C*, T)> Setter;
		typedef std::function<T(const C*)> Getter;

		PropertyInfo(const String& name, Getter getter, Setter setter)
			: IPropertyInfo(name, FieldAttribute::Public)
			, _getter(getter)
			, _setter(setter)
		{			
		}

		virtual bool CanSet() const override { return _setter != nullptr; }

		virtual bool SetValue(BaseObject& object, const Variant& value) override
		{
			if (!CanSet())
				return false;

			_setter(static_cast<C*>(&object), value.Get<T>());
			return true;
		}

		virtual Variant GetValue(const BaseObject* object) const override
		{
			return Variant(_getter(static_cast<const C*>(object)));
		}

	protected:
		Getter _getter;
		Setter _setter;
	};

	////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class StaticPropertyInfo : public IPropertyInfo
	{
	public:
		typedef std::function<void(T)> Setter;
		typedef std::function<T()> Getter;

		StaticPropertyInfo(const String& name, Getter getter, Setter setter)
			: IPropertyInfo(name, FieldAttribute::Public)
			, _getter(getter)
			, _setter(setter)
		{
			_attributes = FieldAttribute::Static;
		}

		virtual bool CanSet() const override { return _setter != nullptr; }

		virtual bool SetValue(BaseObject& object, const Variant& value) override
		{
			if (!CanSet())
				return false;

			_setter(value.Get<T>());
			return true;
		}

		virtual Variant GetValue(const BaseObject* object) const override
		{
			return Variant(_getter());
		}

	protected:
		Getter _getter;
		Setter _setter;
	};

	//////////////////////////////////////////////////////////////////////////
	template<class C, typename T>
	class VariableProperty : public IPropertyInfo
	{
	public:
		VariableProperty(const String& name, T C::*var)
			: IPropertyInfo(name, FieldAttribute::Public)
			, _variable(var)
		{}

		virtual bool CanSet() const override
		{
			return true;
		}

		bool SetValue(BaseObject& object, const Variant& value) override
		{
			T data;
			if (!value.TryGet(data))
				return false;

			(((C*)&object)->*_variable) = data;
			return true;
		}

		Variant GetValue(const BaseObject* object) const override
		{
			return (((const C*)object)->*_variable);
		}

	protected:
		T C::* _variable;
	};

#define UUT_REGISTER_PROPERTY(name, type, varname) \
		internalType->AddMember(new VariableProperty<ClassName, type>(name, &ClassName::varname));
}