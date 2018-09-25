#include "stdafx.h"
#include "app.h"

#include "window.h"


namespace app {
	HINSTANCE handle;

	bool initial(HINSTANCE hinstance) {
		handle = hinstance;
		if (!window::initial(handle))
			return false;
		return true;
	}
	void release() {
		window::release();
	}
	void run() {
		window::messageLoop();
	}
}