#include <iostream> 
#include <string> 
#include <iterator> 
  
#include <boost/property_tree/ptree.hpp>  
#include <boost/property_tree/json_parser.hpp>  
// #include <boost/foreach.hpp> 

using namespace std;  
using namespace boost::property_tree;
using namespace boost::property_tree::json_parser;

auto nth_name = [](auto tree,auto index){auto bounds = tree.equal_range("");advance(bounds.first, index );return bounds.first->first.data();};

auto nth_value = [](auto tree,auto index){auto bounds = tree.equal_range("");advance(bounds.first, index );return bounds.first->second.data();};
  
int main(int argc,char* argv[])  
{  
	if(argc < 2)
	{
		cout << "usage: " << argv[0] << " file.json" << endl;
		return -1;
	}
	//
	ptree tree;  
	try {
        read_json(argv[1], tree); 
    } catch (ptree_error & e) {
		cout << "read error" << endl;
        return -1;
    }

	cout << nth_name(tree,0) << " " <<  nth_value(tree,0) << endl;
	return 0;  
}  