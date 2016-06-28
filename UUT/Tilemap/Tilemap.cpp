#include "Tilemap.h"
#include "TilemapLayer.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(Tilemap)
	{}

	Tilemap::Tilemap()
		: _size(0)
		, _cellSize(16)
	{
	}

	void Tilemap::AddLayer(SharedPtr<TilemapLayer> layer)
	{
		if (layer == nullptr || !layer->_tilemap.Expired())
			return;

		layer->_tilemap = GetSharedThis();
		_layers << layer;
		layer->SetSize(_size);
	}

	void Tilemap::SetSize(const IntVector2& size)
	{
		if (size.x <= 0 || size.y <= 0 || _size == size)
			return;

		_size = size;
		for (auto& it : _layers)
			it->SetSize(_size);
	}

	void Tilemap::SetCellSize(const Vector2& size)
	{
		_cellSize = size;
	}

	const Vector2& Tilemap::GetCellSize() const
	{
		return _cellSize;
	}

	void Tilemap::Clear()
	{
		_layers.Clear();
		_size = IntVector2::Zero;
	}

	void Tilemap::Update(float deltaTime)
	{
		for (auto& it : _layers)
		{
			if (it->IsActive())
				it->Update(deltaTime);
		}
	}
}