#pragma once
#include <Core/String.h>

namespace uut
{
	class Version
	{
	public:
		Version();
		Version(uint16_t _major, uint16_t _minor);
		Version(uint16_t _major, uint16_t _minor, uint16_t _build);
		Version(uint16_t _major, uint16_t _minor, uint16_t _build, uint32_t _revision);

		bool operator ==(const Version& version) const;
		bool operator != (const Version& version) const;
		bool operator <(const Version& version) const;

		String ToString() const;

		uint16_t major;
		uint16_t minor;
		uint16_t build;
		union
		{
			uint32_t revision;
			struct
			{
				uint16_t majorRevision;
				uint16_t minorRevision;
			};
		};
	};
}