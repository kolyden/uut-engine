#pragma once
#include <Core/Object.h>
#include <Core/Math/IntVector2.h>

namespace uut
{
	class Image : public Object
	{
		UUT_OBJECT(uut, Image, Object)
	public:
		Image();
		virtual ~Image();

		bool Create(const IntVector2& size);
		void Destroy();
		bool IsCreated() const;

		const IntVector2& GetSize() const { return _size; }

		uintptr_t GetInternalHandle() const;

	protected:
		IntVector2 _size;
		SDL_Surface* _data;
	};
}