#include <gui_api.hpp>
// #include <cwchar>
#include <cstdlib>
#include <set>

#define STR_LEN 256

#ifdef _WIN32
	static std::set<HWND> running_windows;

	static LRESULT CALLBACK window_callback(
		HWND   window_handler,
		UINT   msg,
		WPARAM wParam,
		LPARAM lParam
	)
	{
		LRESULT result = 0;

		switch (msg) {
			case WM_CLOSE:
				running_windows.erase(window_handler);
				break;
			default:
				result = DefWindowProcA(window_handler, msg, wParam, lParam);
		}

		return result;
	}

	WINDOW_HANDLER gui::create_window(const int width, const int height, const char* title) {
		wchar_t  *wtitle     = new wchar_t[STR_LEN];
		size_t    written_ch = std::mbstowcs(wtitle, title, STR_LEN);
		if (written_ch >= STR_LEN)
			return NULL;

		HINSTANCE instance   = GetModuleHandleA(NULL);

		WNDCLASSW window_class     = {};
		window_class.hInstance     = instance;
		window_class.hCursor       = LoadCursor(NULL, IDC_ARROW);
		window_class.lpszClassName = wtitle;
		window_class.lpfnWndProc   = window_callback;

		if (!RegisterClassW(&window_class))
			return NULL;

		HWND window_handle = CreateWindowExW(
			0,
			wtitle,
			wtitle,
			WS_OVERLAPPEDWINDOW,
			100,
			100,
			width,
			height,
			NULL,
			NULL,
			instance,
			NULL
		);

		if (window_handle == NULL)
			return NULL;

		running_windows.insert(window_handle);

		ShowWindow(window_handle, SW_SHOW);

		return window_handle;
	}

	void gui::update_window(const WINDOW_HANDLER window_handle) {
		MSG msg;
		while (PeekMessageA(&msg, window_handle, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}

	bool gui::window_running(const WINDOW_HANDLER window_handle) {
		return running_windows.find(window_handle) != running_windows.end();
	}
#endif