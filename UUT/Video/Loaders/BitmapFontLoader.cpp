#include "BitmapFontLoader.h"
#include <Core/IO/BinaryReader.h>
#include <Core/IO/Path.h>
#include <Core/IO/Stream.h>
#include <Resources/ResourceCache.h>
#include <Video/BitmapFont.h>
#include <Video/Texture2D.h>

namespace uut
{
	UUT_OBJECT_IMPLEMENT(BitmapFontLoader)
	{}

	BitmapFontLoader::BitmapFontLoader()
	{		
	}

	static const int STRING_BUFFER = 64;
	struct BMFontHeader
	{
		int16_t fontSize;
		uint8_t bitField;
		uint8_t charSize;
		uint16_t stretchH;
		uint8_t aa;
		uint8_t paddingUp;
		uint8_t paddingRight;
		uint8_t paddingDown;
		uint8_t paddingLeft;
		uint8_t spacingHoriz;
		uint8_t spacingVert;
		uint8_t outline;
		char fontName[STRING_BUFFER];
	};

	SharedPtr<Resource> BitmapFontLoader::Load(const SharedPtr<Stream>& stream)
	{
		auto reader = MakeShared<BinaryReader>(stream);

		List<uint8_t> magic;
		reader->ReadBytes(3, magic);
		if (magic.Count() != 3 ||
			magic[0] != 'B' ||
			magic[1] != 'M' ||
			magic[2] != 'F')
		{
// 			ENG_LOGERROR("Not a BMFont format");
			return nullptr;
		}

		bool loadHeader = false;

		const auto version = reader->ReadUint8();
		if (version != 3)
		{
// 			ENG_LOGERROR("BMFont old version");
			return nullptr;
		}

		BMFontHeader header;
		auto font = MakeShared<BitmapFont>();
		List<String> pages;
		List<FontGlyph> chars;
		List<FontKerningPair> kernings;

		while (!reader->IsEOF())
		{
			const auto type = reader->ReadUint8();
			const auto size = reader->ReadInt32();
			if (type == 1)
			{
				reader->ReadBytes(size, &header);
				loadHeader = true;
			}
			else if (type == 2)
			{
// 				reader->SkipBytes(size);
// 				face = new FontFaceBM(header.fontSize);
				reader->ReadBytes(size, &font->_info);
			}
			else if (type == 3)
			{
				String str = reader->ReadStringNT();
				const int count = size / (str.Count() + 1);
				pages.Add(str);
				for (int i = 1; i < count; i++)
				{
					str = reader->ReadStringNT();
					pages.Add(str);
				}
			}
			else if (type == 4)
			{
				const int count = size / 20;
				for (int i = 0; i < count; i++)
				{
					FontGlyph data;
					reader->ReadBytes(20, &data);
					chars.Add(data);
				}
			}
			else if (type == 5)
			{
				const int count = size / 10;
				for (int i = 0; i < count; i++)
				{
					FontKerningPair data;
					reader->ReadBytes(10, &data);
					kernings.Add(data);
				}
			}
			else
			{
// 				ENG_LOGERROR("Error fnt format");
				return nullptr;
			}
		}

		if (!loadHeader || !font)
			return nullptr;

		font->_glyphs = chars;
		font->_kerningPairs = kernings;

		auto cache = ResourceCache::Instance();
		const auto basedir = stream->GetPath().GetDirectoryName();
		for(auto& name : pages)
		{
			auto tex = cache->Load<Texture2D>(Path::Combine(basedir, name));
			font->_textures << tex;
		}

		font->UpdateGlyphsMap();
		font->UpdateKerningMap();
		return font;
	}
}