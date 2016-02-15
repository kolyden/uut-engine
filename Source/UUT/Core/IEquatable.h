#pragma once

namespace uut
{
	class Object;

	class IEquatable
	{
	public:
		virtual bool Equals(const Object* obj) const = 0;
	};

	template<typename T>
	class Equatable : public IEquatable
	{
	public:
		virtual bool Equals(const T* obj) const = 0;
		virtual bool Equals(const Object* obj) const = 0;
	};
}