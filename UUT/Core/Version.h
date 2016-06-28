#pragma once
#include <Core/String.h>

namespace uut
{
	struct Version
	{
		Version();
		Version(uint16_t _major, uint16_t _minor);

		bool operator ==(const Version& version) const;
		bool operator != (const Version& version) const;
		bool operator <(const Version& version) const;

		String ToString() const;

		uint16_t major;
		uint16_t minor;
	};
}