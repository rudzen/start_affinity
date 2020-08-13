#pragma once

#include <type_traits>

#include <winbase.h>

namespace misc
{

constexpr bool is_set(const DWORD dw, const int bit)
{
  return dw & bit;
}

template<typename T>
constexpr T set_bit(const T dw, const int bit)
{
  static_assert(std::is_integral_v<T>);
  return dw | bit;
}

inline bool is_valid_os()
{

  // check operating system

  OSVERSIONINFO verinfo{};

  verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

  return !GetVersionEx(&verinfo) || verinfo.dwPlatformId != VER_PLATFORM_WIN32_WINDOWS;
}

}   // namespace misc