#include "drawbmp.h"
Image img;
void display(){
	int slice=100;
	for(int i=0;i<slice;i++){
		float x1=640.0/slice*i-320;
		float y1=sin(x1)*200;
		float x2=640.0/slice*(i+1)-320;
		float y2=sin(x2)*200;
		Line(&img,x1,y1,x2,y2);
	}
	
}
void initialize(){
	RECT rc;
	hwnd = initwindow();
	GetClientRect(hwnd, &rc);
	int w = rc.right - rc.left;
	int h = rc.bottom - rc.top;
	initimage(&img, w, h);
	SetOrigin(&img, w / 2, h / 2);
	SetColor(&img, 0, 255, 255);
	initgraph(&img);
	hdc = GetDC(hwnd);
}
void mainloop(void showfunc()){
	while (TRUE) {
		//Sleep(40);
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			showfunc();
			SetDIBitsToDevice(hdc, 0, 0, img.Width, img.Height,
			                  0, 0, 0, img.Height, img.Data, &bmi, DIB_RGB_COLORS);
			ClearGraph(&img);
		}
	}
}
int main(int argc, char* argv[])
{
	initialize();
	mainloop(display);
	return 0;
}