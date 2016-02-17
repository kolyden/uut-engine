#pragma once
#include "Core/Object.h"
#include "Core/Math/IntVector2.h"
#include "SDL2/SDL.h"

namespace uut
{
	enum class TextureAccess
	{
		Static,
		Streaming,
		Target,
	};

	class Texture : public Object
	{
	public:
		Texture();
		virtual ~Texture();

		const IntVector2& GetSize() const { return _size; }
		int GetWidth() const { return _size.x; }
		int GetHeight() const { return _size.y; }

		virtual uintptr_t GetNativeHandle() const = 0;

	protected:
		IntVector2 _size;
		TextureAccess _access;
	};
}