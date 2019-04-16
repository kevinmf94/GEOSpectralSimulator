#include "GEORPCServer.h"
#include "rpc/server.h"
#include "rpc/this_server.h"
#include <iostream>

namespace geocontrol
{
	static GEORPCServer* instance;

	GEORPCServer::GEORPCServer()
	{
		port = 9999;
		server = new rpc::server(port);
	}

	GEORPCServer::~GEORPCServer()
	{
	}

	void GEORPCServer::run()
	{
		printf("Running server...\n");
		server->async_run();
		printf("Server started\n");
	}

	void GEORPCServer::stop()
	{
		server->close_sessions();
		server->stop();
	}

	GEORPCServer* GEORPCServer::getInstance()
	{
		if(instance == nullptr)
		{
			instance = new GEORPCServer();
		}

		return instance;
	}
}
