#include "PassabilityLayer.h"
#include "Tilemap.h"

namespace uut
{
	UUT_STRUCT_IMPLEMENT(PassabilityLayer)
	{}

	PassabilityLayer::PassabilityLayer()
	{
	}

	void PassabilityLayer::SetBlocked(int x, int y, bool blocked)
	{
		_value[y*_tilemap->GetSize().x + x] = blocked;
	}

	bool PassabilityLayer::IsBlocked(int x, int y) const
	{
		return _value[y*_tilemap->GetSize().x + x];
	}

	void PassabilityLayer::SetSize(const IntVector2& size)
	{
		_value.resize(size.Area(), false);
	}

	void PassabilityLayer::Update(float deltaTime)
	{
	}

	void PassabilityLayer::DrawLayer(Graphics* graphics) const
	{
	}
}
