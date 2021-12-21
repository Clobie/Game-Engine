/////////////////////////////////////////////////////////////////////////
// D3DClass.h
/////////////////////////////////////////////////////////////////////////
#pragma once

#include <d3d9.h>

class D3DClass
{
public:
	D3DClass(void);
	D3DClass(const D3DClass& other);
	~D3DClass(void);

	bool Initialize(int screenWidth, int screenHeight, bool vsync, HWND hWnd, bool fullscreen, float screenDepth, float screenNear);
	void Shutdown();

	void Clear(D3DCOLOR color);
	void BeginScene();
	void EndScene();
	void Present();

	LPDIRECT3DDEVICE9 GetDevice();
	LPDIRECT3DDEVICE9 device;

public:
	HWND GetHWND();
	int GetWindowHeight() { return m_windowHeight; };
	int GetWindowWidth() { return m_windowWidth; };

private:
	LPDIRECT3D9 direct3d;
	HWND m_hWnd;

	int m_windowWidth;
	int m_windowHeight;
};

