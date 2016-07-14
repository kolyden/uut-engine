#include "Version.h"

namespace uut
{
	Version::Version()
		: major(0)
		, minor(0)
		, build(0)
		, revision(0)
	{}

	Version::Version(uint16_t _major, uint16_t _minor)
		: major(_major)
		, minor(_minor)
		, build(0)
		, revision(0)
	{}

	Version::Version(uint16_t _major, uint16_t _minor, uint16_t _build)
		: major(_major)
		, minor(_minor)
		, build(_build)
		, revision(0)
	{
	}

	Version::Version(uint16_t _major, uint16_t _minor, uint16_t _build, uint32_t _revision)
		: major(_major)
		, minor(_minor)
		, build(_build)
		, revision(_revision)
	{
	}

	bool Version::operator==(const Version& other) const
	{
		return major == other.major && minor == other.minor &&
			build == other.build && revision == other.revision;
	}

	bool Version::operator!=(const Version& other) const
	{
		return major != other.major || minor != other.minor ||
			build != other.build || revision != other.revision;
	}

	bool Version::operator<(const Version& other) const
	{
		if (major != other.major)
			return major < other.major;
		if (minor != other.minor)
			return minor < other.minor;
		if (build != other.build)
			return build < other.build;
		if (revision != other.revision)
			return revision < other.revision;
		return true;

// 		if (major == version.major)
// 			return minor < version.minor;
// 
// 		return major < version.major;
	}

	String Version::ToString() const
	{
		if (revision > 0)
			return String::Format("%u.%u.%u.%u", major, minor, build, revision);

		if (build > 0)
			return String::Format("%u.%u.%u", major, minor, build);

		return String::Format("%u.%u", major, minor);
	}
}