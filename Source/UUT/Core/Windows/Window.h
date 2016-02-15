#pragma once
#include "Core/Object.h"
#include "Core/Math/IntVector2.h"
#include "SDL2/SDL.h"

namespace uut
{
	class Window : public Object
	{
	public:
		Window();
		virtual ~Window();

		bool Create();
		void Destroy();
		bool IsCreated() const;

		void PoolEvent();

		void SetTitle(const String& title);
		const String& GetTitle() const;

		void SetSize(const IntVector2& size);
		const IntVector2& GetSize() const;

		uintptr_t GetInternalHandle() const;

	protected:
		String _title;
		IntVector2 _size;
		SDL_Window* _data;
	};
}