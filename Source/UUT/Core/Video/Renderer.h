#pragma once
#include "Core/Object.h"
#include "Core/Video/Texture.h"
#include "Core/Video/Color.h"
#include "Core/Video/Color32.h"
#include "Core/Math/IntVector2.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

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
		const Color32& GetColor() const;

		void Clear();
		void Present();

		void DrawTexture(Texture* tex, int x, int y) const;
		void DrawTexture(Texture* tex, const IntVector2& pos) const;

		SharedPtr<Texture> CreateTexture(const IntVector2& size, TextureAccess access = TextureAccess::Static);

	protected:
		SharedPtr<Window> _window;
		SDL_Renderer* _data;
		Color32 _drawColor;
	};
}