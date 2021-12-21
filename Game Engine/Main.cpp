/////////////////////////////////////////////////////////////////////////
// main.cpp
/////////////////////////////////////////////////////////////////////////
#include "SystemClass.h"

/////////////////////////////////////////////////////////////////////////
// WinMain
/////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int CmdShow)
{
	SystemClass* System;
	bool result;

	// Create the window
	System = new SystemClass;
	if(!System)
	{
		return 0;
	}

	// Initialize and run the system
	result = System->Initialize();
	if(result)
	{
		System->Run();
	}

	// Shutdown and release the system object
	System->Shutdown();
	delete System;
	System = 0;

	return 0;
}