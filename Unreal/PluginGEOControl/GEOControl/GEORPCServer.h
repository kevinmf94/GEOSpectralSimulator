#pragma once
#include "GEOControl.h"
#include <stdint.h>
#include <string>
#include "rpc/server.h"

namespace geocontrol
{
	class GEORPCServer
	{
	public:
		static GEORPCServer* getInstance();
		~GEORPCServer();

		void run();
		void stop();
		
		template <typename F> void bind(std::string name, F func) {
			server->bind(name, func);
		}
	
	private:
		GEORPCServer();
		
		rpc::server* server;
		uint16_t port;
	};

}


