#pragma once
#include <Core/Object.h>
#include <Core/Math/Vector2i.h>

namespace uut
{
	class Image : public Object
	{
		UUT_OBJECT(uut, Image, Object)
	public:
		Image();
		virtual ~Image();

		bool Create(const Vector2i& size);
		void Destroy();
		bool IsCreated() const;

		const Vector2i& GetSize() const { return _size; }

		uintptr_t GetInternalHandle() const;

	protected:
		Vector2i _size;
		SDL_Surface* _data;
	};
}