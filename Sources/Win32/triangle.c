#include <windows.h>
//tcc -lmsimg32 -run main.c
#pragma comment(lib,"msimg32")
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//TCHAR szText[] = TEXT("win32 AlphaBlend");

BOOL CenterWindow(HWND hwnd)
{
    HWND hwndParent;
    RECT rect, rectP;
    int width, height;      
    int screenwidth, screenheight;
    int x, y;
 
    //make the window relative to its parent
    hwndParent = GetDesktopWindow();    
     
    GetWindowRect(hwnd, &rect);
    GetWindowRect(hwndParent, &rectP);
     
    width  = rect.right  - rect.left;
    height = rect.bottom - rect.top;    
     
    x = ((rectP.right-rectP.left) -  width) / 2 + rectP.left;
    y = ((rectP.bottom-rectP.top) - height) / 2 + rectP.top;    
 
    screenwidth  = GetSystemMetrics(SM_CXSCREEN);
    screenheight = GetSystemMetrics(SM_CYSCREEN);
 
    //make sure that the dialog box never moves outside of//the screen
    if(x < 0) x = 0;
    if(y < 0) y = 0;
    if(x + width  > screenwidth)  x = screenwidth  - width;
    if(y + height > screenheight) y = screenheight - height;    
 
    MoveWindow(hwnd, x, y, width, height, FALSE);
        return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int iCmdShow)
{

	static TCHAR szAppName[]=TEXT("HelloWin");
	HWND hWnd;
	MSG msg;
	WNDCLASS wndClass;
	int				cxScreen, cyScreen;
	wndClass.style=CS_HREDRAW|CS_VREDRAW;
	wndClass.lpfnWndProc=WndProc;
	wndClass.cbClsExtra=0;
	wndClass.cbWndExtra=0;
	wndClass.hInstance=hInstance;
	wndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName=NULL;
	wndClass.lpszClassName=szAppName;
	if(!RegisterClass(&wndClass)) {
		MessageBox(NULL,TEXT("error"),szAppName,MB_ICONERROR|MB_OK);
		return 0;
	}
	cxScreen = GetSystemMetrics(SM_CXSCREEN);
	cyScreen = GetSystemMetrics(SM_CYSCREEN);
	hWnd=CreateWindow(szAppName,TEXT("The hello program"),WS_OVERLAPPEDWINDOW,
	                  350,120,640,480,NULL,NULL,hInstance,NULL);

    CenterWindow(hWnd);
	//也可以放在此
	ShowWindow(hWnd,iCmdShow);
	UpdateWindow(hWnd);
	while(GetMessage(&msg,NULL,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
#define triangle 1
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	static HDC hdc;
	static HDC hBitmapDC;
	static HBITMAP hBitmap;
	static int w=200;
	static int h=100;
	static BLENDFUNCTION bf = {0};
	PAINTSTRUCT ps;
	switch (message) {
	// case   WM_PAINT :
	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		RECT rc;
		GetClientRect(hWnd,&rc);
		int w=rc.right-rc.left;
		int h=rc.bottom-rc.top;
#if triangle
// Create an array of TRIVERTEX structures that describe
// positional and color values for each vertex.
		TRIVERTEX vertex[3];
		vertex[0].x     = w/2;
		vertex[0].y     = 0;
		vertex[0].Red   = 0xffff;
		vertex[0].Green = 0x0000;
		vertex[0].Blue  = 0x0000;
		vertex[0].Alpha = 0x0000;

		vertex[1].x     = 0;
		vertex[1].y     = h;
		vertex[1].Red   = 0x0000;
		vertex[1].Green = 0xffff;
		vertex[1].Blue  = 0x0000;
		vertex[1].Alpha = 0x0000;

		vertex[2].x     = w;
		vertex[2].y     = h;
		vertex[2].Red   = 0x0000;
		vertex[2].Green = 0x0000;
		vertex[2].Blue  = 0xffff;
		vertex[2].Alpha = 0x0000;

// Create a GRADIENT_TRIANGLE structure that
// references the TRIVERTEX vertices.
		GRADIENT_TRIANGLE gTriangle;
		gTriangle.Vertex1 = 0;
		gTriangle.Vertex2 = 1;
		gTriangle.Vertex3 = 2;

// Draw a shaded triangle.
		GradientFill(hdc, vertex, 3, &gTriangle, 1, GRADIENT_FILL_TRIANGLE);
#else
		//
		// Create an array of TRIVERTEX structures that describe
// positional and color values for each vertex. For a rectangle,
// only two vertices need to be defined: upper-left and lower-right.
		TRIVERTEX vertex[2] ;
		vertex[0].x     = 0;
		vertex[0].y     = 0;
		vertex[0].Red   = 0x0000;
		vertex[0].Green = 0xffff;
		vertex[0].Blue  = 0x0000;
		vertex[0].Alpha = 0x0000;

		vertex[1].x     = w;
		vertex[1].y     = h;
		vertex[1].Red   = 0x0000;
		vertex[1].Green = 0x0000;
		vertex[1].Blue  = 0xffff;
		vertex[1].Alpha = 0x0000;

// Create a GRADIENT_RECT structure that
// references the TRIVERTEX vertices.
		GRADIENT_RECT gRect;
		gRect.UpperLeft  = 0;
		gRect.LowerRight = 1;

// Draw a shaded rectangle.
		GradientFill(hdc, vertex, 2, &gRect, 1, GRADIENT_FILL_RECT_H);
#endif
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY :
		PostQuitMessage(0);
		break ;
	}
	return DefWindowProc (hWnd, message, wParam, lParam) ;
}