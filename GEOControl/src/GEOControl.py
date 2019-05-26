from geocontrol import GEOClock
from geocontrol import GEOVehicle
from geocontrol import GEORPCClient
from geocontrol import GEOCamera

import os

if __name__ == '__main__':

	client = GEORPCClient('127.0.0.1', 9999)
	if client.connect():

		clock = GEOClock()
		vehicle = GEOVehicle(client, '../mavlink_line.csv')
		camera = GEOCamera(client, '../mavlink_line_camera2.csv')
		clock.register(vehicle)
		clock.register(camera)
		clock.start()
