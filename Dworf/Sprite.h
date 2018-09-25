#pragma once

#include "drawable.h"


class Sprite : public IDrawable2D
{
	D3DXVECTOR2 position{ 0.0f, 0.0f }, size{ 0.0f, 0.0f };

public:
	Sprite(D3DXVECTOR2 position, D3DXVECTOR2 size);
	~Sprite();

	// Унаследовано через IDrawable
	virtual void Draw(Microsoft::WRL::ComPtr<IDirect3DDevice9>& device) override;
};

