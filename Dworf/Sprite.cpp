#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite(D3DXVECTOR2 position, D3DXVECTOR2 size)
	: position{ position }, size{ size }
{
}


Sprite::~Sprite()
{
}

void Sprite::Draw(Microsoft::WRL::ComPtr<IDirect3DDevice9>& device)
{
	Vertex2D vertices[]{
		{{position.x, position.y, 0.0f, 1.0f}},
		{{position.x + size.x, position.y, 0.0f, 1.0f}},
		{{position.x + size.x, position.y + size.y, 0.0f, 1.0f}},
		{{position.x, position.y + size.y, 0.0f, 1.0f}},
	};

	device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vertices, Vertex2D::size);
}
