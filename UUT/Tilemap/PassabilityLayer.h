#pragma once
#include "TilemapLayer.h"

namespace uut
{
	class PassabilityLayer : public TilemapLayer
	{
		UUT_OBJECT(PassabilityLayer, TilemapLayer)
	public:
		PassabilityLayer();

		void SetBlocked(int x, int y, bool blocked);
		bool IsBlocked(int x, int y) const;

		void SetSize(const IntVector2& size) override;
		void Update(float deltaTime) override;
		void DrawLayer(Graphics* graphics) const override;

	protected:
		std::vector<bool> _value;
	};
}