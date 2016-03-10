#include "Texture2DLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "STB/stb_image.h"
#include <Core/IO/Stream.h>
#include <Core/Video/Renderer.h>

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

	Texture2DLoader::Texture2DLoader(Renderer* renderer)
		: _renderer(renderer)
	{
	}

	SharedPtr<Resource> Texture2DLoader::Load(Stream* stream)
	{
		if (stream == nullptr)
			return SharedPtr<Resource>::EMPTY;

		stbi_io_callbacks callbacks{ &ReadStream, &SeekStream, &IsEOFStream };

		IntVector2 size;
		int comp;
		auto source = stbi_load_from_callbacks(&callbacks, stream, &size.x, &size.y, &comp, STBI_rgb_alpha);
		if (source == nullptr)
			return SharedPtr<Resource>::EMPTY;

		auto tex = _renderer->CreateTexture(size);
		if (!tex)
			return SharedPtr<Resource>::EMPTY;

		int pitch;
		auto dest = static_cast<char*>(tex->Lock(&pitch));
		if (!dest)
			return SharedPtr<Resource>::EMPTY;

		for (int y = 0; y < size.y; y++)
		{
			memcpy(dest + y*pitch, source + y*size.x*comp, size.x * comp);
		}

		tex->Unlock();

		stbi_image_free(source);
		return DynamicCast<Resource>(tex);
	}
}