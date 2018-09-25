#pragma once

#include "drawable.h"

namespace renderScene
{
	void add(IDrawable2D* item);
	void remove(IDrawable2D* item);
	void clear2D();

	void render(Microsoft::WRL::ComPtr<IDirect3DDevice9>& device);
}

