#pragma once
#include <Core/Collections/List.h>
#include <Core/String.h>

namespace uut
{
	class HashString;
	class String;

	class Path
	{
	public:
		Path();
		Path(const char* str);
		Path(const String& str);
		Path(const HashString& str);
		Path(const Path& path);
		Path(Path&& path);

		bool IsEmpty() const;
		bool IsExist() const;
		size_t GetHash() const;

		String GetExtension() const;
		bool IsExtension(const String& ext,
			StringComparison comparsion = StringComparison::OrdinalIgnoreCase) const;
		bool IsExtensions(const String& ext1, const String& ext2,
			StringComparison comparsion = StringComparison::OrdinalIgnoreCase) const;

		Path GetDirectoryName() const;
		const String& GetFileName() const;
		String GetFileNameWithoutExtension() const;
		String GetFullPath() const;

		const List<String>& GetComponents() const;

		String ToUtf8() const;

		int Compare(const Path& path) const;
		bool Equals(const Path& path) const;

		static int Compare(const Path& a, const Path& b);
		static bool Equals(const Path& a, const Path& b);

		bool operator < (const Path& other) const;
		bool operator > (const Path& other) const;

		bool operator == (const Path& other) const;
		bool operator != (const Path& other) const;

		Path& operator = (const Path& other);
		Path& operator = (Path&& other);

		friend Path operator+(const Path& path, const String& txt) { return path.ToUtf8() + txt; }

		static Path Combine(const Path& a, const Path& b);
		static Path Combine(const Path& a, const Path& b, const Path& c);
		static Path FromComponents(const List<String>& components);
		static Path FromString(const String& str);

		static Path GetUserDirectory(const String& company, const String& appname);

		static const Path Empty;

	protected:
		List<String> _components;
		size_t _hash;

		void UpdateHash();
	};
}
