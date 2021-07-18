#pragma once

#ifdef SGF_PLATFORM_WINDOWS
	#ifdef SGF_BUILD_DLL
		#define SGF_API __declspec(dllexport)
	#else
		#define SGF_API __declspec(dllimport)
	#endif
#endif