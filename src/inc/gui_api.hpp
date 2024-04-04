#pragma once

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#define NOMINMAX
	extern "C" {
		#include <windows.h>
	}
	typedef HWND WINDOW_HANDLER;
#else
	typedef void* WINDOW_HANDLER;
#endif

namespace gui {
	WINDOW_HANDLER create_window(const int width, const int height, const char* title);
	void           update_window(const WINDOW_HANDLER window_handler);
	bool           window_running(const WINDOW_HANDLER window_handler);
}
