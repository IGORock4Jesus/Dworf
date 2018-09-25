#include "stdafx.h"
#include "renderer.h"
#include "log.h"
#include "renderScene.h"


using namespace Microsoft::WRL;


namespace renderer
{
	ComPtr<IDirect3D9> direct;
	ComPtr<IDirect3DDevice9> device;
	std::thread thread;
	bool enabled;


	bool initial(HWND hwnd) {
		if (!(direct = Direct3DCreate9(D3D_SDK_VERSION)))
			return false;
		D3DPRESENT_PARAMETERS pp{ 0 };
		pp.Windowed = true;
		RECT cr;
		::GetClientRect(hwnd, &cr);
		pp.BackBufferWidth = cr.right - cr.left;
		pp.BackBufferHeight = cr.bottom - cr.top;
		pp.BackBufferFormat = D3DFMT_X8R8G8B8;
		pp.hDeviceWindow = hwnd;
		pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		if (FAILED(direct->CreateDevice(0, D3DDEVTYPE_HAL, hwnd, D3DCREATE_MULTITHREADED | D3DCREATE_HARDWARE_VERTEXPROCESSING, &pp, &device)))
			return false;

		device->SetRenderState(D3DRS_LIGHTING, FALSE);

		return true;
	}
	void release() {
		device = nullptr;
		direct = nullptr;
	}

	void rendering() {
		while (enabled) {
			device->Clear(0, nullptr, D3DCLEAR_TARGET, 0xff404040, 1.0f, 0);
			device->BeginScene();

			renderScene::render(device);

			device->EndScene();
			device->Present(nullptr, nullptr, nullptr, nullptr);

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
	void start() {
		if (enabled) return;
		enabled = true;
		thread = std::thread(rendering);
		dlog::writeLine("renderer is started;");
	}
	void stop() {
		if (!enabled)return;
		enabled = false;
		if (thread.joinable())
			thread.join();
		dlog::writeLine("renderer is stoped;");
	}
}

