#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define Random rand()%255
#define Length(x) (sizeof(x)/sizeof(x[0])/3)
#define round(x) int(x+0.5)
#define blend(bg,fg,alpha) int(round(alpha * fg + (1-alpha) * bg))
HWND         hwnd ;
HDC hdc;
const float PI=3.1415926536;
typedef unsigned char byte;
int iWidth,iHeight;
BYTE *PImage;
BITMAPINFO bmi;
typedef struct {
	byte r,g,b;
} RGB;
//
typedef float vector3[3];
//三维点数组结构
struct PointArray {
	int length;
	float *x, *y, *z;
};
//
inline void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}
//
inline float fpart(float x)
{
	return x-int(x);
}
inline float rfpart(float x)
{
	return 1-fpart(x);
}
//
DWORD WINAPI ImageShow(LPVOID)
{
	static TCHAR szAppName[] = TEXT (" ") ;

	MSG          msg ;
	WNDCLASS     wndclass ;
	int iCmdShow=1;
	HINSTANCE hInstance =GetModuleHandle(NULL);
	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc   = DefWindowProc;
	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance     = hInstance ;
	wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
	wndclass.hbrBackground = 0 ;
	wndclass.lpszMenuName  = NULL ;
	wndclass.lpszClassName = szAppName ;
	if (!RegisterClass (&wndclass)) {
		MessageBox (NULL, TEXT ("This program requires Windows NT!"), szAppName, MB_ICONERROR) ;
		//return;
	}


	hwnd = CreateWindow (szAppName, TEXT (""),WS_OVERLAPPEDWINDOW,
	                     300,120,640,480,NULL, NULL, hInstance, NULL) ;
	hdc=GetDC(hwnd);
	/* HDC screen_dc = CreateCompatibleDC(hdc);
	//ReleaseDC(hwnd, hdc);
	int w=640,h=480;
	BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB, 
		w * h * 4, 0, 0, 0, 0 }  };
	HBITMAP screen_hb = CreateDIBSection(screen_dc, &bi, DIB_RGB_COLORS, (void**)&PImage, 0, 0);
	HBITMAP screen_ob = (HBITMAP)SelectObject(screen_dc, screen_hb); */
	ShowWindow (hwnd, iCmdShow) ;
	UpdateWindow (hwnd) ;
	//
	while (TRUE) {
		Sleep(40);//降低CPU占用率
		if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)break ;
			TranslateMessage (&msg) ;
			DispatchMessage (&msg) ;

		} else {
			//BitBlt(hdc, 0, 0, w, h, screen_dc, 0, 0, SRCCOPY);
			SetDIBitsToDevice(hdc, 0, 0, iWidth, iHeight,
			                  0, 0, 0, iHeight, PImage, &bmi, DIB_RGB_COLORS);
		}
	}
	return msg.wParam;
}

//
//
class Image
{
public:
	int Width,Height,Size;
	byte *Data;
	int ox, oy;
	int red, green, blue;
	float xscale, yscale;
	//初始化位图矩阵bitmap
	Image(int w, int h) {
		//
		this->ox=0,this->oy=0;
		this->red = 0, this->green = 255, this->blue = 0;
		this->xscale = 1.0, this->yscale = 1.0;
		//
		this->Width=w,this->Height=h;
		//
		this->Data=new byte[w*h*3];
		for (int i = 0; i < w*h*3; i++) {
			this->Data[i]=0;
		}
	}
	Image& operator=(const Image& image) {
		this->Width=image.Width;
		this->Height=image.Height;
		this->Size=image.Width*image.Height*3;
		for (int i = 0; i <this->Size ; i++) {
			this->Data[i]=image.Data[i];
		}
		return *this;
	}
	void Rand() {
		for(int i=0; i<this->Size; i++) {
			this->Data[i]=rand()%255;
		}
	}
//设置背景色
	void SetBgColor(int r, int g, int b) {
		for (int i = 0; i < this->Height; i++) {
			for (int j = 0; j < this->Width * 3;) {
				this->Data[i*this->Width * 3 + j++] = b;
				this->Data[i*this->Width * 3 + j++] = g;
				this->Data[i*this->Width * 3 + j++] = r;
			}
		}
	}
	void ClearGraph() {
		memset(this->Data,0,this->Width*this->Height*3);
		ValidateRect( hwnd, NULL );
	}
//设置坐标原点
	void SetOrigin(int x, int y) {
		ox = x, oy = y;
	}
//设置缩放比例
	void SetScale(float x, float y) {
		xscale = x, yscale = y;
	}
//设置像素点为指定的RGB值
	void SetPixel(int x, int y) {
		x = ox + x*xscale;
		y = oy + y*yscale;
		if ((x<0 || x>this->Width) || (y<0 || y>this->Height))return;
		this->Data[y*this->Width * 3 + x * 3] = blue;
		this->Data[y*this->Width * 3 + x * 3 + 1] = green;
		this->Data[y*this->Width * 3 + x * 3 + 2] = red;
	}
	RGB GetPixel(int x,int y) {
		x = ox + x*xscale;
		y = oy + y*yscale;
		RGB rgb;
		rgb.b=this->Data[y*this->Width * 3 + x * 3];
		rgb.g=this->Data[y*this->Width * 3 + x * 3 + 1];
		rgb.r=this->Data[y*this->Width * 3 + x * 3 + 2];
	}
//设置将要使用的RGB颜色值
	void SetColor(int r, int g, int b) {
		red = r;
		green = g;
		blue = b;
	}

	/*二维绘图部分：主要是基本图元的算法*/
//Bresenham line

	void BresenhamLine(int x1, int y1, int x2, int y2) {
		int dx = x2 - x1, dy = y2 - y1, inc, pi;
		inc = ((dx * dy) >= 0) ? 1 : -1;
		if (abs(dx) > abs(dy)) {
			if (dx < 0) {
				swap(x1, x2),swap(y1, y2);
				dx = -dx,dy = -dy;
			}
			dy = (dy > 0) ? dy : -dy;
			pi = 2 * dy - dx;
			while (x1++ <= x2) {
				SetPixel(x1 - 1, y1);
				if (pi < 0) pi += 2 * dy;
				else {
					y1 += inc;
					pi += 2 * (dy - dx);
				}
			}
		} else {
			if (dy < 0) {
				swap(x1, x2),swap(y1, y2);
				dx = -dx,dy = -dy;
			}
			dx = (dx > 0) ? dx : -dx;
			pi = 2 * dx - dy;
			while (y1++ < y2) {
				SetPixel(x1, y1 - 1);
				if (pi < 0) pi += 2 * dx;
				else {
					x1 += inc;
					pi += 2 * (dx - dy);
				}
			}
		}
	}


//线框三角
	void Triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
		BresenhamLine(x1, y1, x2, y2);
		BresenhamLine(x2, y2, x3, y3);
		BresenhamLine(x3, y3, x1, y1);
	}

	/*填充三角形*/
//绘制填充平顶三角形
	void TopTriangle(int x0, int y0, int x1, int y1, int x2, int y2) {
		//先判断下输入的三角形
		if (y0 == y1) {
		} else if (y0 == y2) {
			swap(x2, x1),swap(y2, y1);
		} else if (y1 == y2) {
			swap(x0, x2),swap(y0, y2);
		} else {
			return; //error \brief 不是平顶三角形
		}

		if (x1 < x0) {
			swap(x1, x0),swap(y1, y0);
		} else if (x1 == x0) {
			return;// error \brief不是三角形
		}
		//计算左右误差
		float dxy_left = (x2 - x0)*1.0 / (y2 - y0);
		float dxy_right = (x1 - x2)*1.0 / (y1 - y2);
		//开始进行填充
		float xs = x0, xe = x1;
		for (int y = y0; y <= y2; y++) {
			BresenhamLine(xs,y,xe,y);
			xs += dxy_left;
			xe += dxy_right;
		}
	} //
//绘制平底三角形
	void BottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2) {
		//先判断下输入的三角形
		if (y2 == y1) {
		} else if (y2 == y0) {
			swap(x0, x1),swap(y0, y1);
		} else if (y0 == y1) {
			swap(x0, x2),swap(y0, y2);
		} else {
			return; //error \brief 不是平顶三角形
		}
		if (x1 < x2) {
			swap(x1, x2);
		} else if (x1 == x2) {
			return;// error \brief不是三角形
		}
		//计算左右误差
		float dxy_left = (x2 - x0)*1.0 / (y2 - y0);
		float dxy_right = (x1 - x0)*1.0 / (y1 - y0);
		//开始进行填充
		float xs = x0, xe = x0;
		for (int y = y0; y <= y2; y++) {
			BresenhamLine(xs,y,xe,y);
			xs += dxy_left;
			xe += dxy_right;
		}
	}
//绘制任意三角形
	int FillTriangle(int x0, int y0, int x1, int y1, int x2, int y2) {
		if ((x0 == x1&&x1 == x2) || (y0 == y1&&y1 == y2)) {
			return 1; //error \brief传进来的点无法构成三角形
		}
		//将三个顶点按照从上到下排序
		if (y0 > y1)swap(x0, x1),swap(y0, y1);
		if (y0 > y2)swap(x0, x2),swap(y0, y2);
		if (y1 > y2)swap(y1, y2),swap(x1, x2);
		//进行绘制
		if (y0 == y1) { //平顶三角形
			TopTriangle(x0, y0, x1, y1, x2, y2);
		} else if (y1 == y2) {
			BottomTriangle(x0, y0, x1, y1, x2, y2);
		} else {
			float k=1.0*(x2 - x0) / (y2 - y0);
			int new_x = x0 +k*(y1 - y0);
			BottomTriangle(x0, y0, new_x, y1, x1, y1);
			TopTriangle(new_x, y1, x1, y1, x2, y2);
		}
		return 0;
	}

	/*三维部分：主要是旋转[暂时只考虑平行投影]*/


//绘制三维点在二维xOy平面的封闭多边形
	void DrawArray(PointArray r) {
		for (int i = 0; i < r.length - 1; i++) {
			BresenhamLine(r.x[i], r.y[i], r.x[i + 1], r.y[i + 1]);
		}
		BresenhamLine(r.x[r.length - 1], r.y[r.length - 1], r.x[0], r.y[0]);
	}
//绘制两组三维点对应连线在二维xOy平面的投影
	void Line3d(PointArray a, PointArray b) {
		int n = a.length;
		for (int i = 0; i < n; i++) {
			BresenhamLine(a.x[i], a.y[i], b.x[i], b.y[i]);
		}
	}
//
	void FillTriangle3d(PointArray a) {
		FillTriangle(a.x[0],a.y[0],a.x[1],a.y[1],a.x[2],a.y[2]);
	}
//
	void Triangle3d(PointArray a) {
		Triangle(a.x[0],a.y[0],a.x[1],a.y[1],a.x[2],a.y[2]);
	}
//
	void FillRect3d(PointArray a) {
		FillTriangle(a.x[0],a.y[0],a.x[1],a.y[1],a.x[2],a.y[2]);
		FillTriangle(a.x[0],a.y[0],a.x[3],a.y[3],a.x[2],a.y[2]);
	}
//
//封闭多边形
	void Rect3d(PointArray a) {
		for (int i = 0; i < 3; i++) {
			BresenhamLine(a.x[i], a.y[i], a.x[i + 1], a.y[i + 1]);
		}
		BresenhamLine(a.x[3], a.y[3], a.x[0], a.y[0]);
	}
//
	void initgraph() {
		iWidth=this->Width;
		iHeight=this->Height;
		int size=iWidth*iHeight*3;
		PImage=new BYTE[size];
		this->Data=PImage;
		//
		ZeroMemory(&bmi, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = iWidth;
		bmi.bmiHeader.biHeight = iHeight;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 24;
		bmi.bmiHeader.biCompression = BI_RGB;
		//
		CreateThread(0,0,(LPTHREAD_START_ROUTINE)ImageShow,(void*)1,0,0);
	}

};
//抗锯齿线
void putpixel(Image img,int x,int y,RGB fg,float alpha=1)
{
	//printf("%f ",alpha);
	RGB bg,c;
	bg=img.GetPixel(x,y);
	c.r=blend(bg.r,fg.r,alpha);
	c.g=blend(bg.g,fg.g,alpha);
	c.b=blend(bg.b,fg.b,alpha);
	img.SetColor(c.r,c.g,c.b);
	img.SetPixel(x,y);
}
void drawline(Image img,int x1,int y1,int x2,int y2,RGB color)
{
	int dx=x2-x1,dy=y2-y1;
	int flag=abs(dx)<abs(dy);
	if(flag)swap(x1,y1),swap(x2,y2),swap(dx,dy);
	if(x2<x1)swap(x1,x2),swap(y1,y2);
	float grad=1.0*dy/dx;
	float intery = y1 + rfpart(x1) * grad;
	//
	int xstart,xend,yend,xgap,px,py;
	//first
	xend = round(x1);
	yend = y1 + grad * (xend - x1);
	xgap = rfpart(x1 + 0.5);
	px= int(xend), py=int(yend);
	putpixel(img, px, py, color, rfpart(yend) * xgap);
	putpixel(img, px, py+1, color, fpart(yend) * xgap);
	xstart=px+1;
	//second
	xend = round(x2);
	yend = y2 + grad * (xend - x2);
	xgap = rfpart(x2 + 0.5);
	px= int(xend), py=int(yend);
	putpixel(img, px, py, color, rfpart(yend) * xgap);
	putpixel(img, px, py+1, color, fpart(yend) * xgap);
	xend=px;
	//
	int x,y;
	//
	//printf("(%d %d) ",xstart,xend);
	for(x=xstart; x<xend; x++) {
		y=int(intery);
		if(flag) {
			px=y,py=x;
			putpixel(img, px, py, color, rfpart(intery));
			putpixel(img, px+1, py, color, fpart(intery));
		} else {
			px=x,py=y;
			putpixel(img, px, py, color, rfpart(intery));
			putpixel(img, px, py+1, color, fpart(intery));
		}

		intery += grad;
	}
}


//
//三维点初始化
PointArray Array3d(int n)
{
	PointArray r;
	r.length = n;
	r.x = new float[n];
	r.y = new float[n];
	r.z = new float[n];
	for (int i = 0; i < n; i++) {
		r.x[i] = r.y[i] = r.z[i] = 0.0;
	}
	return r;
}
//三维点通过数组赋值
PointArray eval(float *a, int n)
{
	PointArray r;
	r.length = n;
	r.x = new float[n];
	r.y = new float[n];
	r.z = new float[n];
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
void Rotate(PointArray pa, vector3 vec,float t)
{
	//PointArray r = Array3d(pa.length);
	float x,y,z,a,b,c;
	float base=sqrt(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]);
	a=vec[0]/base,b=vec[1]/base,c=vec[2]/base;
	for (int i = 0; i < pa.length; i++) {
		x=pa.x[i],y=pa.y[i],z=pa.z[i];
		//
		pa.x[i]=(cos(t)+(1-cos(t))*a*a)*x+
		        ((1-cos(t))*a*b-sin(t)*c)*y+
		        ((1-cos(t))*a*c+sin(t)*b)*z;
		//
		pa.y[i]=((1-cos(t))*b*a+sin(t)*c)*x+
		        (cos(t)+(1-cos(t))*b*b)*y+
		        ((1-cos(t))*b*c-sin(t)*a)*z;
		//
		pa.z[i]=((1-cos(t))*c*a-sin(t)*b)*x+
		        ((1-cos(t))*c*b+sin(t)*a)*y+
		        (cos(t)+(1-cos(t))*c*c)*z;
		//
	}
	//return r;
}
//
void RotateX(PointArray pa,float t)
{
	//PointArray r = Array3d(pa.length);
	float x,y,z;

	for (int i = 0; i < pa.length; i++) {
		x=pa.x[i],y=pa.y[i],z=pa.z[i];
		//
		pa.x[i]=x;
		//
		pa.y[i]=y*cos(t)-z*sin(t);
		//
		pa.z[i]=y*sin(t)+z*cos(t);
	}
}
//
void RotateY(PointArray pa,float t)
{
	float x,y,z;
	for (int i = 0; i < pa.length; i++) {
		x=pa.x[i],y=pa.y[i],z=pa.z[i];
		//
		pa.x[i]=z*sin(t)+x*cos(t);
		pa.y[i]=y;
		pa.z[i]=z*cos(t)-x*sin(t);
	}
}
//
void RotateZ(PointArray pa,float t)
{
	//PointArray r = Array3d(pa.length);
	float x,y,z;

	for (int i = 0; i < pa.length; i++) {
		x=pa.x[i],y=pa.y[i],z=pa.z[i];
		//
		pa.x[i]=x*cos(t)-y*sin(t);
		//
		pa.y[i]=x*sin(t)+y*cos(t);
		//
		pa.z[i]=z;
		//
	}
	//return r;
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
	Image img=Image(bmi.bmiHeader.biWidth,bmi.bmiHeader.biHeight);
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



