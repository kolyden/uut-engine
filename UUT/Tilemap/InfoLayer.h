#pragma once
#include "TilemapLayer.h"

namespace uut
{
	template<class T>
	class InfoLayer : public TilemapLayer
	{
	public:
		InfoLayer() {}

		T& operator[] (const IntVector2& pos) { return _data[PosToIndex(pos.x, pos.y)]; }
		const T& operator[] (const IntVector2& pos) const { return _data[PosToIndex(pos.x, pos.y)]; }

		void Set(int x, int y, const T& data) { _data[PosToIndex(x, y)] = data; }

		T& Get(int x, int y) { return _data[PosToIndex(x, y)]; }
		const T& Get(int x, int y) const { return _data[PosToIndex(x, y)]; }

		void SetSize(const IntVector2& size) override
		{
			_size = size;
			_data.SetSize(_size.Area());
		}

	protected:
		List<T> _data;
		IntVector2 _size;

		int PosToIndex(int x, int y) const { return y*_size.x + x; }
	};
}