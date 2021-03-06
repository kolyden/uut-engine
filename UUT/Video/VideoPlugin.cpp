#include "VideoPlugin.h"
#include <Core/Reflection/Type.h>
#include "Core/Context.h"
#include "BufferObject.h"
#include "FreeCamera.h"
#include "Mesh.h"
#include "Image.h"
#include "IndexBuffer.h"
#include "Sprite.h"
#include "Texture.h"
#include "Texture2D.h"
#include "VertexBuffer.h"
#include "Renderer.h"
#include "CommandList.h"
#include "Graphics.h"
#include "imageEffects/Plasma.h"
#include "Loaders/Texture2DLoader.h"
#include "Loaders/BitmapFontLoader.h"
#include "Font.h"
#include "BitmapFont.h"
#include "TextureAtlas.h"
#include "PipelineState.h"

namespace uut
{
	VideoPlugin::VideoPlugin()
		: Plugin("Video", Version(0, 1))
	{
	}

	void VideoPlugin::OnRegister()
	{
		// Buffers
		UUT_REGISTER_OBJECT(BufferObject);
		UUT_REGISTER_OBJECT(VertexBuffer);
		UUT_REGISTER_OBJECT(IndexBuffer);
		UUT_REGISTER_OBJECT(CommandList);
		UUT_REGISTER_OBJECT(PipelineState);

		UUT_REGISTER_OBJECT(Color);
		UUT_REGISTER_OBJECT(Color32);
		UUT_REGISTER_OBJECT(Viewport);

		// Textures
		UUT_REGISTER_OBJECT(Image);
		UUT_REGISTER_OBJECT(Texture);
		UUT_REGISTER_OBJECT(Texture2D);
		UUT_REGISTER_OBJECT(Sprite);
		UUT_REGISTER_OBJECT(TextureAtlas);

		UUT_REGISTER_OBJECT(Camera);
		UUT_REGISTER_OBJECT(FreeCamera);
		UUT_REGISTER_OBJECT(Mesh);

		// Fonts
		UUT_REGISTER_OBJECT(Font);
		UUT_REGISTER_OBJECT(BitmapFont);

		// Effects
		UUT_REGISTER_OBJECT(Plasma);

		UUT_REGISTER_OBJECT(Texture2DLoader);
		UUT_REGISTER_OBJECT(BitmapFontLoader);

		UUT_REGISTER_MODULE(Renderer);
		UUT_REGISTER_MODULE(Graphics);
	}
}