#include "GEOControl.h"
#include <stdio.h>
#include "rpc/server.h"

using namespace geocontrol;

GEOControl::GEOControl()
{

}

GEOControl::~GEOControl()
{

}

void printhello()
{
	printf("Printing Hello\n");
	fflush(stdin);
}

void GEOControl::start()
{
	printf("Starting server...\n");
	fflush(stdin);

	server = new rpc::server(9999);
	server->bind("printHello", &printhello);
	
	printf("Server started!\n");
	fflush(stdin);
	server->run();
}
