/////////////////////////////////////////////////////////////////////////
// GraphicsClass.h
/////////////////////////////////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include "D3DClass.h"
#include "SpriteClass.h"
#include "FontClass.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	GraphicsClass(void);
	GraphicsClass(const GraphicsClass& other);
	~GraphicsClass(void);

	bool Initialize(int screenWidth, int screenHeight, HWND hWnd);
	void Shutdown();
	bool Frame();
	bool Clear(D3DCOLOR color);
	bool Present();

public:
	LPDIRECT3DDEVICE9 GetDevice();

public:
	void CaptureScreen();
	HWND GetHWND();
	int GetWindowHeight() { return m_D3D->GetWindowHeight(); };
	int GetWindowWidth() { return m_D3D->GetWindowWidth(); };

private:
	bool Render();

private:
	D3DClass* m_D3D;
};