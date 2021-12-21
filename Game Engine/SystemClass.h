/////////////////////////////////////////////////////////////////////////
// SystemClass.h
/////////////////////////////////////////////////////////////////////////
#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "GameClass.h"

class SystemClass
{
public:
	SystemClass(void);
	SystemClass(const SystemClass& other);
	~SystemClass(void);

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCSTR m_applicationName;
	HINSTANCE m_hInstance;
	HWND m_hWnd;

private:
	InputClass* m_Input;
	GraphicsClass* m_Graphics;
	TimerClass* m_Timer;
	GameClass* m_Game;
};

static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static SystemClass* ApplicationHandle = 0;