#include "Inferno.h"

IDirect3DDevice9 *Device = 0;
GameState *currentState = 0;
GameState *inferno = new Inferno();


LRESULT CALLBACK D3D::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR cmdLine, int showCmd) {



	currentState = inferno;

	if (!D3D::InitD3D(hinstance, true, D3DDEVTYPE_HAL, &Device))
		return 0;

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (msg.message != WM_QUIT) {
		static float lastTime = (float)timeGetTime();


		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			float currTime = (float)timeGetTime();
			float deltaTime = (currTime - lastTime)*0.001f;
			if (!currentState->isInit)
				currentState->isInit = currentState->Init();
			currentState->GameLoop(deltaTime);

			lastTime = currTime;
		}
	}



	Device->Release();

	return 0;
}
