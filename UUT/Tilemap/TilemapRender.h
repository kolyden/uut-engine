#pragma once
#include "TilemapLayer.h"

namespace uut
{
	class Graphics;
	class TilemapChunk;

	class TilemapRender : public TilemapLayer
	{
		UUT_OBJECT(TilemapRender, TilemapLayer)
	public:
		TilemapRender();

		void SetVisible(bool visible);
		bool IsVisible() const;

		virtual void Draw(Graphics* graphics) const = 0;

		void SetSize(const IntVector2& size) override {}
		void Update(float deltaTime) override {}

	protected:
		bool _visible;
	};
}