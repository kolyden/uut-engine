#include "TilemapPlugin.h"
#include <Core/Context.h>
#include "Tilemap.h"
#include "ObjectLayer.h"
#include "ObjectLayerItem.h"
#include "Tileset.h"
#include "TilesetLayer.h"
#include "BlockedLayer.h"
#include "ObjectLayerFlags.h"

namespace uut
{
	TilemapPlugin::TilemapPlugin()
		: Plugin("Tilemap", Version(0, 1))
	{
	}

	void TilemapPlugin::OnRegister()
	{
		UUT_REGISTER_OBJECT(TilemapLayer);
		UUT_REGISTER_OBJECT(Tilemap);
		UUT_REGISTER_OBJECT(ObjectLayer);
		UUT_REGISTER_OBJECT(ObjectLayerItem);
		UUT_REGISTER_OBJECT(ObjectLayerFlags);
		UUT_REGISTER_OBJECT(Tileset);
		UUT_REGISTER_OBJECT(TilesetLayer);
		UUT_REGISTER_OBJECT(BlockedLayer);
	}
}