#include <Win32toAndroid.h>
#include <Window.h>
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow) 
{
	
	Window * window = new Window(hInstance,"Game for Android",1280,752);
	return 0;
}
