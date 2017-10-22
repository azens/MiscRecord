#include "drawbmp.hpp"
void display(Image* img){
	int slice=100;
	for(int i=0;i<slice;i++){
		float x1=640.0/slice*i-320;
		float y1=sin(x1)*200;
		float x2=640.0/slice*(i+1)-320;
		float y2=sin(x2)*200;
		Line(img,x1,y1,x2,y2);
	}
	
}
int main(int argc, char* argv[])
{
	
	RECT rc;
	hwnd = initwindow();
	GetClientRect(hwnd, &rc);
	int w = rc.right - rc.left;
	int h = rc.bottom - rc.top;
	Image img;
	initimage(&img, w, h);
	SetOrigin(&img, w / 2, h / 2);
	SetColor(&img, 0, 255, 255);
	initgraph(&img);
	hdc = GetDC(hwnd);
	while (TRUE) {
		//Sleep(40);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			display(&img);
			SetDIBitsToDevice(hdc, 0, 0, w, h,
			                  0, 0, 0, h, img.Data, &bmi, DIB_RGB_COLORS);
			ClearGraph(&img);
		}
	}
	return 0;
}