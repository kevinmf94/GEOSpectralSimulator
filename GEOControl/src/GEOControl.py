import sys
import os
from geocontrol import GEOClock
from geocontrol import GEOVehicle
from geocontrol import GEORPCClient
from geocontrol import GEOCamera

from geocontrol import MockGEORPCClient

if __name__ == '__main__':

	#client = MockGEORPCClient('127.0.0.1', 9999)
	client = GEORPCClient('127.0.0.1', 9999)

	if client.connect():

		clock = GEOClock()
		
		if os.path.isfile(sys.argv[1]):
			vehicle = GEOVehicle(client, sys.argv[1])
			clock.register(vehicle)

		if len(sys.argv) > 2:
			if os.path.isfile(sys.argv[2]):
				camera = GEOCamera(client, sys.argv[2])
				clock.register(camera)
	
		clock.start()
