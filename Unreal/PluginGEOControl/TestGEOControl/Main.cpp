#include "GEORPCServer.h"
#include <stdio.h>
#include "rpc/server.h"

using namespace geocontrol;

int main()
{
	GEORPCServer* server = GEORPCServer::getInstance();
	server->bind("test", [](int x) { printf("Hello %d\n", x); });
	server->bind("moveToXYZ", [](double x, double y, double z) { printf("moveToXYZ %f %f %f\n", x, y, z); });
	server->run();

	char c;
	do
	{
		c = getchar();
	} while (c != 'c');

	server->stop();

	return 0;
}