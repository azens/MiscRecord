#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

TCHAR szText[] = TEXT("win32 AlphaBlend");

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int iCmdShow)
{
	static TCHAR szAppName[]=TEXT("HelloWin");
	HWND hWnd;
	MSG msg;
	WNDCLASS wc= {sizeof(WNDCLASS)};
	wc.style=CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc=WndProc;
	// wc.cbClsExtra=0;
	// wc.cbWndExtra=0;
	wc.hInstance=hInstance;
	wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	// wc.lpszMenuName=NULL;
	wc.lpszClassName=szAppName;
	if(!RegisterClass(&wc)) {
		MessageBox(NULL,TEXT("error"),szAppName,MB_ICONERROR|MB_OK);
		return 0;
	}
	hWnd=CreateWindow(szAppName,TEXT("RGB"),WS_OVERLAPPEDWINDOW,
	                  320,120,500,500,NULL,NULL,hInstance,NULL);

	//也可以放在此
	ShowWindow(hWnd,iCmdShow);
	UpdateWindow(hWnd);
	while(GetMessage(&msg,NULL,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
//
// inline
void Circle(HDC dc,int ox,int oy,int r)
{
	Ellipse(dc,ox-r,oy-r,ox+r,oy+r);
}
//
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	//
	HDC hdc,hMemDC;
	HBITMAP hBitmap;
	HBRUSH hbrush;
	RECT rc= {0,0,500,500};
	PAINTSTRUCT ps;
	int ox=250,oy=210,r=100;
	//
	switch (message) {
	case   WM_PAINT :
		hdc=BeginPaint(hWnd,&ps);
		//MemDC
		hMemDC = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc,500,500);
		SelectObject(hMemDC,hBitmap);
		//ClearScreen with  Black
		hbrush = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hMemDC,hbrush);
		FillRect(hdc,&rc,hbrush);
		//RED
		hbrush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hMemDC,hbrush);
		//Ellipse(hMemDC,0+200,0+200+30,100+200,100+200+30);
		Circle(hMemDC,ox,oy+0.8*r,r);
		BitBlt(hdc,0,0,500,500,hMemDC,0,0,SRCPAINT);
		//GREEN
		hbrush = CreateSolidBrush(RGB(0, 255, 0));
		SelectObject(hMemDC,hbrush);
		//Ellipse(hMemDC,0+200-26,0+200-15,100+200-26,100+200-15);
		Circle(hMemDC,ox-0.866*0.8*r,oy-0.5*0.8*r,r);
		BitBlt(hdc,0,0,500,500,hMemDC,0,0,SRCPAINT);
		//BLUE
		hbrush = CreateSolidBrush(RGB(0, 0, 255));
		SelectObject(hMemDC,hbrush);
		//Ellipse(hMemDC,0+200+26,0+200-15,100+200+26,100+200-15);
		Circle(hMemDC,ox+0.866*0.8*r,oy-0.5*0.8*r,r);
		BitBlt(hdc,0,0,500,500,hMemDC,0,0,SRCPAINT);
		//
		DeleteObject(hBitmap);
		DeleteDC( hMemDC );
		EndPaint (hWnd, &ps) ;

		break;
	case WM_DESTROY :
		PostQuitMessage(0);
		break ;
	}
	return DefWindowProc (hWnd, message, wParam, lParam) ;
}
