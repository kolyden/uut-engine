#pragma once
#include "Core/Object.h"
#include "Core/Math/IntVector2.h"
#include "SDL2/SDL.h"

namespace uut
{
	class Image : public Object
	{
	public:
		Image();
		virtual ~Image();

		bool Create(const IntVector2& size);
		void Destroy();
		bool IsCreated() const;

		const IntVector2& GetSize() const { return _size; }

	protected:
		IntVector2 _size;
		SDL_Surface* _data;
	};
}