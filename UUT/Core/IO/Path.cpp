#include "Path.h"
#include "File.h"
#include "Directory.h"
#include <Core/HashString.h>
#include <Core/Math/Math.h>
#include <SDL2/SDL.h>

namespace std
{
	template <> struct hash<uut::String>
	{
		size_t operator()(const uut::String& str) const
		{
			// djb2 algorithm
			size_t h = 5381;
			for (int i = 0; i < str.Count(); i++)
				h = ((h << 5) + h) + str[i];

			return h;
		}
	};
}

namespace uut
{
	const Path Path::EMPTY;

	Path::Path()
		: _hash(0)
	{
	}

	Path::Path(const char* str)
	{
		*this = FromString(str);
	}

	Path::Path(const String& str)
	{
		*this = FromString(str);
	}

	Path::Path(const HashString& str)
	{
		*this = FromString(str.GetData());
	}

	Path::Path(const Path& path)
		: _components(path._components)
		, _hash(path._hash)
	{
	}

	Path::Path(Path&& path)
		: _components(std::move(path._components))
		, _hash(std::move(path._hash))
	{
	}

	bool Path::IsEmpty() const
	{
		return _hash == 0;
	}

	bool Path::IsExist() const
	{
		return File::Exists(*this) || Directory::Exist(*this);
	}

	String Path::GetExtension() const
	{
		const int count = _components.Count();
		if (count == 0)
			return String::Empty;

		const int pos = _components[count - 1].LastIndexOf(".");
		if (pos < 0) return String::Empty;

		return _components[count - 1].Substring(pos + 1);
	}

	bool Path::IsExtension(const String& ext, StringComparison comparsion) const
	{
		return GetExtension().Equals(ext, comparsion);
	}

	bool Path::IsExtensions(const String& ext1, const String& ext2, StringComparison comparsion) const
	{
		const auto ext = GetExtension();
		return
			ext.Equals(ext1, comparsion) ||
			ext.Equals(ext2, comparsion);
	}

	Path Path::GetDirectoryName() const
	{
		if (_components.Count() < 2)
			return EMPTY;

		return FromComponents(_components.GetRange(0, _components.Count() - 1));
	}

	const String& Path::GetFileName() const
	{
		const int count = _components.Count();
		return count > 0 ? _components[count - 1] : String::Empty;
	}

	String Path::GetFileNameWithoutExtension() const
	{
		if (IsEmpty())
			return String::Empty;

		auto name = _components[_components.Count() - 1];
		const int pos = name.LastIndexOf(".");
		if (pos > 0)
			name = name.Substring(0, pos);

		return name;
	}

	const List<String>& Path::GetComponents() const
	{
		return _components;
	}

	String Path::ToUtf8() const
	{
		return String::Join(_components, "/");
	}

	int Path::Compare(const Path& path) const
	{
		return Compare(*this, path);
	}

	bool Path::Equals(const Path& path) const
	{
		return Equals(*this, path);
	}

	int Path::Compare(const Path& a, const Path& b)
	{
		return Math::Compare(a._hash, b._hash);
// 		int ret = Math::compare(a._hash, b._hash);
// 		if (ret != 0)
// 			return ret;

// 		const int lng_a = a._components.Count();
// 		const int lng_b = b._components.Count();
// 		ret = Math::compare(lng_a, lng_b);
// 		if (ret != 0)
// 			return ret;
// 
// 		for (int i = 0; i < lng_a; i++)
// 		{
// 			ret = StringUtils::Compare(a._components[i], b._components[i],
// 				StringComparison::OrdinalIgnoreCase);
// 			if (ret != 0)
// 				return ret;
// 		}
// 
// 		return 0;
	}


	bool Path::Equals(const Path& a, const Path& b)
	{
		return Compare(a, b) == 0;
	}

	//////////////////////////////////////////////////////////////////////////
	bool Path::operator < (const Path& other) const
	{
		return Compare(other) < 0;
	}

	bool Path::operator > (const Path& other) const
	{
		return Compare(other) > 0;
	}

	bool Path::operator == (const Path& other) const
	{
		return Equals(other);
	}

	bool Path::operator != (const Path& other) const
	{
		return Equals(other);
	}

	Path& Path::operator=(const Path& other)
	{
		_components = other._components;
		_hash = other._hash;
		return *this;
	}

	Path& Path::operator=(Path&& other)
	{
		_components = std::move(other._components);
		_hash = std::move(other._hash);
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////
	Path Path::Combine(const Path& a, const Path& b)
	{
		if (a.IsEmpty() && b.IsEmpty())
			return Path::EMPTY;

		if (a.IsEmpty())
			return b;

		if (b.IsEmpty())
			return a;

		Path path;
		path._components += a._components;
		path._components += b._components;
		path.UpdateHash();

		return path;
	}

	Path Path::Combine(const Path& a, const Path& b, const Path& c)
	{
		return Path::Combine(Path::Combine(a, b), c);
	}

	Path Path::FromComponents(const List<String>& components)
	{
		if (components.IsEmpty())
			return Path::EMPTY;

		Path ret = components[0];
		for (uint i = 1; i < components.Count(); i++)
			ret = Combine(ret, components[i]);

		return ret;
	}

	Path Path::FromString(const String& _str)
	{
		String str = _str;
		str.Replace("\\", "/");

		Path path;
		str.Split('/', path._components);
		path.UpdateHash();

		return path;
	}

	Path Path::GetUserDirectory(const String& company, const String& appname)
	{
		return SDL_GetPrefPath(company, appname);
	}

	//////////////////////////////////////////////////////////////////////////
	void Path::UpdateHash()
	{
		static std::hash<String> hashFn;

		// FNV hash
		_hash = 2166136261;
		for(auto& str : _components)
			_hash = (_hash * 16777619) ^ hashFn(str);
	}
}