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
	char tmp[100];
	char str[400];
	//puts(s);
	int count=0,index;
	for(int i=0; i<size; i++) {
		if(
		    s[i]=='<'&&
		    s[i+1]=='a'&&
		    s[i+2]==' '&&
		    s[i+3]=='h'&&
		    s[i+4]=='r'&&
		    s[i+5]=='e'&&
		    s[i+6]=='f'&&
		    s[i+7]=='='
		) {
			memset(str,0,400);
			index=9;
			if(s[i+8]=='\'') {
				while(s[i+index]!='\'') {
					str[index-9]=s[i+index];
					index++;
				}
				str[index-9]='\0';
				count++;
				puts(str);
				//printf("%d %s len=%d\n",count,str,index);
			} else if(s[i+8]=='\"') {
				while(s[i+index]!='\"') {
					str[index-9]=s[i+index];
					index++;
				}
				str[index-9]='\0';
				count++;
				puts(str);
				//printf("%d %s len=%d\n",count,str,index);
			}
		}
	}
	return 0;
}