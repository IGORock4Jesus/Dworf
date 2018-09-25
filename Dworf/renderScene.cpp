#include "stdafx.h"
#include "renderScene.h"
#include "window.h"


namespace renderScene
{
	std::list<IDrawable2D*> items2D;
	std::list<std::shared_ptr<IDrawable3D>> items3D;
	std::mutex mutex2, mutex3;


	void add(IDrawable2D* item) {
		std::lock_guard<std::mutex> locker{ mutex2 };
		items2D.push_back(item);
	}
	void add(std::shared_ptr<IDrawable3D>& item) {
		std::lock_guard<std::mutex> locker{ mutex3 };
		items3D.push_back(item);
	}
	void remove(IDrawable2D* item) {
		std::lock_guard<std::mutex> locker{ mutex2 };
		items2D.remove(item);
	}
	void remove(std::shared_ptr<IDrawable3D>& item) {
		std::lock_guard<std::mutex> locker{ mutex3 };
		items3D.remove(item);
	}
	void clear2D() {
		std::lock_guard<std::mutex> locker{ mutex2 };
		for (auto&& i : items2D)
			delete i;
		items2D.clear();
	}
	void clear3D() {
		std::lock_guard<std::mutex> locker{ mutex3 };
		items3D.clear();
	}
	void clear() {
		{
			std::lock_guard<std::mutex> locker{ mutex2 };
			items2D.clear();
		}
		{
			std::lock_guard<std::mutex> locker{ mutex3 };
			items3D.clear();
		}
	}
	void render(Microsoft::WRL::ComPtr<IDirect3DDevice9>& device) {
		{
			D3DXMATRIX m;
			device->SetTransform(D3DTS_PROJECTION, D3DXMatrixOrthoLH(&m, window::getWidth(), window::getHeight(), 0.1f, 1000.0f));
			device->SetTransform(D3DTS_VIEW, D3DXMatrixLookAtLH(&m, &D3DXVECTOR3(0.0f, 0.0f, 100.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, -1.0f, 0.0f)));

			std::lock_guard<std::mutex> locker{ mutex2 };
			device->SetFVF(Vertex2D::format);
			for (auto&& i : items2D) {
				i->Draw(device);
			}
		}
	}
}
