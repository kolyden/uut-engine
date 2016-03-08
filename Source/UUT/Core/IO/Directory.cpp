#include "Directory.h"
#include <Windows.h>
#include <functional>

namespace uut
{
	static const int g_buff_size = 512;
	static char g_buff[g_buff_size];
	static String g_asterisk = "*";

	static void FindEnumerate(const String& path, const String& searchMask, bool recursive,
		std::function<bool(const String& relPath, const WIN32_FIND_DATAA&)> func, const String& pathAdd = String::EMPTY)
	{
		WIN32_FIND_DATAA findData;
		HANDLE hFind = ::FindFirstFileA(path + "/" + searchMask, &findData);

		while (hFind != INVALID_HANDLE_VALUE)
		{
			const bool isDirectory = (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY;

			if (!isDirectory || (strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, "..") != 0))
			{
				if (!func(pathAdd, findData))
					break;

				if (recursive && isDirectory)
				{
					const String str = String("/") + findData.cFileName;
					FindEnumerate(path + str, searchMask, recursive, func, pathAdd + str);
				}
			}

			if (!::FindNextFileA(hFind, &findData))
				break;
		}

		if (hFind != INVALID_HANDLE_VALUE)
			::FindClose(hFind);
	}

	//////////////////////////////////////////////////////////////////////////
	bool Directory::Create(const Path& path)
	{
		if (path.IsEmpty())
			return false;

		if (Exist(path))
			return true;

		auto rootPath = path.GetDirectoryName();
		if (!rootPath.IsEmpty() && !Create(rootPath))
			return false;

		return ::CreateDirectoryA(path.ToUtf8(), nullptr) ? true : false;
	}

	bool Directory::Delete(const Path& path)
	{
		if (path.IsEmpty())
			return false;

		return ::RemoveDirectoryA(path.ToUtf8()) ? true : false;
	}

	bool Directory::Exist(const Path& path)
	{
		auto ret = ::GetFileAttributesA(path.ToUtf8());
		if (ret == INVALID_FILE_ATTRIBUTES)
			return false;

		return (ret & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY;
	}

	Path Directory::GetCurrent()
	{
		DWORD ret = ::GetCurrentDirectoryA(g_buff_size, g_buff);
		if (ret == 0)
			return Path::EMPTY;

		return String(g_buff);
	}

	List<Path> Directory::GetDirectories(const Path& path)
	{
		return GetDirectories(path, g_asterisk);
	}

	List<Path> Directory::GetDirectories(const Path& path, const String& searchPattern)
	{
		return GetDirectories(path, searchPattern, SearchOptions::TopDirectoryOnly);
	}

	List<Path> Directory::GetDirectories(const Path& path, const String& searchPattern, SearchOptions searchOptions)
	{
		List<Path> list;
		FindEnumerate(path.ToUtf8(), searchPattern,
			searchOptions == SearchOptions::AllDirectories ? true : false,
			[&list](const String& relPath, const WIN32_FIND_DATAA& find) -> bool
		{
			if ((find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY)
				return true;

			list << Path::Combine(relPath, find.cFileName);
			return true;
		});

// 		ENG_LOGDEBUGF("GetDirectories current:'%s', path:'%s', total:%d",
// 			GetCurrent().ToUtf8().GetData(), path.ToUtf8().GetData(), list.Count());
		return list;
	}

	List<Path> Directory::GetFiles(const Path& path)
	{
		return GetFiles(path, g_asterisk);
	}

	List<Path> Directory::GetFiles(const Path& path, const String& searchPattern)
	{
		return GetFiles(path, searchPattern, SearchOptions::TopDirectoryOnly);
	}

	List<Path> Directory::GetFiles(const Path& path, const String& searchPattern, SearchOptions searchOptions)
	{
		List<Path> list;
		FindEnumerate(path.ToUtf8(), searchPattern,
			searchOptions == SearchOptions::AllDirectories ? true : false,
			[&list](const String& relPath, const WIN32_FIND_DATAA& find) -> bool
		{
			if ((find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
				return true;

			list << Path::Combine(relPath, find.cFileName);
			return true;
		});

// 		ENG_LOGDEBUGF("GetFiles current:'%s', path:'%s', total:%d",
// 			GetCurrent().ToUtf8().GetData(), path.ToUtf8().GetData(), list.Count());
		return list;
	}

	List<Path> Directory::GetEntries(const Path& path)
	{
		return GetEntries(path, g_asterisk);
	}

	List<Path> Directory::GetEntries(const Path& path, const String& searchPattern)
	{
		return GetEntries(path, searchPattern, SearchOptions::TopDirectoryOnly);
	}

	List<Path> Directory::GetEntries(const Path& path, const String& searchPattern, SearchOptions searchOptions)
	{
		List<Path> list;
		FindEnumerate(path.ToUtf8(), searchPattern,
			searchOptions == SearchOptions::AllDirectories ? true : false,
			[&list](const String& relPath, const WIN32_FIND_DATAA& find) -> bool
		{
			list << Path::Combine(relPath, find.cFileName);
			return true;
		});

// 		ENG_LOGDEBUGF("GetEntries current:'%s', path:'%s', total:%d",
// 			GetCurrent().ToUtf8().GetData(), path.ToUtf8().GetData(), list.Count());
		return list;
	}
}