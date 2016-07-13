#pragma once
#include "String.h"

namespace uut
{
	namespace detail
	{
		template<> struct StringConvert<int> {
			static String ToString(int value) { return std::to_string(value); }
		};

		template<> struct StringConvert<float> {
			static String ToString(float value) { return std::to_string(value); }
		};
	}

	namespace detail
	{
		template<int Index>
		struct ToStringArg
		{
			static const String Text;
		};
		template<int Index>const String ToStringArg<Index>::Text = String::Format("{%d}", Index);

		template<int Index, typename Arg>
		void Write(String& o, Arg&& arg)
		{
			auto& text = ToStringArg<Index>::Text;
			o.Replace(text, ToString<std::remove_reference_t<Arg>>(arg));
		}

		template<int Index, typename Arg, typename ...Args>
		void Write(String& o, Arg&& arg, Args&&... args)
		{
			auto& text = ToStringArg<Index>::Text;
			o.Replace(text, ToString<std::remove_reference_t<Arg>>(arg));
			Write<Index + 1>(o, std::forward<Args>(args)...);
		}
	}

	template<typename... Args>
	static String StringFormat(const String& format, Args... args)
	{
		String str = format;
		detail::Write<0>(str, args...);
		return str;
	}
}