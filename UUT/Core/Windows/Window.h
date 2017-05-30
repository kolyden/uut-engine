#pragma once
#include <Core/Object.h>
#include <Core/Math/Vector2i.h>

namespace uut
{
	class Image;

	class Window : public Object
	{
		UUT_OBJECT(uut, Window, Object)
	public:
		Window();
		virtual ~Window();

		bool Create();
		void Destroy();
		bool IsCreated() const;

		void SetTitle(const String& title);
		const String& GetTitle() const;

		void SetSize(const Vector2i& size);
		const Vector2i& GetSize() const;

		void SetIcon(const SharedPtr<Image>& icon);
		const SharedPtr<Image>& GetIcon() const;

		bool IsMouseFocused() const;

		static Window* GetFocusedWindow();

		uintptr_t GetInternalHandle() const;

	protected:
		String _title;
		Vector2i _size;
		SharedPtr<Image> _icon;
		SDL_Window* _data;
	};
}