//g++ main.cpp -lwininet
/*
usage example:
get http://www.guotu56.com/uploads/allimg/151209/1-151209164502.jpg
*/
#include <stdio.h>
#include <windows.h>
#include <wininet.h>
#define MAXBLOCKSIZE 1024

//void download(const char*);

int main(int argc, char* argv[])
{
	if(argc > 1) {
		//char str[]="http://www.guotu56.com/uploads/allimg/151209/1-151209164502.jpg";
		int len=strlen(argv[1]);
		int pos,length=len;
		do {
			pos=len+1;
		} while(argv[1][len--]!='/');
		char*filename;
		if(argc>2) {
			filename=argv[2];
		} else {
			filename=(char*)malloc(length-pos+1+5);
			for(int i=0; i<length-pos; i++) {
				filename[i]=argv[1][i+pos];
			}
			filename[length-pos-5]='.';
			filename[length-pos-4]='h';
			filename[length-pos-3]='t';
			filename[length-pos-2]='m';
			filename[length-pos-1]='l';
			filename[length-pos]='\0';
			//filename=argv[1];
		}

		//printf("%d\n",pos);
		puts(filename);
		HINTERNET hSession = InternetOpen("RookIE/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
		if (hSession != NULL) {
			HINTERNET handle2 = InternetOpenUrl(hSession, (const char*)argv[1], NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);
			if (handle2 != NULL) {
				//printf("%s\n",(const char*)argv[1]);
				puts(filename);
				byte Temp[MAXBLOCKSIZE];
				ULONG Number = 1;

				FILE *stream;
				if( (stream = fopen( (const char*)filename, "wb" )) != NULL ) { //这里只是个测试，因此写了个死的文件路径
					while (Number > 0) {
						InternetReadFile(handle2, Temp, MAXBLOCKSIZE - 1, &Number);
						//fprintf(stream, (const char*)Temp);
						fwrite(Temp, sizeof (char), Number , stream);
					}
					fclose( stream );
				}

				InternetCloseHandle(handle2);
				handle2 = NULL;
			}
			InternetCloseHandle(hSession);
			hSession = NULL;
		}
	} else {
		printf("Usage: auto-Update url");
	}
	return 0;
}


/**
 * 执行 文件下载 操作
 * @param Url: The target action url
 *
 */
// void download(const char *Url)
// {

// }