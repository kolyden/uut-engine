#pragma once
#include <Core/Object.h>
#include <Core/Math/IntVector2.h>
#include <Video/Vertex.h>

namespace uut
{
	class Tilemap;

	class TilemapLayer : public Object
	{
		UUT_OBJECT(uut, TilemapLayer, Object)
	public:
		TilemapLayer();

		void SetName(const String& name);
		const String& GetName() const;

		void SetActive(bool active);
		bool IsActive() const;

		void SetVisible(bool visible);
		bool IsVisible() const;

		SharedPtr<Tilemap> GetTilemap() const;

	protected:
		WeakPtr<Tilemap> _tilemap;
		String _name;
		bool _active;
		bool _visible;

		virtual void OnSetSize(const IntVector2& size) {};
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() const {};

		friend class Tilemap;
	};

	// TODO: Implement Layers
	// - Tiles
	// - Tile Blocking/?Types
	// - Objects
	// - Zones
	// - ?Event
}