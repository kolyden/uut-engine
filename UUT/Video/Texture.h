#pragma once
#include <Core/Math/Vector2i.h>
#include <Resources/Resource.h>

namespace uut
{
	enum class TextureAccess
	{
		Static,
		Streaming,
		Target,
	};

	class Texture : public Resource
	{
		UUT_OBJECT(uut, Texture, Resource)
	public:
		Texture();
		virtual ~Texture();

		const Vector2i& GetSize() const { return _size; }
		int GetWidth() const { return _size.x; }
		int GetHeight() const { return _size.y; }

		virtual intptr_t GetNativeHandle() const = 0;

	protected:
		Vector2i _size;
		TextureAccess _access;
	};
}