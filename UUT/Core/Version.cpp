#include "Version.h"

namespace uut
{
	Version::Version()
		: major()
		, minor(0)
	{}

	Version::Version(uint16_t _major, uint16_t _minor)
		: major(_major)
		, minor(_minor)
	{}

	bool Version::operator==(const Version& version) const
	{
		return major == version.major && minor == version.minor;
	}

	bool Version::operator!=(const Version& version) const
	{
		return major != version.major || minor != version.minor;
	}

	bool Version::operator<(const Version& version) const
	{
		if (major == version.major)
			return minor < version.minor;

		return major < version.major;
	}

	String Version::ToString() const
	{
		return String::Format("%u.%u", major, minor);
	}
}