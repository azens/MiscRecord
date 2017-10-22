//改成DrawArray帧率由50-60fps提示到90-100fps。
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define PI  3.1415926536
#define Length(x) (sizeof(x)/sizeof(x[0])/3)

HWND  hwnd;
HDC hdc;

typedef unsigned char byte;
//
BITMAPINFO bmi;
typedef struct tagRGB {
	byte r, g, b;
} RGB;
//

//三维点数组结构
typedef struct tagPoint3D {
	float x, y, z;
}Point3D;
//
inline void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}
typedef struct tagImage {
	int Width, Height, Size;
	byte *Data;
	int ox, oy;
	int red, green, blue;
	float xscale, yscale;
} Image;
//初始化位图矩阵bitmap
void initimage(Image* img, int w, int h)
{
	//
	img->ox = 0, img->oy = 0;
	img->red = 0, img->green = 255, img->blue = 0;
	img->xscale = 1.0, img->yscale = 1.0;
	//
	img->Width = w, img->Height = h;
	//
	img->Data = new byte[w*h * 3];
	for (int i = 0; i < w*h * 3; i++) {
		img->Data[i] = 0;
	}
}
//设置背景色
void SetBgColor(Image *img, int r, int g, int b)
{
	for (int i = 0; i < img->Height; i++) {
		for (int j = 0; j < img->Width * 3;) {
			img->Data[i*img->Width * 3 + j++] = b;
			img->Data[i*img->Width * 3 + j++] = g;
			img->Data[i*img->Width * 3 + j++] = r;
		}
	}
}
void ClearGraph(Image *img)
{
	memset(img->Data, 0, img->Width*img->Height * 3);
	ValidateRect(hwnd, NULL);
}
//设置坐标原点
void SetOrigin(Image *img, int x, int y)
{
	img->ox = x, img->oy = y;
}
//设置缩放比例
void SetScale(Image *img, float x, float y)
{
	img->xscale = x, img->yscale = y;
}
//设置像素点为指定的RGB值
void SetPixel(Image *img, int x, int y)
{
	x = img->ox + x*img->xscale;
	y = img->oy + y*img->yscale;
	if ((x<0 || x>img->Width) || (y<0 || y>img->Height))return;
	img->Data[y*img->Width * 3 + x * 3] = img->blue;
	img->Data[y*img->Width * 3 + x * 3 + 1] = img->green;
	img->Data[y*img->Width * 3 + x * 3 + 2] = img->red;
}
RGB GetPixel(Image *img, int x, int y)
{
	x = img->ox + x*img->xscale;
	y = img->oy + y*img->yscale;
	RGB rgb;
	rgb.b = img->Data[y*img->Width * 3 + x * 3];
	rgb.g = img->Data[y*img->Width * 3 + x * 3 + 1];
	rgb.r = img->Data[y*img->Width * 3 + x * 3 + 2];
	return rgb;
}
//设置将要使用的RGB颜色值
void SetColor(Image *img, int r, int g, int b)
{
	img->red = r;
	img->green = g;
	img->blue = b;
}

/*二维绘图部分：主要是基本图元的算法*/
//Bresenham line

void BresenhamLine(Image *img, int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1, dy = y2 - y1, inc, pi;
	inc = ((dx * dy) >= 0) ? 1 : -1;
	if (abs(dx) > abs(dy)) {
		if (dx < 0) {
			swap(x1, x2), swap(y1, y2);
			dx = -dx, dy = -dy;
		}
		dy = (dy > 0) ? dy : -dy;
		pi = 2 * dy - dx;
		while (x1++ <= x2) {
			SetPixel(img, x1 - 1, y1);
			if (pi < 0) pi += 2 * dy;
			else {
				y1 += inc;
				pi += 2 * (dy - dx);
			}
		}
	}
	else {
		if (dy < 0) {
			swap(x1, x2), swap(y1, y2);
			dx = -dx, dy = -dy;
		}
		dx = (dx > 0) ? dx : -dx;
		pi = 2 * dx - dy;
		while (y1++ < y2) {
			SetPixel(img, x1, y1 - 1);
			if (pi < 0) pi += 2 * dx;
			else {
				x1 += inc;
				pi += 2 * (dx - dy);
			}
		}
	}
}
//BresenhamLine2
void Line(Image* img, int x1, int y1, int x2, int y2)
{
	int dx, dy, p, const1, const2, x, y, inc;

	int steep = (abs(y2 - y1) > abs(x2 - x1)) ? 1 : 0;
	if (steep == 1) {
		swap(x1, y1);
		swap(x2, y2);
	}
	if (x1 > x2) {
		swap(x1, x2);
		swap(y1, y2);
	}
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	p = 2 * dy - dx;
	const1 = 2 * dy;
	const2 = 2 * (dy - dx);
	x = x1;
	y = y1;

	inc = (y1 < y2) ? 1 : -1;
	while (x <= x2) {
		if (steep == 1)
			SetPixel(img, y, x);
		else
			SetPixel(img, x, y);
		x++;
		if (p < 0)
			p += const1;
		else {
			p += const2;
			y += inc;
		}
	}
}

//封闭多边形
void Rect3d(Image *img, Point3D pts[])
{
	for (int i = 0; i < 3; i++) {
		Line(img, pts[i].x, pts[i].y, pts[i + 1].x, pts[i + 1].y);
	}
	Line(img, pts[3].x, pts[3].y, pts[0].x, pts[0].y);
}
//三维点通过数组赋值
void eval(Point3D r[], float a[], int n)
{
	for (int i = 0; i < n; i++) {
		r[i].x = a[3 * i];
		r[i].y = a[3 * i + 1];
		r[i].z = a[3 * i + 2];
	}
	//return r;
}
void RotateX(float data[], int length, float t)
{
	//PointArray r = Array3d(pa.length);
	float x, y, z;

	for (int i = 0; i < length; i++) {
		x = data[3*i+0], y = data[3 * i + 1], z = data[3 * i + 2];
		//
		data[3 * i + 0] = x;
		//
		data[3 * i + 1] = y*cos(t) - z*sin(t);
		//
		data[3 * i + 2] = y*sin(t) + z*cos(t);
	}
}
//
void RotateY(float data[], int length, float t)
{
	float x, y, z;
	for (int i = 0; i < length; i++) {
		x = data[3 * i + 0], y = data[3 * i + 1], z = data[3 * i + 2];
		//
		//
		data[3 * i + 0] = z*sin(t) + x*cos(t);
		data[3 * i + 1] = y;
		data[3 * i + 2] = z*cos(t) - x*sin(t);
	}
}
//
void RotateZ(float data[], int length, float t)
{
	//PointArray r = Array3d(pa.length);
	float x, y, z;

	for (int i = 0; i < length; i++) {
		x = data[3 * i + 0], y = data[3 * i + 1], z = data[3 * i + 2];
		//
		data[3 * i + 0] = x*cos(t) - y*sin(t);
		//
		data[3 * i + 1] = x*sin(t) + y*cos(t);
		//
		data[3 * i + 2] = z;
		//
	}
	//return r;
}
//void Project(float data3[],float data)
void DrawArray(Image*img, float data[], int type, int number) {
	//quad
	int size = 8;
	for (int i = 0; i < number; i++) {
		Line(img, data[i*size + 0], data[i*size + 1], data[i*size + 2], data[i*size + 3]);
		Line(img, data[i*size + 2], data[i*size + 3], data[i*size + 4], data[i*size + 5]);
		Line(img, data[i*size + 4], data[i*size + 5], data[i*size + 6], data[i*size + 7]);
		Line(img, data[i*size + 6], data[i*size + 7], data[i*size + 0], data[i*size + 1]);
	}

}
void DrawArray3(Image*img,float data[], int type, int number) {
	//quad
	int size = 12;
	for (int i = 0; i < number; i++) {
		Line(img, data[i*size + 0], data[i*size + 1], data[i*size + 3], data[i*size + 4]);
		Line(img, data[i*size + 3], data[i*size + 4], data[i*size + 6], data[i*size + 7]);
		Line(img, data[i*size + 6], data[i*size + 7], data[i*size + 9], data[i*size + 10]);
		Line(img, data[i*size + 9], data[i*size + 10], data[i*size + 0], data[i*size + 1]);
	}
}
float d = 0.1;
float r = 50;
float yrot = 45;
//
inline float fun(float x, float y)
{
	//Matlab Peaks Function
	float z = 3 * (1 - x)*(1 - x)*exp(-x*x - (y + 1)*(y + 1))
		- 10 * (x / 5 - x*x*x - y*y*y*y*y)*exp(-x*x - y*y)
		- 1.0 / 3 * exp(-(x + 1)*(x + 1) - y*y);
	return z * 10;
}
float data[12 * 60 * 60];
float temp[12 * 60 * 60];
void initiate(int w,int h) {
	
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
	DrawArray3(img, temp, 1, 60 * 60);
	//RotateX(temp, 3600 * 4, 15 * 2 * PI / 360);
	//free(ptsb.x);free(ptsb.y);free(ptsb.z);
	yrot += 0.1;
	//Sleep(100);
}

void initgraph(Image*img)
{
	int iWidth = img->Width;
	int iHeight = img->Height;
	int size = iWidth*iHeight * 3;
	img->Data = new BYTE[size];
	//
	ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = iWidth;
	bmi.bmiHeader.biHeight = iHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;
}
HWND initwindow()
{
	static TCHAR szAppName[] = TEXT(" ");

	WNDCLASS     wndclass;
	int iCmdShow = 1;
	HINSTANCE hInstance = GetModuleHandle(NULL);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = DefWindowProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = 0;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	if (!RegisterClass(&wndclass)) {
		MessageBox(NULL, TEXT("img program requires Windows NT!"), szAppName, MB_ICONERROR);
		//return;
	}
	hwnd = CreateWindow(szAppName, TEXT(""), WS_OVERLAPPEDWINDOW,
		300, 120, 640+36+8, 480+16, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	return hwnd;
}
MSG msg;
HDC cdc;
void render(Image img)
{

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		//if (msg.message == WM_QUIT);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	else {
		display(&img);
		//BitBlt(hdc, 0, 0, img.Width, img.Height, cdc, 0, 0, SRCCOPY);
		SetDIBitsToDevice(hdc, 0, 0, img.Width, img.Height,
			0, 0, 0, img.Height, img.Data, &bmi, DIB_RGB_COLORS);
		ClearGraph(&img);
	}
}
float fps(Image img, int n_frame)
{
	clock_t start, finish;
	int i;
	float fps;
	printf("Performing benchmark, please wait");
	start = clock();
	for (i = 0; i < n_frame; i++) {
		render(img);
	}
	printf("done\n");
	finish = clock();
	fps = float(n_frame) / (finish - start)*CLOCKS_PER_SEC;
	return fps;
}
#define FPS 0
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

#if FPS
	while (TRUE) {
		// Sleep(40);//降低CPU占用率
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		else {
			display(&img);
			BitBlt(hdc, 0, 0, w, h, cdc, 0, 0, SRCCOPY);
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
