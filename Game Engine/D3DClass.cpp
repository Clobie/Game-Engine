/////////////////////////////////////////////////////////////////////////
// D3DClass.cpp
/////////////////////////////////////////////////////////////////////////
#include "D3DClass.h"


D3DClass::D3DClass(void)
{
	m_windowWidth = 0;
	m_windowHeight = 0;
}

D3DClass::D3DClass(const D3DClass& other)
{

}


D3DClass::~D3DClass(void)
{
	if(device)
	{
		device->Release();
		device = 0;
	}

	if(direct3d)
	{
		direct3d->Release();
		direct3d = 0;
	}
}

void D3DClass::Shutdown()
{
	if(device)
	{
		device->Release();
		device = 0;
	}

	if(direct3d)
	{
		direct3d->Release();
		direct3d = 0;
	}
}

bool D3DClass::Initialize(int screenWidth, int screenHeight, bool vsync, HWND hWnd, bool fullscreen, float screenDepth, float screenNear)
{
	// Create Direct 3D Pointer
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if(!direct3d)
	{
		return false;
	}

	// Present Parameters
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.Windowed = !(fullscreen);
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.BackBufferWidth = screenWidth;
	d3dpp.BackBufferHeight = screenHeight;


	// Create the device
	direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &d3dpp, &device);
	if (!device)
	{
		return false;
	}

	m_hWnd = hWnd;
	m_windowWidth = screenWidth;
	m_windowHeight = screenHeight;
	return true;
}

void D3DClass::Clear(D3DCOLOR color)
{
	//2nd param 'NULL' clears the entire back buffer.
	device->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
}

void D3DClass::BeginScene()
{
	device->BeginScene();
}

void D3DClass::EndScene()
{
	device->EndScene();
}

void D3DClass::Present()
{
	//Present our scene to the window.
	device->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DDEVICE9 D3DClass::GetDevice()
{
	return device;
}

HWND D3DClass::GetHWND()
{
	return m_hWnd;
}