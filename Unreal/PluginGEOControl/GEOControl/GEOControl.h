#pragma once

namespace geocontrol
{
	class GEOControl
	{
	public:
		GEOControl();
		~GEOControl();
		int printHello(int x);

		void moveTo(double x, double y);
	};
}