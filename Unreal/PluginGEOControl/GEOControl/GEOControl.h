#pragma once
#include "rpc/server.h"

namespace geocontrol {

	class GEOControl
	{
	public:
		GEOControl();
		~GEOControl();

		void start();

		rpc::server* server;
	};
}

