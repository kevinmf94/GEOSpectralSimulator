from abc import ABC
import time
import requests
import threading
import sys


class GEOClient(ABC):
	__running = True

	def __init__(self, url, service, request, version, format, coord, size, cellsize, offset=(0, 0)):
		self.url = url
		self.service = service
		self.request = request
		self.version = version
		self.format = format
		self.params = "?"
		self.coord = coord
		self.size = size
		self.cellsize = cellsize
		self.offset = offset

	def generate_params(self):
		self.add_param("SERVICE", self.service)
		self.add_param("REQUEST", self.request)
		self.add_param("VERSION", self.version)
		self.add_param("FORMAT", self.format)
		self.add_param("BBOX", self.generate_bbox())

	def generate_bbox(self):
		x = self.coord[0] + (self.offset[0]*self.cellsize)
		y = self.coord[1] + (self.offset[1]*self.cellsize)
		x2 = x + self.cellsize * self.size[0]
		y2 = y + self.cellsize * self.size[1]

		return "{},{},{},{}".format(x, y, x2, y2)

	@staticmethod
	def progress_bar_worker():
		count = 0
		while GEOClient.__running:
			print(".", end="")
			if count % 100 == 0:
				print("")

			sys.stdout.flush()
			time.sleep(0.1)
			count = count + 1

	@staticmethod
	def start_progress_bar():
		GEOClient.__running = True
		t = threading.Thread(target=GEOClient.progress_bar_worker)
		t.start()

	@staticmethod
	def stop_progress_bar():
		GEOClient.__running = False

	def send_request(self):
		self.generate_params()

		print("Request to: " + str(self.url) + str(self.params))
		print("Downloading", end="")
		sys.stdout.flush()
		GEOClient.start_progress_bar()
		data = requests.get(self.url + self.params)
		GEOClient.stop_progress_bar()
		print("Download completed!")
		sys.stdout.flush()

		return data

	def add_param(self, key, value):
		self.params = self.params + "&" + str(key) + "=" + str(value)
