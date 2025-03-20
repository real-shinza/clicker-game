#include <windows.h>
#include "window/window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	Window window(hInstance, nCmdShow);

	return 0;
}