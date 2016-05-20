#pragma once
#include <Resources/Resource.h>
#include <Core/Math/IntVector2.h>

namespace uut
{
	class Graphics;
	class TilemapLayer;

	class Tilemap : public Resource
	{
		UUT_OBJECT(Tilemap, Resource)
	public:
		Tilemap();

		void AddLayer(TilemapLayer* layer);
		template<class C> C* AddLayer()
		{
			static_assert(std::is_base_of<TilemapLayer, C>::value, "must be derived from TilemapLayer");
			auto layer = new C();
			AddLayer(layer);
			return layer;
		}

		void SetSize(const IntVector2& size);
		const IntVector2& GetSize() const { return _size; }

		void Clear();

		void Update(float deltaTime);
		void Draw(Graphics* graphics) const;

	protected:
		IntVector2 _size;
		List<SharedPtr<TilemapLayer>> _layers;
	};
}
