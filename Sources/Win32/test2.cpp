#include <stdio.h>
#include <io.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const char *to_search=".\\*";        //欲查找的文件，支持通配符


int main()
{
	string location_base=".\\";
	vector<string> location;

	long handle;                                                //用于查找的句柄
	struct _finddata_t fileinfo;                               //文件信息的结构体
	handle=_findfirst(to_search,&fileinfo);                    //第一次查找
	int i=0;

	if(-1==handle)return -1;
	printf("%s\n",fileinfo.name);                              //打印出找到的文件的文件名
	cout<<location_base+fileinfo.name<<endl;
	location.push_back(location_base+fileinfo.name);
	while(_findnext(handle,&fileinfo)==0)                      //循环查找其他符合的文件，知道找不到其他的为止
	{
		printf("%s\n",fileinfo.name);
		//location[i]=location_base;

		cout<<location_base+fileinfo.name<<endl;
		location.push_back(location_base+fileinfo.name);
	}
	
	cout<<location.size()<<endl;
	_findclose(handle);                                      //关闭句柄

	return 0;
}