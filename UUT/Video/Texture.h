#pragma once
#include <Core/Math/IntVector2.h>
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

		const IntVector2& GetSize() const { return _size; }
		int GetWidth() const { return _size.x; }
		int GetHeight() const { return _size.y; }

		virtual intptr_t GetNativeHandle() const = 0;

	protected:
		IntVector2 _size;
		TextureAccess _access;
	};
}