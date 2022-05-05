#pragma once
#include<iostream>
#include<fmt/core.h>
#include<fmt/color.h>
namespace ak
{
	class Log
	{
		static bool isLogEnabled;
	public:
		static void Enable(bool v)
		{
			isLogEnabled = v;
		}
		template <typename... T>
		static void Print(fmt::format_string<T...> fmt, T&&... args)
		{
			if (isLogEnabled)
			{
				fmt::print(fmt, args...);
			}
		}
		template <typename S, typename... Args>
		 static void Error( const S& format_str, const Args&... args)
		{
			if (isLogEnabled)
			{
				fmt::print(fg(fmt::color::red), format_str, args...);
			}
		}
	};
}

