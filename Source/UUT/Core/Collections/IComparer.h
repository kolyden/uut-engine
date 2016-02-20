#pragma once

namespace uut
{
	template<typename T>
	class IComparer
	{
	public:
		virtual ~IComparer() {}
		virtual int Compare(const T& a, const T& b) const = 0;
	};
}