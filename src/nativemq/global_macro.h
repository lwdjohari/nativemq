#pragma once

#define NATIVEMQ_NAMESPACE namespace nativemq
#define NATIVEMQ_BEGIN_NAMESPACE NATIVEMQ_NAMESPACE {
#define NATIVEMQ_MAKE_NAMESPACE(arg) namespace arg {
#define NATIVEMQ_END_NAMESPACE }
#define NATIVEMQ_INNER_NAMESPACE(arg) \
  NATIVEMQ_BEGIN_NAMESPACE            \
  namespace arg {
#define NATIVEMQ_INNER_END_NAMESPACE \
  }                                  \
  }

// Architecture
#define NATIVEMQ_ARCH_32BIT 0
#define NATIVEMQ_ARCH_64BIT 0

// HW Accelarator
#if defined(__AVX2__)
  #define NATIVEMQ_UTF8_ACCELERATOR "AVX2"
  #define NATIVEMQ_USE_MQTT_UTF8_AVX2
#elif defined(__SSE4_2__)
  #define NATIVEMQ_UTF8_ACCELERATOR "SSE4.2"
  #define NATIVEMQ_USE_MQTT_UTF8_SSE42
#elif defined(__ARM_NEON) || defined(__ARM_NEON__)
  #define NATIVEMQ_UTF8_ACCELERATOR "NEON"
  #define NATIVEMQ_USE_MQTT_UTF8_NEON
#else
  #define NATIVEMQ_UTF8_ACCELERATOR "SCALAR"
  #define NATIVEMQ_USE_MQTT_UTF8_SCALAR
#endif


// Compiler
#define NATIVEMQ_COMPILER_CLANG 0
#define NATIVEMQ_COMPILER_CLANG_ANALYZER 0
#define NATIVEMQ_COMPILER_GCC 0
#define NATIVEMQ_COMPILER_MSVC 0

// Endianness
#define NATIVEMQ_ENDIAN_BIG 0
#define NATIVEMQ_ENDIAN_LITTLE 0

// CPU
#define NATIVEMQ_CPU_ARM 0
#define NATIVEMQ_CPU_JIT 0
#define NATIVEMQ_CPU_MIPS 0
#define NATIVEMQ_CPU_PPC 0
#define NATIVEMQ_CPU_RISCV 0
#define NATIVEMQ_CPU_X86 0

// C Runtime
#define NATIVEMQ_CRT_BIONIC 0
#define NATIVEMQ_CRT_BSD 0
#define NATIVEMQ_CRT_GLIBC 0
#define NATIVEMQ_CRT_LIBCXX 0
#define NATIVEMQ_CRT_MINGW 0
#define NATIVEMQ_CRT_MSVC 0
#define NATIVEMQ_CRT_NEWLIB 0

#ifndef NATIVEMQ_CRT_NONE
#define NATIVEMQ_CRT_NONE 0
#endif  // NATIVEMQ_CRT_NONE

// Language standard version
#define NATIVEMQ_CPP17 201703L
#define NATIVEMQ_CPP20 202002L
#define NATIVEMQ_CPP23 202207L

// Platform
#define NATIVEMQ_PLATFORM_ANDROID 0
#define NATIVEMQ_PLATFORM_BSD 0
#define NATIVEMQ_PLATFORM_WEBGL 0
#define NATIVEMQ_PLATFORM_HAIKU 0
#define NATIVEMQ_PLATFORM_HURD 0
#define NATIVEMQ_PLATFORM_IOS 0
#define NATIVEMQ_PLATFORM_LINUX 0
#define NATIVEMQ_PLATFORM_NX 0
#define NATIVEMQ_PLATFORM_OSX 0
#define NATIVEMQ_PLATFORM_PS4 0
#define NATIVEMQ_PLATFORM_PS5 0
#define NATIVEMQ_PLATFORM_RPI 0
#define NATIVEMQ_PLATFORM_VISIONOS 0
#define NATIVEMQ_PLATFORM_WINDOWS 0
#define NATIVEMQ_PLATFORM_WINRT 0
#define NATIVEMQ_PLATFORM_XBOXONE 0

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Compilers
#if defined(__clang__)
// clang defines __GNUC__ or _MSC_VER
#undef NATIVEMQ_COMPILER_CLANG
#define NATIVEMQ_COMPILER_CLANG \
  (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#if defined(__clang_analyzer__)
#undef NATIVEMQ_COMPILER_CLANG_ANALYZER
#define NATIVEMQ_COMPILER_CLANG_ANALYZER 1
#endif  // defined(__clang_analyzer__)
#elif defined(_MSC_VER)
#undef NATIVEMQ_COMPILER_MSVC
#define NATIVEMQ_COMPILER_MSVC _MSC_VER
#elif defined(__GNUC__)
#undef NATIVEMQ_COMPILER_GCC
#define NATIVEMQ_COMPILER_GCC \
  (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#error "NATIVEMQ_COMPILER_* is not defined!"
#endif  //

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Architectures
#if defined(__arm__) || defined(__aarch64__) || defined(_M_ARM)
#undef NATIVEMQ_CPU_ARM
#define NATIVEMQ_CPU_ARM 1
#define NATIVEMQ_CACHE_LINE_SIZE 64
#elif defined(__MIPSEL__) || defined(__mips_isa_rev) || defined(__mips64)
#undef NATIVEMQ_CPU_MIPS
#define NATIVEMQ_CPU_MIPS 1
#define NATIVEMQ_CACHE_LINE_SIZE 64
#elif defined(_M_PPC) || defined(__powerpc__) || defined(__powerpc64__)
#undef NATIVEMQ_CPU_PPC
#define NATIVEMQ_CPU_PPC 1
#define NATIVEMQ_CACHE_LINE_SIZE 128
#elif defined(__riscv) || defined(__riscv__) || defined(RISCVEL)
#undef NATIVEMQ_CPU_RISCV
#define NATIVEMQ_CPU_RISCV 1
#define NATIVEMQ_CACHE_LINE_SIZE 64
#elif defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || \
    defined(__x86_64__)
#undef NATIVEMQ_CPU_X86
#define NATIVEMQ_CPU_X86 1
#define NATIVEMQ_CACHE_LINE_SIZE 64
#else  // Doesn't have CPU defined.
#undef NATIVEMQ_CPU_JIT
#define NATIVEMQ_CPU_JIT 1
#define NATIVEMQ_CACHE_LINE_SIZE 64
#endif  //

#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__) ||    \
    defined(__64BIT__) || defined(__mips64) || defined(__powerpc64__) || \
    defined(__ppc64__) || defined(__LP64__)
#undef NATIVEMQ_ARCH_64BIT
#define NATIVEMQ_ARCH_64BIT 64
#else
#undef NATIVEMQ_ARCH_32BIT
#define NATIVEMQ_ARCH_32BIT 32
#endif  //

#if NATIVEMQ_CPU_PPC
// __BIG_ENDIAN__ is gcc predefined macro
#if defined(__BIG_ENDIAN__)
#undef NATIVEMQ_ENDIAN_BIG
#define NATIVEMQ_ENDIAN_BIG 1
#else
#undef NATIVEMQ_ENDIAN_LITTLE
#define NATIVEMQ_ENDIAN_LITTLE 1
#endif
#else
#undef NATIVEMQ_ENDIAN_LITTLE
#define NATIVEMQ_ENDIAN_LITTLE 1
#endif  // NATIVEMQ_CPU_PPC

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Operating_Systems
#if defined(_DURANGO) || defined(_XBOX_ONE)
#undef NATIVEMQ_PLATFORM_XBOXONE
#define NATIVEMQ_PLATFORM_XBOXONE 1
#elif defined(_WIN32) || defined(_WIN64)
// http://msdn.microsoft.com/en-us/library/6sehtctf.aspx
#ifndef NOMINMAX
#define NOMINMAX
#endif  // NOMINMAX
//  If _USING_V110_SDK71_ is defined it means we are using the v110_xp or
//  v120_xp toolset.
#if defined(_MSC_VER) && (_MSC_VER >= 1700) && !defined(_USING_V110_SDK71_)
#include <winapifamily.h>
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1700) && (!_USING_V110_SDK71_)
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
#undef NATIVEMQ_PLATFORM_WINDOWS
#if !defined(WINVER) && !defined(_WIN32_WINNT)
#if NATIVEMQ_ARCH_64BIT
//				When building 64-bit target Win7 and above.
#define WINVER 0x0601
#define _WIN32_WINNT 0x0601
#else
//				Windows Server 2003 with SP1, Windows XP with
// SP2 and above
#define WINVER 0x0502
#define _WIN32_WINNT 0x0502
#endif  // NATIVEMQ_ARCH_64BIT
#endif  // !defined(WINVER) && !defined(_WIN32_WINNT)
#define NATIVEMQ_PLATFORM_WINDOWS _WIN32_WINNT
#else
#undef NATIVEMQ_PLATFORM_WINRT
#define NATIVEMQ_PLATFORM_WINRT 1
#endif
#elif defined(__ANDROID__)
// Android compiler defines __linux__
#include <sys/cdefs.h>  // Defines __BIONIC__ and includes android/api-level.h
#undef NATIVEMQ_PLATFORM_ANDROID
#define NATIVEMQ_PLATFORM_ANDROID __ANDROID_API__
#elif defined(__VCCOREVER__)
// RaspberryPi compiler defines __linux__
#undef NATIVEMQ_PLATFORM_RPI
#define NATIVEMQ_PLATFORM_RPI 1
#elif defined(__linux__)
#undef NATIVEMQ_PLATFORM_LINUX
#define NATIVEMQ_PLATFORM_LINUX 1
#elif defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__) || \
    defined(__ENVIRONMENT_TV_OS_VERSION_MIN_REQUIRED__)
#undef NATIVEMQ_PLATFORM_IOS
#define NATIVEMQ_PLATFORM_IOS 1
#elif defined(__has_builtin) && __has_builtin(__is_target_os) && \
    __is_target_os(xros)
#undef NATIVEMQ_PLATFORM_VISIONOS
#define NATIVEMQ_PLATFORM_VISIONOS 1
#elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
#undef NATIVEMQ_PLATFORM_OSX
#define NATIVEMQ_PLATFORM_OSX __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__
#elif defined(__EMSCRIPTEN__)
#include <emscripten/version.h>
#undef NATIVEMQ_PLATFORM_WEBGL
#define NATIVEMQ_PLATFORM_WEBGL                                \
  (__EMSCRIPTEN_major__ * 10000 + __EMSCRIPTEN_minor__ * 100 + \
   __EMSCRIPTEN_tiny__)
#elif defined(__ORBIS__)
#undef NATIVEMQ_PLATFORM_PS4
#define NATIVEMQ_PLATFORM_PS4 1
#elif defined(__PROSPERO__)
#undef NATIVEMQ_PLATFORM_PS5
#define NATIVEMQ_PLATFORM_PS5 1
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || \
    defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
#undef NATIVEMQ_PLATFORM_BSD
#define NATIVEMQ_PLATFORM_BSD 1
#elif defined(__GNU__)
#undef NATIVEMQ_PLATFORM_HURD
#define NATIVEMQ_PLATFORM_HURD 1
#elif defined(__NX__)
#undef NATIVEMQ_PLATFORM_NX
#define NATIVEMQ_PLATFORM_NX 1
#elif defined(__HAIKU__)
#undef NATIVEMQ_PLATFORM_HAIKU
#define NATIVEMQ_PLATFORM_HAIKU 1
#endif  //

#if !NATIVEMQ_CRT_NONE
// https://sourceforge.net/p/predef/wiki/Libraries/
#if defined(__BIONIC__)
#undef NATIVEMQ_CRT_BIONIC
#define NATIVEMQ_CRT_BIONIC 1
#elif defined(_MSC_VER)
#undef NATIVEMQ_CRT_MSVC
#define NATIVEMQ_CRT_MSVC 1
#elif defined(__GLIBC__)
#undef NATIVEMQ_CRT_GLIBC
#define NATIVEMQ_CRT_GLIBC (__GLIBC__ * 10000 + __GLIBC_MINOR__ * 100)
#elif defined(__MINGW32__) || defined(__MINGW64__)
#undef NATIVEMQ_CRT_MINGW
#define NATIVEMQ_CRT_MINGW 1
#elif defined(__apple_build_version__) || defined(__ORBIS__) || \
    defined(__EMSCRIPTEN__) || defined(__llvm__) || defined(__HAIKU__)
#undef NATIVEMQ_CRT_LIBCXX
#define NATIVEMQ_CRT_LIBCXX 1
#elif NATIVEMQ_PLATFORM_BSD
#undef NATIVEMQ_CRT_BSD
#define NATIVEMQ_CRT_BSD 1
#endif  //

#if !NATIVEMQ_CRT_BIONIC && !NATIVEMQ_CRT_BSD && !NATIVEMQ_CRT_GLIBC &&  \
    !NATIVEMQ_CRT_LIBCXX && !NATIVEMQ_CRT_MINGW && !NATIVEMQ_CRT_MSVC && \
    !NATIVEMQ_CRT_NEWLIB
#undef NATIVEMQ_CRT_NONE
#define NATIVEMQ_CRT_NONE 1
#endif  // NATIVEMQ_CRT_*
#endif  // !NATIVEMQ_CRT_NONE

///
#define NATIVEMQ_PLATFORM_POSIX                                                \
  (0 || NATIVEMQ_PLATFORM_ANDROID || NATIVEMQ_PLATFORM_BSD ||                  \
   NATIVEMQ_PLATFORM_WEBGL || NATIVEMQ_PLATFORM_HAIKU ||                       \
   NATIVEMQ_PLATFORM_HURD || NATIVEMQ_PLATFORM_IOS ||                          \
   NATIVEMQ_PLATFORM_LINUX || NATIVEMQ_PLATFORM_NX || NATIVEMQ_PLATFORM_OSX || \
   NATIVEMQ_PLATFORM_PS4 || NATIVEMQ_PLATFORM_PS5 || NATIVEMQ_PLATFORM_RPI ||  \
   NATIVEMQ_PLATFORM_VISIONOS)

///
#define NATIVEMQ_PLATFORM_NONE                                                 \
  !(0 || NATIVEMQ_PLATFORM_ANDROID || NATIVEMQ_PLATFORM_BSD ||                 \
    NATIVEMQ_PLATFORM_WEBGL || NATIVEMQ_PLATFORM_HAIKU ||                      \
    NATIVEMQ_PLATFORM_HURD || NATIVEMQ_PLATFORM_IOS ||                         \
    NATIVEMQ_PLATFORM_LINUX || NATIVEMQ_PLATFORM_NX ||                         \
    NATIVEMQ_PLATFORM_OSX || NATIVEMQ_PLATFORM_PS4 || NATIVEMQ_PLATFORM_PS5 || \
    NATIVEMQ_PLATFORM_RPI || NATIVEMQ_PLATFORM_VISIONOS ||                     \
    NATIVEMQ_PLATFORM_WINDOWS || NATIVEMQ_PLATFORM_WINRT ||                    \
    NATIVEMQ_PLATFORM_XBOXONE)

///
#define NATIVEMQ_PLATFORM_OS_CONSOLE                     \
  (0 || NATIVEMQ_PLATFORM_NX || NATIVEMQ_PLATFORM_PS4 || \
   NATIVEMQ_PLATFORM_PS5 || NATIVEMQ_PLATFORM_WINRT ||   \
   NATIVEMQ_PLATFORM_XBOXONE)

///
#define NATIVEMQ_PLATFORM_OS_DESKTOP                        \
  (0 || NATIVEMQ_PLATFORM_BSD || NATIVEMQ_PLATFORM_HAIKU || \
   NATIVEMQ_PLATFORM_HURD || NATIVEMQ_PLATFORM_LINUX ||     \
   NATIVEMQ_PLATFORM_OSX || NATIVEMQ_PLATFORM_WINDOWS)

///
#define NATIVEMQ_PLATFORM_OS_EMBEDDED (0 || NATIVEMQ_PLATFORM_RPI)

///
#define NATIVEMQ_PLATFORM_OS_MOBILE \
  (0 || NATIVEMQ_PLATFORM_ANDROID || NATIVEMQ_PLATFORM_IOS)

///
#define NATIVEMQ_PLATFORM_OS_WEB (0 || NATIVEMQ_PLATFORM_WEBGL)

///
#if NATIVEMQ_COMPILER_GCC
#define NATIVEMQ_COMPILER_NAME                                \
  "GCC " NATIVEMQ_STRINGIZE(__GNUC__) "." NATIVEMQ_STRINGIZE( \
      __GNUC_MINOR__) "." NATIVEMQ_STRINGIZE(__GNUC_PATCHLEVEL__)
#elif NATIVEMQ_COMPILER_CLANG
#define NATIVEMQ_COMPILER_NAME                                         \
  "Clang " NATIVEMQ_STRINGIZE(__clang_major__) "." NATIVEMQ_STRINGIZE( \
      __clang_minor__) "." NATIVEMQ_STRINGIZE(__clang_patchlevel__)
#elif NATIVEMQ_COMPILER_MSVC
#if NATIVEMQ_COMPILER_MSVC >= 1930  // Visual Studio 2022
#define NATIVEMQ_COMPILER_NAME "MSVC 17.0"
#elif NATIVEMQ_COMPILER_MSVC >= 1920  // Visual Studio 2019
#define NATIVEMQ_COMPILER_NAME "MSVC 16.0"
#elif NATIVEMQ_COMPILER_MSVC >= 1910  // Visual Studio 2017
#define NATIVEMQ_COMPILER_NAME "MSVC 15.0"
#elif NATIVEMQ_COMPILER_MSVC >= 1900  // Visual Studio 2015
#define NATIVEMQ_COMPILER_NAME "MSVC 14.0"
#elif NATIVEMQ_COMPILER_MSVC >= 1800  // Visual Studio 2013
#define NATIVEMQ_COMPILER_NAME "MSVC 12.0"
#elif NATIVEMQ_COMPILER_MSVC >= 1700  // Visual Studio 2012
#define NATIVEMQ_COMPILER_NAME "MSVC 11.0"
#elif NATIVEMQ_COMPILER_MSVC >= 1600  // Visual Studio 2010
#define NATIVEMQ_COMPILER_NAME "MSVC 10.0"
#elif NATIVEMQ_COMPILER_MSVC >= 1500  // Visual Studio 2008
#define NATIVEMQ_COMPILER_NAME "MSVC 9.0"
#else
#define NATIVEMQ_COMPILER_NAME "MSVC"
#endif  //
#endif  // NATIVEMQ_COMPILER_

#if NATIVEMQ_PLATFORM_ANDROID
#define NATIVEMQ_PLATFORM_NAME \
  "Android " NATIVEMQ_STRINGIZE(NATIVEMQ_PLATFORM_ANDROID)
#elif NATIVEMQ_PLATFORM_BSD
#define NATIVEMQ_PLATFORM_NAME "BSD"
#elif NATIVEMQ_PLATFORM_WEBGL
#define NATIVEMQ_PLATFORM_NAME                                                   \
  "Emscripten " NATIVEMQ_STRINGIZE(__EMSCRIPTEN_major__) "." NATIVEMQ_STRINGIZE( \
      __EMSCRIPTEN_minor__) "." NATIVEMQ_STRINGIZE(__EMSCRIPTEN_tiny__)
#elif NATIVEMQ_PLATFORM_HAIKU
#define NATIVEMQ_PLATFORM_NAME "Haiku"
#elif NATIVEMQ_PLATFORM_HURD
#define NATIVEMQ_PLATFORM_NAME "Hurd"
#elif NATIVEMQ_PLATFORM_IOS
#define NATIVEMQ_PLATFORM_NAME "iOS"
#elif NATIVEMQ_PLATFORM_LINUX
#define NATIVEMQ_PLATFORM_NAME "Linux"
#elif NATIVEMQ_PLATFORM_NONE
#define NATIVEMQ_PLATFORM_NAME "None"
#elif NATIVEMQ_PLATFORM_NX
#define NATIVEMQ_PLATFORM_NAME "NX"
#elif NATIVEMQ_PLATFORM_OSX
#define NATIVEMQ_PLATFORM_NAME "macOS"
#elif NATIVEMQ_PLATFORM_PS4
#define NATIVEMQ_PLATFORM_NAME "PlayStation 4"
#elif NATIVEMQ_PLATFORM_PS5
#define NATIVEMQ_PLATFORM_NAME "PlayStation 5"
#elif NATIVEMQ_PLATFORM_RPI
#define NATIVEMQ_PLATFORM_NAME "RaspberryPi"
#elif NATIVEMQ_PLATFORM_VISIONOS
#define NATIVEMQ_PLATFORM_NAME "visionOS"
#elif NATIVEMQ_PLATFORM_WINDOWS
#define NATIVEMQ_PLATFORM_NAME "Windows"
#elif NATIVEMQ_PLATFORM_WINRT
#define NATIVEMQ_PLATFORM_NAME "WinRT"
#elif NATIVEMQ_PLATFORM_XBOXONE
#define NATIVEMQ_PLATFORM_NAME "Xbox One"
#else
#error "Unknown NATIVEMQ_PLATFORM!"
#endif  // NATIVEMQ_PLATFORM_

#if NATIVEMQ_CPU_ARM
#define NATIVEMQ_CPU_NAME "ARM"
#elif NATIVEMQ_CPU_JIT
#define NATIVEMQ_CPU_NAME "JIT-VM"
#elif NATIVEMQ_CPU_MIPS
#define NATIVEMQ_CPU_NAME "MIPS"
#elif NATIVEMQ_CPU_PPC
#define NATIVEMQ_CPU_NAME "PowerPC"
#elif NATIVEMQ_CPU_RISCV
#define NATIVEMQ_CPU_NAME "RISC-V"
#elif NATIVEMQ_CPU_X86
#define NATIVEMQ_CPU_NAME "x86"
#endif  // NATIVEMQ_CPU_

#if NATIVEMQ_CRT_BIONIC
#define NATIVEMQ_CRT_NAME "Bionic libc"
#elif NATIVEMQ_CRT_BSD
#define NATIVEMQ_CRT_NAME "BSD libc"
#elif NATIVEMQ_CRT_GLIBC
#define NATIVEMQ_CRT_NAME "GNU C Library"
#elif NATIVEMQ_CRT_MSVC
#define NATIVEMQ_CRT_NAME "MSVC C Runtime"
#elif NATIVEMQ_CRT_MINGW
#define NATIVEMQ_CRT_NAME "MinGW C Runtime"
#elif NATIVEMQ_CRT_LIBCXX
#define NATIVEMQ_CRT_NAME "Clang C Library"
#elif NATIVEMQ_CRT_NEWLIB
#define NATIVEMQ_CRT_NAME "Newlib"
#elif NATIVEMQ_CRT_NONE
#define NATIVEMQ_CRT_NAME "None"
#else
#error "Unknown NATIVEMQ_CRT!"
#endif  // NATIVEMQ_CRT_

#if NATIVEMQ_ARCH_32BIT
#define NATIVEMQ_ARCH_NAME "32-bit"
#elif NATIVEMQ_ARCH_64BIT
#define NATIVEMQ_ARCH_NAME "64-bit"
#endif  // NATIVEMQ_ARCH_

#if defined(__cplusplus)
#if NATIVEMQ_COMPILER_MSVC && defined(_MSVC_LANG) && _MSVC_LANG != __cplusplus
#error "When using MSVC you must set /Zc:__cplusplus compiler option."
#endif  // NATIVEMQ_COMPILER_MSVC && defined(_MSVC_LANG) && _MSVC_LANG !=
        // __cplusplus

#if __cplusplus < NATIVEMQ_CPP17
#error "C++17 standard support is required to build."
#elif __cplusplus < NATIVEMQ_CPP20
#define NATIVEMQ_CPP_NAME "C++17"
#elif __cplusplus < NATIVEMQ_CPP23
#define NATIVEMQ_CPP_NAME "C++20"
#else
// See: https://gist.github.com/bkaradzic/2e39896bc7d8c34e042b#orthodox-c
#define NATIVEMQ_CPP_NAME "C++WayTooModern"
#endif  // NATIVEMQ_CPP_NAME
#else
#define NATIVEMQ_CPP_NAME "C++Unknown"
#endif  // defined(__cplusplus)

#if NATIVEMQ_COMPILER_MSVC && (!defined(_MSVC_TRADITIONAL) || _MSVC_TRADITIONAL)
#error "When using MSVC you must set /Zc:preprocessor compiler option."
#endif  // NATIVEMQ_COMPILER_MSVC && (!defined(_MSVC_TRADITIONAL) ||
        // _MSVC_TRADITIONAL)

#if NATIVEMQ_PLATFORM_OSX && NATIVEMQ_PLATFORM_OSX < 130000
// #error "Minimum supported macOS version is 13.00.\n"
#elif NATIVEMQ_PLATFORM_IOS && NATIVEMQ_PLATFORM_IOS < 160000
// #error "Minimum supported macOS version is 16.00.\n"
#endif  // NATIVEMQ_PLATFORM_OSX < 130000

#if NATIVEMQ_ENDIAN_BIG
static_assert(false, "\n\n"
                     "\t** IMPORTANT! **\n\n"
                     "\tThe code was not tested for big endian, and big endian "
                     "CPU is considered unsupported.\n"
                     "\t\n");
#endif  // NATIVEMQ_ENDIAN_BIG

#if NATIVEMQ_PLATFORM_BSD || NATIVEMQ_PLATFORM_HAIKU || NATIVEMQ_PLATFORM_HURD
static_assert(false, "\n\n"
                     "\t** IMPORTANT! **\n\n"
                     "\tYou're compiling for unsupported platform!\n"
                     "\tIf you wish to support this platform, make your own "
                     "fork, and modify code for _yourself_.\n"
                     "\t\n"
                     "\tDo not submit PR to main repo, it won't be considered, "
                     "and it would code rot anyway. I have no ability\n"
                     "\tto test on these platforms, and over years there "
                     "wasn't any serious contributor who wanted to take\n"
                     "\tburden of maintaining code for these platforms.\n"
                     "\t\n");
#endif  // NATIVEMQ_PLATFORM_*

#if NATIVEMQ_COMPILER_CLANG || NATIVEMQ_COMPILER_GCC
#define NATIVEMQ_FN_EXPERIMENTAL \
  [[gnu::warning("Experimental feature, subject to change")]]
#elif NATIVEMQ_COMPILER_MSVC && \
    (!defined(_MSVC_TRADITIONAL) || _MSVC_TRADITIONAL)
#define NATIVEMQ_FN_EXPERIMENTAL \
  __declspec(deprecated("Experimental feature, subject to change"))
#else
#define NATIVEMQ_FN_EXPERIMENTAL
#endif

#if NATIVEMQ_COMPILER_CLANG || NATIVEMQ_COMPILER_GCC
#define NATIVEMQ_FN_WIP                                                        \
  [[gnu::warning("Work-in-progress feature, subject to change or not covered " \
                 "all features")]]
#elif NATIVEMQ_COMPILER_MSVC && \
    (!defined(_MSVC_TRADITIONAL) || _MSVC_TRADITIONAL)
#define NATIVEMQ_FN_WIP                                                       \
  __declspec(deprecated("Work-in-progress feature, subject to change or not " \
                        "covered all features"))
#else
#define NATIVEMQ_FN_WIP
#endif

#include <iostream>
#include <type_traits>

#define NATIVEMQ_ENUM_CLASS_ENABLE_BITMASK_OPERATORS(T)                  \
  inline T operator|(T lhs, T rhs) {                                     \
    return static_cast<T>(static_cast<std::underlying_type_t<T>>(lhs) |  \
                          static_cast<std::underlying_type_t<T>>(rhs));  \
  }                                                                      \
                                                                         \
  inline T operator&(T lhs, T rhs) {                                     \
    return static_cast<T>(static_cast<std::underlying_type_t<T>>(lhs) &  \
                          static_cast<std::underlying_type_t<T>>(rhs));  \
  }                                                                      \
                                                                         \
  inline T operator^(T lhs, T rhs) {                                     \
    return static_cast<T>(static_cast<std::underlying_type_t<T>>(lhs) ^  \
                          static_cast<std::underlying_type_t<T>>(rhs));  \
  }                                                                      \
                                                                         \
  inline T operator~(T rhs) {                                            \
    return static_cast<T>(~static_cast<std::underlying_type_t<T>>(rhs)); \
  }

#define NATIVEMQ_ENUM_CLASS_DISPLAY_TRAIT(E)                             \
  inline std::ostream& operator<<(std::ostream& os, E e) {               \
    return os << static_cast<typename std::underlying_type<E>::type>(e); \
  }

#define NVMQ_STR(s) std::string(s)
#define NVMQ_ESTR std::string{}

NATIVEMQ_BEGIN_NAMESPACE

namespace impl {
template <typename Enum, typename Lambda>
std::string enum_to_string_impl(Enum e, Lambda lambda) {
  return lambda(e);
}
}  // namespace impl

NATIVEMQ_END_NAMESPACE

#define NATIVEMQ_ENUM_CLASS_TO_STRING_FORMATTER(EnumType, ...)       \
                                                                     \
  inline std::string ToStringEnum##EnumType(EnumType e) {            \
    static const auto toStringFunc = [](EnumType e) -> std::string { \
      switch (e) {                                                   \
        __VA_ARGS__                                                  \
        default:                                                     \
          throw std::invalid_argument("Unsupported enum value");     \
      }                                                              \
    };                                                               \
    return nativemq::impl::enum_to_string_impl(e, toStringFunc);     \
  }