#ifndef _CONFIG_HEADER_CMAKE
#define _CONFIG_HEADER_CMAKE

#define PROJECT_VER "1.0.0"

#if defined(_WIN32) || defined(WIN32)
#define OS_NAME "Windows"
#elif defined(__linux__)
#define OS_NAME "Linux"
#elif defined(__APPLE__)
#define OS_NAME "iOS"
#else
#define OS_NAME "unknown"
#endif
#define COPYRIGHT       "Copyright (C) 2024 Antoni Bertolin"
#define LICENSE_VERSION "MIT License"

#endif  // INCLUDE_GUARD
