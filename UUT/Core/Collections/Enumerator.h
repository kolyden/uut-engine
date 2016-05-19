#pragma once

namespace uut
{
	template<typename T>
	class Enumerator
	{
	public:
		T operator*() const
		{
			return Current();
		}

		const Enumerator<T>& operator++()
		{
			MoveNext();
			return *this;
		}

		bool operator!=(const IEnumerable<T>& it) const
		{
		}

		virtual T Current() const = 0;
		virtual bool MoveNext() = 0;
		virtual void Reset() = 0;

	protected:
	};
}