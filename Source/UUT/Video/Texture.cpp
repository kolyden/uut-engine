#include "Texture.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(Texture)
	{}

	Texture::Texture()
		: _size(0)
		, _access(TextureAccess::Static)
	{
	}

	Texture::~Texture()
	{
	}
}