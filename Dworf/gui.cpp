#include "stdafx.h"
#include "gui.h"


namespace gui
{


	bool initial();
	void release();

	void render(LPDIRECT3DDEVICE9 device);

	void keyDown(BYTE key);
	void keyUp(BYTE key);
}