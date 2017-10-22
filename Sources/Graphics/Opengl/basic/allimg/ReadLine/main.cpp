#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdio>
using namespace std;
vector<string> vec;
int num=0;
void initiate()
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
}
int main()
{
	initiate();
	char flag[BUFSIZ];
	char string[BUFSIZ];
	char string2[BUFSIZ];
	int len=log10(vec.size())+1;
	for(int i=0;i<vec.size();i++){
		sprintf(flag,"%%0%dd.jpg",len);
		//puts(flag);
		sprintf(string,flag,i);
		sprintf(string2,"ren %s %s",vec[i].c_str(),string);
		//puts(string2);
		system(string2);
	}
}