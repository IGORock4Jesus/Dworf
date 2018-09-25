#pragma once

__interface IDrawable
{
	void Draw(Microsoft::WRL::ComPtr<IDirect3DDevice9>& device);
};



__interface IDrawable2D : public IDrawable
{

};

__interface IDrawable3D : public IDrawable
{

};

struct Vertex2D
{
	D3DXVECTOR4 position;

	static const DWORD size;
	static const DWORD format;
};