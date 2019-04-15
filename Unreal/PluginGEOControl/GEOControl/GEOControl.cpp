#include "GEOControl.h"
#include <stdio.h>

namespace geocontrol
{
	GEOControl::GEOControl()
	{
		
	}


	GEOControl::~GEOControl()
	{
	}

	int GEOControl::printHello(int x)
	{
		printf("Hello World!\n");
		return x+1;
	}

	void GEOControl::moveTo(double x, double y)
	{
		printf("MoveTo X:%f, Y:%f\n", x, y);
	}
}

