#pragma once

namespace uut
{
	template<class T, class DataType>
	class IEnumerable
	{
	public:
		typedef typename DataType::iterator Iterator;
		typedef typename DataType::const_iterator ConstIterator;

		Iterator Begin() { return _data.begin(); }
		Iterator End() { return _data.end(); }

		ConstIterator Begin() const { return _data.begin(); }
		ConstIterator End() const { return _data.end(); }

	protected:
		DataType _data;
	};
}