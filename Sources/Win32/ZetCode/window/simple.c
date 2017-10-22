#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                    PSTR pCmdLine, int CmdShow) {
                    
    MessageBoxW(NULL, L"First Program", L"First", MB_OK);

    return 0;
}