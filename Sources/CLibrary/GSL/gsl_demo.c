#include <stdio.h>
#include <gsl/gsl_sf_bessel.h>
#pragma comment(lib,"gsl-19")
int main()
{
	printf("%g",gsl_sf_bessel_J0(5.0));
	return 0;
}