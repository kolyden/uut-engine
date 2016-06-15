#pragma once
#include <Resources/Resource.h>
#include <Core/Math/IntVector2.h>
#include <Core/Math/Vector2.h>

namespace uut
{
	class TilemapLayer;

	class Tilemap : public Resource
	{
		UUT_OBJECT(Tilemap, Resource)
	public:
		Tilemap();

		void AddLayer(TilemapLayer* layer);

		template<class C, std::enable_if_t<std::is_base_of<TilemapLayer, C>::value>* = nullptr>
		C* AddLayer(const String& name = String::Empty)
		{
			auto layer = SharedPtr<C>::Make();
			if (layer == nullptr)
				return nullptr;

			if (!name.IsEmpty())
				layer->SetName(name);
			AddLayer(layer);
			return layer;
		}

		void SetSize(const IntVector2& size);
		const IntVector2& GetSize() const { return _size; }

		void SetCellSize(const Vector2& size);
		const Vector2& GetCellSize() const;

		void Clear();

		void Update(float deltaTime);

	protected:
		IntVector2 _size;
		Vector2 _cellSize;
		List<SharedPtr<TilemapLayer>> _layers;
	};
}