#include <windows.h>
#include <stdio.h>
//
#define Length(x) sizeof(x)/sizeof(x[0])
//
typedef unsigned char byte;
typedef struct {
	byte high,quality,length;
} music;

int n[4]= {125,250,500,1000};
//
int a[7]= {262,294,330,349,392,440,494};
int b[7]= {523,587,659,698,784,880,988};
int c[7]= {1047,1175,1319,1397,1568,1760,1979};
//
// int total[]= {
	// 233,232,252,262,312,312,262,253,252,262,254,233,232,252,262,312,312,262,253,252,
	// 262,254,233,232,252,262,312,312,262,253,252,262,254,233,232,252,262,312,312,262,
	// 253,252,262,254,233,232,252,262,312,312,262,253,252,262,254,233,232,252,262,312,
	// 312,262,253,252,262,254,233,232,252,262,312,312,262,253,252,262,254
// };

// void write()
// {
	// char filename[64]="music.txt";
	// FILE* fp=fopen(filename,"wb");
	// int f,t;
	// for(int i=0; i<Length(total); i++) {
		// fprintf(fp,"%d ",total[i]);
	// }
	// fclose(fp);
// }
//
//
void decode(int total,int* f,int* t)
{
	int i,temp1,temp2,temp3;
	//for(i=0; i<Length(total); i++) {
		temp1=total/100;
		temp2=(total/10)%10;
		temp3=total%10;
		switch(temp1) {
		case 1:
			*f=a[temp2-1];
			break;
		case 2:
			*f=b[temp2-1];
			break;
		case 3:
			*f=c[temp2-1];
			break;
		}
		*t=n[temp3-1];
		//printf("(%d %d) ",f,t);
	//}

}
void read()
{
	char filename[64]="music.txt";
	FILE* fp=fopen(filename,"rb");
	int f,t,num;
	while(!feof(fp)) {
		fscanf(fp,"%d ",&num);
		decode(num,&f,&t);
		printf("(%d %d) ",f,t);
		Beep(f,t);
	}
	fclose(fp);
}

//
int main()
{
	//write();
	read();
	//decode();
}