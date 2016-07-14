#include "Texture2DLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "STB/stb_image.h"
#include <Core/IO/Stream.h>
#include <Video/Renderer.h>
#include <Video/Texture2D.h>
#include <Resources/ResourceLoaderAttribute.h>
#include <Core/Reflection/ConstructorInfo.h>

namespace uut
{
	// fill 'data' with 'size' bytes.  return number of bytes actually read
	static int ReadStream(void *user, char *data, int size)
	{
		auto stream = static_cast<Stream*>(user);
		return stream->Read(data, size);
	}

	// skip the next 'n' bytes, or 'unget' the last -n bytes if negative
	static void SeekStream(void *user, int n)
	{
		auto stream = static_cast<Stream*>(user);
		stream->Seek(SeekMethod::Current, n);
	}

	// returns nonzero if we are at end of file/data
	static int IsEOFStream(void *user)
	{
		auto stream = static_cast<Stream*>(user);
		return stream->IsEOF() ? 1 : 0;
	}

	///////////////////////////////////////////////////////////////////////////
	UUT_OBJECT_IMPLEMENT(Texture2DLoader)
	{
		internalType->AddAttribute(new ResourceLoaderAttribute());
		UUT_REGISTER_CTOR_DEFAULT();
	}

	Texture2DLoader::Texture2DLoader()
	{
	}

	SharedPtr<Resource> Texture2DLoader::Load(const SharedPtr<Stream>& stream)
	{
		stbi_io_callbacks callbacks{ &ReadStream, &SeekStream, &IsEOFStream };

		IntVector2 size;
		int comp;
		auto source = stbi_load_from_callbacks(&callbacks, stream, &size.x, &size.y, &comp, STBI_rgb_alpha);
		if (source == nullptr)
			return nullptr;

		auto renderer = Renderer::Instance();
		auto tex = renderer->CreateTexture(size);
		if (!tex)
			return nullptr;

		int pitch;
		auto dest = static_cast<stbi_uc*>(tex->Lock(&pitch));
		if (!dest)
			return nullptr;

		for (int y = 0; y < size.y; y++)
		{
			for (int x = 0; x < size.x; x++)
			{
				const uint32_t col = ((uint32_t*)(source + y*size.x*comp + x*comp))[0];
				((uint32_t*)(dest + y*pitch + x*comp))[0] = Color32::FromABGR(col).ToInt();
			}
			//memcpy(dest + y*pitch, source + y*size.x*comp, size.x * comp);
		}

		tex->Unlock();

		stbi_image_free(source);
		return DynamicCast<Resource>(tex);
	}
}
