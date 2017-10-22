#include <stdio.h>
int main(int argc,char* argv[])
{
	//char filename[]=argv[1];
	FILE* fp=fopen(argv[1],"rb");
	fseek(fp,0,SEEK_END);
	int size=ftell(fp);
	fseek(fp,0,SEEK_SET);
	char* s=(char*)malloc(size);
	fread(s,size,1,fp);
	fclose(fp);
	char tmp[400];
	char str[100];
	freopen("test.txt","ab",stdout);
	//puts(s);
	int flag1=-1,flag2=-1,count=0,max=0,num=0;
	for(int i=0; i<size; i++) {
		if(s[i]=='\"')flag1=-flag1;
		else if(flag1==1)flag2=1,tmp[count]=s[i],count++;
		else if(flag1==-1&&flag2==1) {
			tmp[count]='\0',flag2=-flag2;
			if(tmp[count-1]=='g'&&
			        tmp[count-2]=='p'&&
			        tmp[count-3]=='j'&&
			        tmp[count-4]=='.') {
				//printf("%s\n",tmp);
				num++;
				//if(strlen(tmp)>20)
				sprintf(str,"http://www.guotu56.com%s\n",tmp);

				fprintf(stdout,str);
				//system(str);
			}
			count=0;
		}
		if(max<count)max=count;
	}
	//printf("size=%d max=%d num=%d\n",size,max,num);
	return 0;
}