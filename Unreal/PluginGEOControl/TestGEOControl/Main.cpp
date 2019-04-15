#include "GEORPCServer.h"
#include <stdio.h>
#include "rpc/server.h"

using namespace geocontrol;

int main()
{
	GEORPCServer server;
	server.init();
	server.bindGeoControl();
	server.run();

	char c;
	do
	{
		c = getchar();
	} while (c != 'c');

	server.stop();

	return 0;
}