#include "GEOControl.h"
#include "rpc/server.h"

int main()
{
	rpc::server srv(9999);
	GEOControl control;
	control.start();

	return 0;
}