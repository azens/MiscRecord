#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
void parse(string& url)
{
    string head="http://";
    string base="www.guotu56.com";
    //string url="http://www.google.com/upload/img";
    string full;
    //1.Ïà¶ÔÂ·¾¶
    if(url.length()==0||url[0]=='#')return;
    else if(url[0]=='/')full=head+base+url;
    else if(url[0]=='h')full=url;
    else full=head+url;
    cout<<full<<endl;
    string cmd="get "+full;
    cout<<cmd<<endl;
    system(cmd.c_str());
}
int main()
{
    vector<string> vec;
    ifstream ifs("href.txt");
    string s;

    while(getline(ifs,s))
    {
        vec.push_back(s);
        cout<<s<<endl;
    }
    ifs.close();
    return 0;
}