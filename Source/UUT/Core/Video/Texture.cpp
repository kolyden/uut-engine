#include "Texture.h"

namespace uut
{
	Texture::Texture()
		: _size(0)
		, _access(TextureAccess::Static)
	{
	}

	Texture::~Texture()
	{
	}
}