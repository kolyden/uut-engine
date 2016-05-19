#pragma once
#include "Path.h"

namespace uut
{
	enum class SearchOptions
	{
		AllDirectories,
		TopDirectoryOnly,
	};

	class Directory
	{
	public:
		static bool Create(const Path& path);
		static bool Delete(const Path& path);

		static bool Exist(const Path& path);

		static Path GetCurrent();

		static List<Path> GetDirectories(const Path& path);
		static List<Path> GetDirectories(const Path& path, const String& searchPattern);
		static List<Path> GetDirectories(const Path& path, const String& searchPattern, SearchOptions searchOptions);

		static List<Path> GetFiles(const Path& path);
		static List<Path> GetFiles(const Path& path, const String& searchPattern);
		static List<Path> GetFiles(const Path& path, const String& searchPattern, SearchOptions searchOptions);

		static List<Path> GetEntries(const Path& path);
		static List<Path> GetEntries(const Path& path, const String& searchPattern);
		static List<Path> GetEntries(const Path& path, const String& searchPattern, SearchOptions searchOptions);

	protected:
		Directory() = delete;
	};
}