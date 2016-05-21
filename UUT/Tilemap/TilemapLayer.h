#pragma once
#include <Core/Object.h>
#include <Core/Math/IntVector2.h>

namespace uut
{
	class Graphics;
	class Tilemap;

	class TilemapLayer : public Object
	{
		UUT_OBJECT(TilemapLayer, Object)
	public:
		TilemapLayer();

		virtual void SetSize(const IntVector2& size) = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void DrawLayer(Graphics* graphics) const = 0;
		//? virtual void OnEdit(EditorEvent& evt) = 0; move in editor?

	protected:
		WeakPtr<Tilemap> _tilemap;

		friend class Tilemap;
	};

	// TODO: Implement Layers
	// - Tiles
	// - Tile Blocking/?Types
	// - Objects
	// - Zones
	// - ?Event
}