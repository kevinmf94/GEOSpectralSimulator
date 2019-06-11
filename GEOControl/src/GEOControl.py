import sys
from geocontrol import GEOClock
from geocontrol import GEOVehicle
from geocontrol import GEORPCClient
from geocontrol import GEOCamera

from geocontrol import MockGEORPCClient

import os

if __name__ == '__main__':

	#client = MockGEORPCClient('127.0.0.1', 9999)
	client = GEORPCClient('127.0.0.1', 9999)

	if client.connect():

		clock = GEOClock()
		vehicle = GEOVehicle(client, '../mavlink_line.csv')
		#camera = GEOCamera(client, '../mavlink_line_camera2.csv')
		clock.register(vehicle)
		#clock.register(camera)
		clock.start()
		#client.set_location_and_lookat(340293.0, 4676971.5, 3000.0, 340293.0, 4680713.5, 3000.0)
		#client.set_location_and_lookat(340293.0, 4676991.5, 3000.0, 340293.0, 4677991.5, 3000.0)

		#10982.9345703, 3731.9174805, 3000.0
