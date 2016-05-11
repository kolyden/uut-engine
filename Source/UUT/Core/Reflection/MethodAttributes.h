#pragma once

namespace uut
{
	enum class MethodAttribute
	{
		Private = 0,
		Public = 1,
		Static = 2,
	};

	template<class T>
	class EnumFlagsValue
	{
	public:
		EnumFlagsValue() : _flags(0) {}
		EnumFlagsValue(unsigned flag) : _flags(flag) {}
		EnumFlagsValue(T flag) : _flags(static_cast<unsigned>(flag)) {}

		operator unsigned() const
		{ return _flags; }

		void Clear() { _flags = 0; }
		bool IsEmpty() const { return _flags == 0; }
		bool HasFlag(T flag) const { return (_flags & (unsigned)flag) == (unsigned)flag; }
		void RemoveFlag(T flag) { _flags &= ~(unsigned)flag; }

		void operator |= (unsigned flag) { _flags |= flag; }
		void operator |= (T flag) { _flags |= (unsigned)flag; }

		EnumFlagsValue operator | (T flag) { EnumFlagsValue flags(_flags);  flags |= (unsigned)flag; return flags; }

		bool operator & (unsigned flag) const { return (_flags & flag) == flag; }
		bool operator & (T flag) const { return HasFlag(flag); }

		bool operator == (unsigned flag) const { return _flags == flag; }
		bool operator == (T flag) const { return _flags == (unsigned)flag; }
		bool operator != (unsigned flag) const { return !operator==(flag); }
		bool operator != (T flag) const { return !operator==(flag); }

	protected:
		unsigned _flags;
	};

	typedef EnumFlagsValue<MethodAttribute> MethodAttributes;
}