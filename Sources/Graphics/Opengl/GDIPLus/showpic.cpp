#include <windows.h>
#include <gdiplus.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
using namespace Gdiplus;
#pragma comment(lib,"gdiplus")
vector<string> vec;
int num=0;
//根据图片的宽度和高度更新窗口客户区的大小
void set_window_size(HWND hWnd,int width,int height)
{
	RECT rcWindow,rcClient;
	int border_width,border_height;

	GetWindowRect(hWnd,&rcWindow);
	GetClientRect(hWnd,&rcClient);

	border_width = (rcWindow.right-rcWindow.left) - (rcClient.right-rcClient.left);
	border_height = (rcWindow.bottom-rcWindow.top) - (rcClient.bottom-rcClient.top);

	SetWindowPos(hWnd,0,0,0,border_width+width,border_height+height,SWP_NOMOVE|SWP_NOZORDER);
}

void draw_image(HWND hWnd,const char* file,int i,int j,int n)
{
	HDC hdc;
	int width=500,height=500;
	int x=1.0*width*i/n,y=1.0*height*j/n;
	//cout<<file<<endl;
	//
	//char *CStr = "string to convert";

	size_t len = strlen(file) + 1;
	size_t converted = 0;
	wchar_t *WStr;
	WStr=(wchar_t*)malloc(len*sizeof(wchar_t));
	mbstowcs_s(&converted, WStr, len, file, _TRUNCATE);
	//加载图像
	Image image(WStr);
	if(image.GetLastStatus() == -1) {
		MessageBox(hWnd,"图片无效!",NULL,MB_OK);
		return;
	}

	//取得宽度和高度
	//width = image.GetWidth();
	//height = image.GetHeight();

	//更新窗口大小
	//set_window_size(hWnd,width,height);

	hdc = GetDC(hWnd);

	//绘图
	Graphics graphics(hdc);
	graphics.DrawImage(&image,x,y,width/n,height/n);

	ReleaseDC(hWnd,hdc);

	return;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch(uMsg) {

	case WM_PAINT:
		//if(num==vec.size())num-=vec.size();
		draw_image(hWnd,vec[num].c_str(),0,0,1);
		num++;
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int main(int argc,char* argv[])
{
	//
	ifstream ifs("test.txt");
	string temp;
	int tempr,tempt;
	while(!ifs.eof()) {
		getline(ifs,temp);
		if(temp.length()>4)
			vec.push_back(temp);
		//cout<<temp<<endl;
	}
	ifs.close();
	//
	MSG msg;
	WNDCLASS wce= {0};
	HWND hWnd;
	HINSTANCE hInstance;
	wce.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wce.hCursor = LoadCursor(NULL,IDC_ARROW);
	wce.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wce.hInstance = hInstance;
	wce.lpfnWndProc = WndProc;
	wce.lpszClassName = "MyClassName";
	wce.style = CS_HREDRAW|CS_VREDRAW;
	if(!RegisterClass(&wce))
		return 1;

	const char* title = "";
	hWnd = CreateWindow("MyClassName",title,WS_OVERLAPPEDWINDOW,350,120,500+16,500+36,
	                    NULL,NULL,hInstance,NULL);
	if(hWnd == NULL)
		return 1;

	//GdiPlus初始化
	ULONG_PTR gdipludToken;
	GdiplusStartupInput gdiplusInput;
	GdiplusStartup(&gdipludToken,&gdiplusInput,NULL);

	//窗口接收文件拖放
	//DragAcceptFiles(hWnd,TRUE);

	ShowWindow(hWnd,1);
	UpdateWindow(hWnd);
	//
	
	//
	//while(1){
	while(GetMessage(&msg,NULL,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if(num==vec.size())return 0;
		//if(num==vec.size())num-=vec.size();

		//draw_image(hWnd,vec[num].c_str(),0,0,1);
		//cout<<vec[num]<<endl;
		
		//draw_image(hWnd,vec[1].c_str(),1,0,2);
		//getchar();
		//Sleep(40);
	}

	//GdiPlus 取消初始化
	GdiplusShutdown(gdipludToken);

	return 0;
}