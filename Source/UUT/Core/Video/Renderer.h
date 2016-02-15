#pragma once
#include "Core/Object.h"
#include "Core/Video/Texture.h"
#include "Core/Video/Color32.h"
#include "Core/Math/IntVector2.h"
#include "SDL2/SDL.h"

namespace uut
{
	class Window;
	class Texture;

	class Renderer : public Object
	{
	public:
		Renderer();
		virtual ~Renderer();

		bool Create(Window* window);
		void Destroy();
		bool IsCreated() const;

		void SetColor(const Color32& color);
		void Clear();
		void Present();

		void DrawTexture(Texture* tex, int x, int y);
		void DrawTexture(Texture* tex, const IntVector2& pos);

		SharedPtr<Texture> CreateTexture(const IntVector2& size, TextureAccess access = TextureAccess::Static);

	protected:
		SharedPtr<Window> _window;
		SDL_Renderer* _data;
	};
}