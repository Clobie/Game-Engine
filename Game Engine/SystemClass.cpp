/////////////////////////////////////////////////////////////////////////
// SystemClass.cpp
/////////////////////////////////////////////////////////////////////////
#include "SystemClass.h"


SystemClass::SystemClass(void)
{
	m_Input = 0;
	m_Graphics = 0;
	m_Timer = 0;
	m_Game = 0;
}

SystemClass::SystemClass(const SystemClass& other)
{

}


SystemClass::~SystemClass(void)
{

}

bool SystemClass::Initialize()
{
	int screenWidth, screenHeight;
	screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	//screenWidth  = 800;
	//screenHeight = 600;
	bool result;

	// Initialize the windows API
	InitializeWindows(screenWidth, screenHeight);

	// Create the input object.  This object will be used to handle reading the keyboard input from the user.
	m_Input = new InputClass;
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	m_Input->Initialize();


	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	m_Graphics = new GraphicsClass;
	if(!m_Graphics)
	{
		return false;
	}

	// Initialize the graphics object.
	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hWnd);
	if(!result)
	{
		return false;
	}

	// Create the timer object.
	m_Timer = new TimerClass;
	if(!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if(!result)
	{
		return false;
	}

	// Create the game object.
	m_Game = new GameClass;
	if(!m_Game)
	{
		return false;
	}

	// Initialize the game class.
	result = m_Game->Initialize(m_Graphics, m_Input, m_Timer);
	if(!result)
	{
		return false;
	}

	return true;
}

void SystemClass::Shutdown()
{
	// Release the graphics object.
	if(m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	// Release the input object.
	if(m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	// Shutdown the window
	ShutdownWindows();

	return;
}

void SystemClass::Run()
{
	MSG msg;
	bool done = false, result = false;

	ZeroMemory(&msg, sizeof(MSG));

	while(!done)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			result = Frame();
			if(!result)
			{
				done = true;
			}
		}
	}
	return;
}

bool SystemClass::Frame()
{
	bool result;

	// Check if the user pressed escape and wants to exit the application.
	if(m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	// Do the frame processing for the graphics object.
	result = m_Game->Frame();
	if(!result)
	{
		return false;
	}

	return true;
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_KEYDOWN:
		{
			// send key down to input
			m_Input->KeyDown((unsigned int)wParam);
			return 0;
		}
	case WM_KEYUP:
		{
			// send key up to input
			m_Input->KeyUp((unsigned int)wParam);
			return 0;
		}
	default:
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}
}

void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wcex;
	DEVMODE dmScreenSettings;
	int posX, posY;

	// Get an external pointer to this object.
	ApplicationHandle = this;

	// Get the instance of this application.
	m_hInstance = GetModuleHandle(NULL);

	// Give the application name
	m_applicationName = "Meteor Assault";

	// Setup the windows class with default settings.
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wcex.hIconSm = wcex.hIcon;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = m_applicationName;
	wcex.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wcex);

	// Determine the resolution of the clients desktop screen. (THIS IS FOR FULLSCREEN WINDOWED MODE ONLY, CURRENTLY!
	//screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	//screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if(FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;			
		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to max resolution anyways.
		//screenWidth  = 1280;
		//screenHeight = 720;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth)  / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, 
				WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
				posX, posY, screenWidth, screenHeight, NULL, NULL, m_hInstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);

	// Hide the mouse cursor.
	ShowCursor(false);

	return;
}

void SystemClass::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if(FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hWnd);
	m_hWnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hInstance);
	m_hInstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}