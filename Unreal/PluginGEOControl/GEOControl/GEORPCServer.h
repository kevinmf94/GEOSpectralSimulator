#pragma once
#include "GEOControl.h"
#include <stdint.h>
#include <string>

namespace geocontrol
{
	class GEORPCServer
	{
	public:
		GEORPCServer();
		GEORPCServer(uint16_t port);
		~GEORPCServer();

		void init();
		void run();
		void stop();
		
		void setPort(uint16_t port);
		void bindGeoControl();

	private:

		GEOControl* geoControl;
		void* server;
		uint16_t port = 9999;
	};

}


