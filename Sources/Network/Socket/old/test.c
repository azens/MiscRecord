#include <stdio.h>
#include <string.h>
int main()
{
	char str[]="http://www.guotu56.com/uploads/allimg/151209/1-151209164502.jpg";
	int len=strlen(str);
	int pos,length=len;
	do{
		pos=len+1;
	}while(str[len--]!='/');
	char* filename=(char*)malloc(length-pos+1);
	for(int i=0;i<length-pos;i++){
		filename[i]=str[i+pos];
	}
	printf("%d\n",pos);
	puts(filename);
	return 0;
}
	