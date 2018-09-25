#include "stdafx.h"
#include "window.h"
#include "log.h"
#include "renderer.h"
#include "Sprite.h"
#include "renderScene.h"


namespace window {
	HWND handle;
	LPCSTR className = "DWORF WINDOW";
	int width, height;
	Sprite* testSprite;


	void onCreate(HWND hwnd) {
		dlog::writeLine("onCreate");
		renderer::initial(hwnd);
	}
	void onClose(HWND hwnd) {
		dlog::writeLine("onClose");
		renderer::release();
	}
	void onShow(HWND hwnd, bool isShow) {
		if (isShow)
			dlog::writeLine("onShow");
		else
			dlog::writeLine("onHide");
	}
	void onActivate(HWND hwnd, bool isActive) {
		if (isActive) {
			dlog::writeLine("onActivate");
			renderer::start();
		}
		else {
			dlog::writeLine("onDeactivate");
			renderer::stop();
		}
	}
	void onKeyDown(HWND hwnd, WPARAM wparam) {
		switch (wparam)
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;

		case VK_F3:
			if (testSprite == nullptr) {
				renderScene::add(testSprite = new Sprite({ 100, 100 }, { 200, 100 }));
			}
			break;

		case VK_F4:
			if (testSprite != nullptr) {
				renderScene::remove(testSprite);
				delete testSprite;
				testSprite = nullptr;
			}
			break;
		}
	}

	LRESULT CALLBACK processor(HWND h, UINT m, WPARAM w, LPARAM l) {
		switch (m)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_CREATE:
			onCreate(h);
			break;
		case WM_CLOSE:
			onClose(h);
			DestroyWindow(h);
			break;
		case WM_SHOWWINDOW:
			onShow(h, w == TRUE);
			break;
		case WM_ACTIVATEAPP:
			onActivate(h, w == TRUE);
			break;
		case WM_KEYDOWN:
			onKeyDown(h, w);
			break;
		default:
			return DefWindowProc(h, m, w, l);
		}
		return 0;
	}
	bool initial(HINSTANCE hinstance) {
		WNDCLASS wc{ 0 };
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hInstance = hinstance;
		wc.lpfnWndProc = processor;
		wc.lpszClassName = className;
		wc.style = CS_HREDRAW | CS_VREDRAW;
		RegisterClass(&wc);
		width = 800; // GetSystemMetrics(SM_CXSCREEN)
		height = 600; // GetSystemMetrics(SM_CYSCREEN)
		handle = CreateWindow(className, className, WS_POPUPWINDOW, 0, 0, width, height, HWND_DESKTOP, nullptr, hinstance, nullptr);
		if (!handle)return false;
		ShowWindow(handle, SW_NORMAL);
		UpdateWindow(handle);
		return true;
	}
	void release() {

	}
	HWND getHandle() {
		return handle;
	}
	void messageLoop() {
		MSG msg;
		while (GetMessage(&msg, nullptr, 0, 0))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}
	int getWidth() {
		return width;
	}
	int getHeight() {
		return height;
	}
}
