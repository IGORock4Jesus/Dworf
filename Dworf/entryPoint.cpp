#include "stdafx.h"
#include "app.h"


int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, LPSTR, int) {
	if (app::initial(hinstance)) {
		app::run();
	}
	app::release();
	return 0;
}