#include <windows.h>

int WINAPI WinMain( HINSTANCE hInstance,      // handle to current instance
					HINSTANCE hPrevInstance,  // handle to previous instance
					LPSTR lpCmdLine,          // pointer to command line
					int nCmdShow              // show state of window
					)
{

	_asm
	{
		add         edx,0Ch	  
	}
	return 0;
}