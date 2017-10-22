#include "drawbmp.h"

float d = 0.1;
float r=50;
float yrot=45;
float data[12 * 60 * 60];
float temp[12 * 60 * 60];
//
//inline 
float fun(float x,float y)
{
	//Matlab Peaks Function
	float z=3*(1-x)*(1-x)*exp(-x*x - (y+1)*(y+1))
	        - 10*(x/5 - x*x*x - y*y*y*y*y)*exp(-x*x-y*y)
	        - 1.0/3*exp(-(x+1)*(x+1) - y*y);
	return z*10;
}

void initiate(int w,int h)
{

	float x, y, z1, z2, z3, z4;
	int index,sx=60,sy=60;
	float dx =0.1;
	float dy =0.1;
	for (int i = 0; i < sx; i++) {
		for (int j = 0; j < sy; j++) {
			index = sx * j + i;
			x = dx * i - 6/2;
			y = dy * j - 6/2;
			//printf("%f %f\n", x, y);
			data[12 * index + 0] = x*r;
			data[12 * index + 1] = fun(x, y);
			data[12 * index + 2] = y*r;
			data[12 * index + 3] = (x + dx)*r;
			data[12 * index + 4] = fun(x+dx, y);
			data[12 * index + 5] = y*r;
			data[12 * index + 6] = (x + dx)*r;
			data[12 * index + 7] = fun(x+dx, y+dy);
			data[12 * index + 8] = (y + dy)*r;
			data[12 * index + 9] = x*r;
			data[12 * index + 10] = fun(x, y+dy);
			data[12 * index + 11] = (y + dy)*r;
		}
	}
	//memcpy(temp, data, sizeof(float) * 12 * 60 * 60);
	//RotateX(temp, 3600 * 4, 90 * 2 * PI / 360);
}

//
void display(Image* img)
{
	memcpy(temp, data, sizeof(float) * 12 * 60 * 60);
	RotateY(temp, 3600 * 4, yrot);
	RotateX(temp, 3600 * 4, 15 * 2 * PI / 360);
	DrawArray3(img, temp, FILLQUAD, 60 * 60);
	//RotateX(temp, 3600 * 4, 15 * 2 * PI / 360);
	yrot += 0.1;
	//Line(img,0,0,250,250);
	//Sleep(100);
}

void render(Image img)
{

	if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE)) {
		//if (msg.message == WM_QUIT);
		TranslateMessage (&msg) ;
		DispatchMessage (&msg) ;
	} else {
		display(&img);
		//BitBlt(hdc, 0, 0, img.Width, img.Height, cdc, 0, 0, SRCCOPY);
		SetDIBitsToDevice(hdc, 0, 0, img.Width,img.Height,
		                  0, 0, 0, img.Height, img.Data, &bmi, DIB_RGB_COLORS);
		ClearGraph(&img);
	}
}
float fps(Image img,int n_frame )
{
	clock_t start, finish;
	int i;
	float fps;
	printf( "Performing benchmark, please wait" );
	start = clock();
	for( i=0; i<n_frame; i++ ) {
		render(img);
	}
	printf( "done\n" );
	finish = clock();
	fps = (float)(n_frame)/(finish-start)*CLOCKS_PER_SEC;
	return fps;
}

int main(int argc, char* argv[])
{
	Image img;
	RECT rc;
	hwnd = initwindow();
	GetClientRect(hwnd, &rc);
	int w = rc.right - rc.left;
	int h = rc.bottom - rc.top;
	initiate(w, h);
	initimage(&img, w, h);
	SetOrigin(&img, w / 2, h / 2);
	SetColor(&img, 0, 255, 255);
	//int iWidth,iHeight;
	initgraph(&img);

	hdc = GetDC(hwnd);

#if 0
	while (TRUE) {
		//Sleep(40);//降低CPU占用率
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		} else {
			display(&img);
			//BitBlt(hdc, 0, 0, w, h, cdc, 0, 0, SRCCOPY);
			SetDIBitsToDevice(hdc, 0, 0, w, h,
			                  0, 0, 0, h, img.Data, &bmi, DIB_RGB_COLORS);
			ClearGraph(&img);
		}
	}
#else
	printf("%f\n", fps(img, 100));
#endif
	return 0;
}
