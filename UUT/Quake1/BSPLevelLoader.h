#pragma once
#include <Resources/ResourceLoader.h>
#include "BSP.h"

namespace uut
{
	class BSPLevel;

	class BSPLevelLoader : public ResourceLoaderImpl<BSPLevel>
	{
		UUT_OBJECT(uut, BSPLevelLoader, ResourceLoader)
	public:
		SharedPtr<Resource> Load(const SharedPtr<Stream>& stream) override;

		template<typename T>
		static void LoadLump(const uutQ1::bsp::Lump& lump, List<T>& list, const SPtr<Stream>& stream)
		{
			stream->SetPosition(lump.fileofs);
			list.SetSize(lump.filelen / sizeof(T));
			stream->Read(list.GetData(), list.GetDataSize());
		}
	};
}