#pragma once

namespace window {

	bool initial(HINSTANCE hinstance);
	void release();
	HWND getHandle();
	void messageLoop();
	int getWidth();
	int getHeight();
}
