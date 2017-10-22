#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define PI 3.1415926536
#define Random rand()%255
#define Length(x) (sizeof(x)/sizeof(x[0])/3)
#define round(x) int(x+0.5)
#define blend(bg,fg,alpha) int(round(alpha * fg + (1-alpha) * bg))
//图元类型
enum{LINE,LINESTRIP,TRIANGLE,FILLTRIANGLE,QUAD,FILLQUAD};

HWND  hwnd;
HDC hdc;
MSG msg;
//HDC cdc;
typedef unsigned char byte;
//BYTE *PImage;
BITMAPINFO bmi;
typedef struct {
	byte r,g,b;
} RGB;
//
typedef float vector3[3];
//三维点数组结构
typedef struct tagPointArray {
	int length;
	float *x, *y, *z;
}PointArray;
//
//inline 
void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
//
inline float fpart(float x)
{
	return x-(int)(x);
}
inline float rfpart(float x)
{
	return 1-fpart(x);
}
//


//
//
typedef struct tagImage {
	int Width,Height,Size;
	byte *Data;
	int ox, oy;
	int red, green, blue;
	float xscale, yscale;
} Image;
//初始化位图矩阵bitmap
void initimage(Image* img,int w, int h)
{
	//
	img->ox=0,img->oy=0;
	img->red = 0, img->green = 255, img->blue = 0;
	img->xscale = 1.0, img->yscale = 1.0;
	//
	img->Width=w,img->Height=h;
	//
	img->Data=(byte*)malloc(w*h*3*sizeof(byte));
	for (int i = 0; i < w*h*3; i++) {
		img->Data[i]=0;
	}
}

void Rand(Image *img)
{
	for(int i=0; i<img->Size; i++) {
		img->Data[i]=rand()%255;
	}
}
//设置背景色
void SetBgColor(Image *img,int r, int g, int b)
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
	memset(img->Data,0,img->Width*img->Height*3);
	ValidateRect( hwnd, NULL );
}
//设置坐标原点
void SetOrigin(Image *img,int x, int y)
{
	img->ox = x, img->oy = y;
}
//设置缩放比例
void SetScale(Image *img,float x, float y)
{
	img->xscale = x, img->yscale = y;
}
//设置像素点为指定的RGB值
void SetPixelLocal(Image *img,int x, int y)
{
	x = img->ox + x*img->xscale;
	y = img->oy + y*img->yscale;
	if ((x<0 || x>img->Width) || (y<0 || y>img->Height))return;
	img->Data[y*img->Width * 3 + x * 3] = img->blue;
	img->Data[y*img->Width * 3 + x * 3 + 1] = img->green;
	img->Data[y*img->Width * 3 + x * 3 + 2] = img->red;
}
RGB GetPixelLocal(Image *img,int x,int y)
{
	x = img->ox + x*img->xscale;
	y = img->oy + y*img->yscale;
	RGB rgb;
	rgb.b=img->Data[y*img->Width * 3 + x * 3];
	rgb.g=img->Data[y*img->Width * 3 + x * 3 + 1];
	rgb.r=img->Data[y*img->Width * 3 + x * 3 + 2];
}
//设置将要使用的RGB颜色值
void SetColor(Image *img,int r, int g, int b)
{
	img->red = r;
	img->green = g;
	img->blue = b;
}

/*二维绘图部分：主要是基本图元的算法*/
//Bresenham line

void BresenhamLine(Image *img,int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1, dy = y2 - y1, inc, pi;
	inc = ((dx * dy) >= 0) ? 1 : -1;
	if (abs(dx) > abs(dy)) {
		if (dx < 0) {
			swap(&x1, &x2),swap(&y1, &y2);
			dx = -dx,dy = -dy;
		}
		dy = (dy > 0) ? dy : -dy;
		pi = 2 * dy - dx;
		while (x1++ <= x2) {
			SetPixelLocal(img,x1 - 1, y1);
			if (pi < 0) pi += 2 * dy;
			else {
				y1 += inc;
				pi += 2 * (dy - dx);
			}
		}
	} else {
		if (dy < 0) {
			swap(&x1, &x2),swap(&y1, &y2);
			dx = -dx,dy = -dy;
		}
		dx = (dx > 0) ? dx : -dx;
		pi = 2 * dx - dy;
		while (y1++ < y2) {
			SetPixelLocal(img,x1, y1 - 1);
			if (pi < 0) pi += 2 * dx;
			else {
				x1 += inc;
				pi += 2 * (dx - dy);
			}
		}
	}
}


//线框三角
void Triangle(Image *img,int x1, int y1, int x2, int y2, int x3, int y3)
{
	BresenhamLine(img,x1, y1, x2, y2);
	BresenhamLine(img,x2, y2, x3, y3);
	BresenhamLine(img,x3, y3, x1, y1);
}

/*填充三角形*/
//绘制填充平顶三角形
void TopTriangle(Image *img,int x0, int y0, int x1, int y1, int x2, int y2)
{
	//先判断下输入的三角形
	if (y0 == y1) {
	} else if (y0 == y2) {
		swap(&x2, &x1),swap(&y2, &y1);
	} else if (y1 == y2) {
		swap(&x0, &x2),swap(&y0, &y2);
	} else {
		return; //error \brief 不是平顶三角形
	}

	if (x1 < x0) {
		swap(&x1, &x0),swap(&y1, &y0);
	} else if (x1 == x0) {
		return;// error \brief不是三角形
	}
	//计算左右误差
	float dxy_left = (x2 - x0)*1.0 / (y2 - y0);
	float dxy_right = (x1 - x2)*1.0 / (y1 - y2);
	//开始进行填充
	float xs = x0, xe = x1;
	for (int y = y0; y <= y2; y++) {
		BresenhamLine(img,xs,y,xe,y);
		xs += dxy_left;
		xe += dxy_right;
	}
} //
//绘制平底三角形
void BottomTriangle(Image *img,int x0, int y0, int x1, int y1, int x2, int y2)
{
	//先判断下输入的三角形
	if (y2 == y1) {
	} else if (y2 == y0) {
		swap(&x0, &x1),swap(&y0, &y1);
	} else if (y0 == y1) {
		swap(&x0, &x2),swap(&y0, &y2);
	} else {
		return; //error \brief 不是平顶三角形
	}
	if (x1 < x2) {
		swap(&x1, &x2);
	} else if (x1 == x2) {
		return;// error \brief不是三角形
	}
	//计算左右误差
	float dxy_left = (x2 - x0)*1.0 / (y2 - y0);
	float dxy_right = (x1 - x0)*1.0 / (y1 - y0);
	//开始进行填充
	float xs = x0, xe = x0;
	for (int y = y0; y <= y2; y++) {
		BresenhamLine(img,xs,y,xe,y);
		xs += dxy_left;
		xe += dxy_right;
	}
}
//绘制任意三角形
int FillTriangle(Image *img,int x0, int y0, int x1, int y1, int x2, int y2)
{
	if ((x0 == x1&&x1 == x2) || (y0 == y1&&y1 == y2)) {
		return 1; //error \brief传进来的点无法构成三角形
	}
	//将三个顶点按照从上到下排序
	if (y0 > y1)swap(&x0, &x1),swap(&y0, &y1);
	if (y0 > y2)swap(&x0, &x2),swap(&y0, &y2);
	if (y1 > y2)swap(&y1, &y2),swap(&x1, &x2);
	//进行绘制
	if (y0 == y1) { //平顶三角形
		TopTriangle(img,x0, y0, x1, y1, x2, y2);
	} else if (y1 == y2) {
		BottomTriangle(img,x0, y0, x1, y1, x2, y2);
	} else {
		float k=1.0*(x2 - x0) / (y2 - y0);
		int new_x = x0 +k*(y1 - y0);
		BottomTriangle(img,x0, y0, new_x, y1, x1, y1);
		TopTriangle(img,new_x, y1, x1, y1, x2, y2);
	}
	return 0;
}

/*三维部分：主要是旋转[暂时只考虑平行投影]*/


//绘制三维点在二维xOy平面的封闭多边形
// void DrawArray(Image *img,PointArray r)
// {
	// for (int i = 0; i < r.length - 1; i++) {
		// BresenhamLine(img,r.x[i], r.y[i], r.x[i + 1], r.y[i + 1]);
	// }
	// BresenhamLine(img,r.x[r.length - 1], r.y[r.length - 1], r.x[0], r.y[0]);
// }
//绘制两组三维点对应连线在二维xOy平面的投影
void Line3d(Image *img,PointArray a, PointArray b)
{
	int n = a.length;
	for (int i = 0; i < n; i++) {
		BresenhamLine(img,a.x[i], a.y[i], b.x[i], b.y[i]);
	}
}
//
void FillTriangle3d(Image *img,PointArray a)
{
	FillTriangle(img,a.x[0],a.y[0],a.x[1],a.y[1],a.x[2],a.y[2]);
}
//
void Triangle3d(Image *img,PointArray a)
{
	Triangle(img,a.x[0],a.y[0],a.x[1],a.y[1],a.x[2],a.y[2]);
}
//
void FillRect3d(Image *img,PointArray a)
{
	FillTriangle(img,a.x[0],a.y[0],a.x[1],a.y[1],a.x[2],a.y[2]);
	FillTriangle(img,a.x[0],a.y[0],a.x[3],a.y[3],a.x[2],a.y[2]);
}
//
//封闭多边形
void Rect3d(Image *img,PointArray a)
{
	for (int i = 0; i < 3; i++) {
		BresenhamLine(img,a.x[i], a.y[i], a.x[i + 1], a.y[i + 1]);
	}
	BresenhamLine(img,a.x[3], a.y[3], a.x[0], a.y[0]);
}






//
//三维点初始化
// PointArray Array3d(int n)
// {
	// PointArray r;
	// r.length = n;
	// r.x = new float[n];
	// r.y = new float[n];
	// r.z = new float[n];
	// for (int i = 0; i < n; i++) {
		// r.x[i] = r.y[i] = r.z[i] = 0.0;
	// }
	// return r;
// }
//三维点通过数组赋值
PointArray eval(PointArray r,float *a, int n)
{
	// PointArray r;
	// r.length = n;
	// r.x = new float[n];
	// r.y = new float[n];
	// r.z = new float[n];
	for (int i = 0; i < n; i++) {
		r.x[i] = a[3*i];
		r.y[i] = a[3*i + 1];
		r.z[i] = a[3*i + 2];
	}
	return r;
}
//输出三维点数组的数据
void print(PointArray r)
{
	for (int i = 0; i < r.length; i++) {
		printf("%f %f %f\n", r.x[i], r.y[i], r.z[i]);
	}
}
//
void fileprint(FILE* fp,PointArray r)
{
	for (int i = 0; i < r.length; i++) {
		fprintf(fp,"%f %f ", r.x[i], r.y[i], r.z[i]);
	}
	fprintf(fp," quad\n");
}
//
//对三维点进行旋转
void Rotate0(PointArray pa, vector3 vec,float t)
{
	//PointArray r = Array3d(pa.length);
	float x,y,z,a,b,c;
	float base=sqrt(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]);
	a=vec[0]/base,b=vec[1]/base,c=vec[2]/base;
	float qsin=sin(t);
	float qcos=cos(t);
	float rcos=1-cos(t);
	for (int i = 0; i < pa.length; i++) {
		x=pa.x[i],y=pa.y[i],z=pa.z[i];
		//
		pa.x[i]=(qcos+rcos*a*a)*x+(rcos*a*b-qsin*c)*y+(rcos*a*c+qsin*b)*z;
		//
		pa.y[i]=(rcos*b*a+qsin*c)*x+(qcos+rcos*b*b)*y+(rcos*b*c-qsin*a)*z;
		//
		pa.z[i]=(rcos*c*a-qsin*b)*x+(rcos*c*b+qsin*a)*y+(qcos+rcos*c*c)*z;
		//
	}
	//return r;
}
void Rotate(PointArray pa, vector3 vec,float t)
{
	//PointArray r = Array3d(pa.length);
	float x,y,z,a,b,c;
	float base=sqrt(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]);
	a=vec[0]/base,b=vec[1]/base,c=vec[2]/base;
	float qsin=sin(t);
	float qcos=cos(t);
	float rcos=1-cos(t);
	for (int i = 0; i < pa.length; i++) {
		x=pa.x[i],y=pa.y[i],z=pa.z[i];
		//
		pa.x[i]=(qcos+rcos*a*a)*x+(rcos*a*b-qsin*c)*y+(rcos*a*c+qsin*b)*z;
		//
		pa.y[i]=(rcos*b*a+qsin*c)*x+(qcos+rcos*b*b)*y+(rcos*b*c-qsin*a)*z;
		//
		pa.z[i]=(rcos*c*a-qsin*b)*x+(rcos*c*b+qsin*a)*y+(qcos+rcos*c*c)*z;
		//
	}
	//return r;
}
//
//BresenhamLine2
void Line(Image* img, int x1, int y1, int x2, int y2)
{
	int dx, dy, p, const1, const2, x, y, inc;

	int steep = (abs(y2 - y1) > abs(x2 - x1)) ? 1 : 0;
	if (steep == 1) {
		swap(&x1, &y1);
		swap(&x2, &y2);
	}
	if (x1 > x2) {
		swap(&x1, &x2);
		swap(&y1, &y2);
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
			SetPixelLocal(img, y, x);
		else
			SetPixelLocal(img, x, y);
		x++;
		if (p < 0)
			p += const1;
		else {
			p += const2;
			y += inc;
		}
	}
}


//三维点通过数组赋值
// void eval(Point3D r[], float a[], int n)
// {
// for (int i = 0; i < n; i++) {
// r[i].x = a[3 * i];
// r[i].y = a[3 * i + 1];
// r[i].z = a[3 * i + 2];
// }

// }
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
void DrawArray(Image*img, float data[], int type, int number)
{
	//quad
	int size = 8;
	for (int i = 0; i < number; i++) {
		Line(img, data[i*size + 0], data[i*size + 1], data[i*size + 2], data[i*size + 3]);
		Line(img, data[i*size + 2], data[i*size + 3], data[i*size + 4], data[i*size + 5]);
		Line(img, data[i*size + 4], data[i*size + 5], data[i*size + 6], data[i*size + 7]);
		Line(img, data[i*size + 6], data[i*size + 7], data[i*size + 0], data[i*size + 1]);
	}

}
void DrawArray3(Image*img,float data[], int type, int number)
{
	//quad
	int size;
	switch(type) {
	case LINE:
		size=3;
		for (int i = 0; i < number; i++) {
			Line(img, data[i*size + 0], data[i*size + 1], data[i*size + 3], data[i*size + 4]);
		}
		break;
	case LINESTRIP:
		size=6;
		for (int i = 0; i < number; i++) {
			Line(img, data[i*size + 0], data[i*size + 1], data[i*size + 3], data[i*size + 4]);
		}
		break;
	case TRIANGLE:
		size=9;
		for (int i = 0; i < number; i++) {
			Line(img, data[i*size + 0], data[i*size + 1], data[i*size + 3], data[i*size + 4]);
			Line(img, data[i*size + 3], data[i*size + 4], data[i*size + 6], data[i*size + 7]);
			Line(img, data[i*size + 6], data[i*size + 7], data[i*size + 0], data[i*size + 1]);
			//Line(img, data[i*size + 9], data[i*size + 10], data[i*size + 0], data[i*size + 1]);
		}
		break;
	case FILLTRIANGLE:
		size=9;
		for (int i = 0; i < number; i++) {
			FillTriangle(img,data[i*size + 0], data[i*size + 1], data[i*size + 3], data[i*size + 4],data[i*size + 6], data[i*size + 7]);
			//Line(img, data[i*size + 9], data[i*size + 10], data[i*size + 0], data[i*size + 1]);
		}
		break;
	case QUAD:
		size=12;
		for (int i = 0; i < number; i++) {
			Line(img, data[i*size + 0], data[i*size + 1], data[i*size + 3], data[i*size + 4]);
			Line(img, data[i*size + 3], data[i*size + 4], data[i*size + 6], data[i*size + 7]);
			Line(img, data[i*size + 6], data[i*size + 7], data[i*size + 9], data[i*size + 10]);
			Line(img, data[i*size + 9], data[i*size + 10], data[i*size + 0], data[i*size + 1]);
		}
		break;
	case FILLQUAD:
		size=12;
		for (int i = 0; i < number; i++) {
			SetColor(img, Random, Random, Random);
			FillTriangle(img,data[i*size + 0], data[i*size + 1], data[i*size + 3], data[i*size + 4],data[i*size + 6], data[i*size + 7]);
			//SetColor(img, Random, Random, Random);
			FillTriangle(img,data[i*size + 0], data[i*size + 1], data[i*size + 9], data[i*size + 10],data[i*size + 6], data[i*size + 7]);
		}
		break;
	}

}
//透视投影
void Perspective(PointArray pa,float ez,float n,float f)
{
	//PointArray rr = Array3d(pa.length);
	float x,y,z;
	for (int i = 0; i < pa.length; i++) {
		x=pa.x[i],y=pa.y[i],z=pa.z[i];
		pa.x[i]=(ez-z)/(n-f)*x;
		pa.y[i]=(ez-z)/(n-f)*y;
		pa.z[i]=z;
	}
	//return rr;
}

//
Image ReadBMP(const char* filename)
{
	FILE *fpBmp;
	BITMAPFILEHEADER bmf;
	BITMAPINFO bmi;
	fpBmp = fopen(filename,"rb");
	fread(&bmf,14,1,fpBmp);
	fread(&bmi.bmiHeader,40,1,fpBmp);
	Image img;
	initimage(&img,bmi.bmiHeader.biWidth,bmi.bmiHeader.biHeight);
	//img.Data = new byte[img.Width*img.Height * 3];
	fread(img.Data,1,bmf.bfSize,fpBmp);
	fclose(fpBmp);
	return img;
}

void WriteBMP(Image img,const char* filename)
{
	FILE *fpBmp;
	int line=(img.Width*3%4==0)?(img.Width*3):(img.Width*3/4+1)*4;
	//printf("%d\n",line);
	BITMAPFILEHEADER bmf= {
		0x4d42,img.Height*line+54,0,0,54
	};
	BITMAPINFO bmi= {
		40,img.Width,img.Height,1,3*8,0,img.Height*line,0,0,100,0
	};
	fpBmp = fopen(filename,"wb");
	fwrite(&bmf,14,1,fpBmp);
	fwrite(&bmi.bmiHeader,40,1,fpBmp);
	fwrite(img.Data,1,bmf.bfSize,fpBmp);
	fclose(fpBmp);
}



void initgraph(Image*img)
{
	int iWidth=img->Width;
	int iHeight=img->Height;
	int size=iWidth*iHeight*3;
	//PImage=new BYTE[size];
	//img->Data=PImage;
	img->Data=(BYTE*)malloc(size*sizeof(BYTE));
	//
	ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = iWidth;
	bmi.bmiHeader.biHeight = iHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;
	bmi.bmiHeader.biCompression = BI_RGB;
	//
	//CreateThread(0,0,(LPTHREAD_START_ROUTINE)ImageShow,(void*)1,0,0);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM w, LPARAM l) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(1);
		break;
	case WM_NCLBUTTONDOWN:
		if ((w >= HTLEFT && w < HTBORDER))
		break;
	default:
		return DefWindowProc(hwnd, msg, w, l);
	}
	return 0;
}
HWND initwindow()
{
	static TCHAR szAppName[] = TEXT (" ") ;

	WNDCLASS     wndclass ;
	int iCmdShow=1;
	HINSTANCE hInstance =GetModuleHandle(NULL);
	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc   = WndProc;
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance     = hInstance ;
	wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = 0 ;
	wndclass.lpszMenuName  = NULL ;
	wndclass.lpszClassName = szAppName ;
	if (!RegisterClass (&wndclass)) {
		MessageBox (NULL, TEXT ("img program requires Windows NT!"), szAppName, MB_ICONERROR) ;
		//return;
	}
	hwnd = CreateWindow (szAppName, TEXT (""),WS_OVERLAPPED|WS_SYSMENU|WS_THICKFRAME,
	                     300,120,640,480,NULL, NULL, hInstance, NULL) ;
	ShowWindow (hwnd, iCmdShow) ;
	UpdateWindow (hwnd) ;
	return hwnd;
}


