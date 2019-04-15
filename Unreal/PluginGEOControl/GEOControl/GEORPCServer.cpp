#include "GEORPCServer.h"
#include "rpc/server.h"
#include <iostream>

namespace geocontrol
{
	GEORPCServer::GEORPCServer()
	{
		this->server = nullptr;
		geoControl = new GEOControl();
	}

	GEORPCServer::GEORPCServer(uint16_t port) : GEORPCServer()
	{
		this->port = port;
	}

	GEORPCServer::~GEORPCServer()
	{

	}

	void GEORPCServer::init()
	{
		server = new rpc::server(this->port);
	}

	void GEORPCServer::bindGeoControl()
	{
		rpc::server* srv = (rpc::server*) server;
		srv->bind("test", [this](int x) { return geoControl->printHello(x); });
		srv->bind("moveTo", [this](double x, double y) { return geoControl->moveTo(x, y); });
	}

	void GEORPCServer::run()
	{
		printf("Running server...\n");
		rpc::server* srv = (rpc::server*) server;
		srv->async_run();
		printf("Server started\n");
	}

	void GEORPCServer::stop()
	{
		rpc::server* srv = (rpc::server*) server;
		srv->stop();
	}

	void GEORPCServer::setPort(uint16_t port)
	{
		this->port = port;
	}

}
