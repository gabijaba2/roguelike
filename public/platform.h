#ifndef _PLATFORM
#define _PLATFORM

#if defined (__unix__) || (defined(__APPLE__) && defined(__MACH__))
	#define PLATFORM_POSIX 1
		
	#include <sys/param.h>
	#if defined (BSD)
		#define PLATFORM_BSD 1
	#elif defined(__linux__)
		#define PLATFORM_LINUX 1
	#elif defined(__APPLE__)
		#define PLATFORM_APPLE 1
	#else
		#error Unsupported system
	#endif
#endif

#if defined (_WIN32)
	#define PLATFORM_WINDOWS 1
#endif


#endif

