#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
    vector<string> vec;
    ifstream ifs("main.cpp");
    string s;

    while(getline(ifs,s))
    {
        vec.push_back(s);
        cout<<s<<endl;
    }
    ifs.close();
    return 0;
}