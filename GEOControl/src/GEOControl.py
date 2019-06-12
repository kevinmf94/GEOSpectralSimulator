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
		vehicle = GEOVehicle(client, sys.argv[1])
		camera = GEOCamera(client, sys.argv[2])
		clock.register(vehicle)
		clock.register(camera)
		clock.start()
