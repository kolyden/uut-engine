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

		void Destroy();
		bool IsCreated() const;

		const IntVector2& GetSize() const { return _size; }

		void* Lock();
		void Unlock();

	protected:
		IntVector2 _size;
		SDL_Texture* _data;
		TextureAccess _access;

		friend class Renderer;
	};
}