// g++ pwd.cpp -lstdc++fs
#include <iostream>
#include <experimental/filesystem>

#ifndef _FSPFX
#define _FSPFX	std::experimental::filesystem::v1::
#endif

int main()
{
	std::cout << "Current path is " << _FSPFX current_path() << '\n';
}