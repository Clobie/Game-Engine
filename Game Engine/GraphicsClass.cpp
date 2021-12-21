/////////////////////////////////////////////////////////////////////////
// GraphicsClass.cpp
/////////////////////////////////////////////////////////////////////////
#include "GraphicsClass.h"

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{

}


GraphicsClass::~GraphicsClass()
{
	
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hWnd)
{
	bool result;

		
	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hWnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hWnd, "Could not initialize Direct3D", "Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsClass::Shutdown()
{
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	return;
}


bool GraphicsClass::Frame()
{
	bool result;


	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}
	return true;
}


bool GraphicsClass::Render()
{
	// THIS WILL GENERATE A BLANK SCREEN!!!  USE GameClass's Frame() method instead!!!
	// Clear the buffers
	m_D3D->Clear(D3DCOLOR_XRGB(255, 255, 255));
	// Begin the scene
	m_D3D->BeginScene();
	// Ends the scene
	m_D3D->EndScene();
	// Presents the screen
	m_D3D->Present();
	return true;
}

bool GraphicsClass::Clear(D3DCOLOR color)
{
	// Clear the buffers
	m_D3D->Clear(color);
	// Begin the scene
	m_D3D->BeginScene();
	return true;
}

bool GraphicsClass::Present()
{
	// Ends the scene
	m_D3D->EndScene();
	// Presents the screen
	m_D3D->Present();
	return true;
}

LPDIRECT3DDEVICE9 GraphicsClass::GetDevice()
{
	return m_D3D->GetDevice();
}

void GraphicsClass::CaptureScreen()
{
    IDirect3DSurface9* pSurface;
	int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

    GetDevice()->CreateOffscreenPlainSurface(nScreenWidth, nScreenHeight, D3DFMT_A8R8G8B8, D3DPOOL_SCRATCH, &pSurface, NULL);
    GetDevice()->GetFrontBufferData(0, pSurface);
   // D3DXSaveSurfaceToFile("Desktop.png",D3DXIFF_PNG,pSurface,NULL,NULL);
    pSurface->Release(); 
}

HWND GraphicsClass::GetHWND()
{
	return m_D3D->GetHWND();
}