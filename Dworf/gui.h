#pragma once

namespace gui
{
	struct Control
	{
		std::string name;
	};

	bool initial();
	void release();

	void add(Control* control);
	void remove(Control* control);
	void remove(std::string name);
	void clear();

	void render(LPDIRECT3DDEVICE9 device);

	void keyDown(BYTE key);
	void keyUp(BYTE key);
}