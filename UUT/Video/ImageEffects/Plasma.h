#pragma once
#include <Core/Object.h>
#include <Core/Math/Vector2i.h>
#include <Video/Color32.h>

namespace uut
{
	class Texture2D;

	class Plasma : public Object
	{
		UUT_OBJECT(uut, Plasma, Object)
	public:
		explicit Plasma(const Vector2i& size);
		virtual ~Plasma();

		void SetPaletteColor(int index, const Color32& color);

		bool Apply(Texture2D* texture, int shift = 0);

		const Vector2i& GetSize() const { return _size; }

	protected:
		Vector2i _size;
		uint32_t _lookupCount;
		int* _lookupTable;
		uint32_t _palette[256];
	};
}