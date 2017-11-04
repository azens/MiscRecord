
#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int
main()
{
    cube c=randi<cube>(4,4,3, distr_param(0,255));
    c.save("test.ppm",ppm_binary);
    return 0;
}

