#include "drawbmp.hpp"
#define randi rand()%500
void triangle(Image img,float x1,float y1,
              float x2,float y2,float x3,float y3,RGB color)
{
	drawline(img,x1,y1,x2,y2,color);
	drawline(img,x2,y2,x3,y3,color);
	drawline(img,x3,y3,x1,y1,color);
}
#define N 1000
int main()
{
	Image img(500,500);
	img.SetOrigin(250,250);
	RGB color;
	float d=2*PI/N,t1,t2;
	for(int i=0; i<N; i++) {
		color.r=255,color.g=255,color.b=255;
		t1=i*d,t2=(i+1)*d;
		drawline(img,100*sin(t1),100*cos(t1),100*sin(t2),100*cos(t2),color);
	}

	WriteBMP(img,"test.bmp");
}