#include "VideoPlugin.h"
#include <Core/Reflection/Type.h>
#include "Core/Context.h"
#include "BufferObject.h"
#include "FreeCamera.h"
#include "Geometry.h"
#include "Image.h"
#include "IndexBuffer.h"
#include "Sprite.h"
#include "Texture.h"
#include "Texture2D.h"
#include "VertexBuffer.h"
#include "VertexDeclaration.h"
#include "Renderer.h"
#include "Graphics.h"
#include "imageEffects/Plasma.h"
#include "Loaders/Texture2DLoader.h"

namespace uut
{
	VideoPlugin::VideoPlugin()
		: Plugin("Video", PluginVersion(0, 1))
	{
	}

	void VideoPlugin::OnRegister()
	{
		// Buffers
		UUT_REGISTER_OBJECT(BufferObject);
		UUT_REGISTER_OBJECT(VertexBuffer);
		UUT_REGISTER_OBJECT(IndexBuffer);
		UUT_REGISTER_OBJECT(VertexDeclaration);

		// Textures
		UUT_REGISTER_OBJECT(Image);
		UUT_REGISTER_OBJECT(Texture);
		UUT_REGISTER_OBJECT(Texture2D);
		UUT_REGISTER_OBJECT(Sprite);

		UUT_REGISTER_OBJECT(Camera);
		UUT_REGISTER_OBJECT(FreeCamera);
		UUT_REGISTER_OBJECT(Geometry);

		// Effects
		UUT_REGISTER_OBJECT(Plasma);

		UUT_REGISTER_OBJECT(Texture2DLoader);

		UUT_REGISTER_MODULE(Renderer);
		UUT_REGISTER_MODULE(Graphics);
	}

	void VideoPlugin::OnUnregister()
	{
	}
}
