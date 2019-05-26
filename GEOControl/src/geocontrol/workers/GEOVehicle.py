from .GEOWorker import GEOWorker
from numpy import genfromtxt
import numpy as np


class GEOVehicle(GEOWorker):

	def __init__(self, client, csv_file, noise=False):
		GEOWorker.__init__(self, client)
		self.data = genfromtxt(csv_file, delimiter=';', skip_header=1)
		self.noise = noise
		self.index = 0
		self.item = self.data[self.index]

	def notify(self, time):

		if not self.is_finish() and int(self.data[self.index][0]) == time:

			self.item = self.data[self.index]

			if self.noise:
				self.item[1], self.item[2], self.item[3] = self.generate_noise(self.item[1], self.item[2], self.item[3])

			# Call client
			self.client.set_location_and_lookat(self.item[1], self.item[2], self.item[3], self.item[4], self.item[5],
												self.item[6])

			self.index = self.index + 1

	def is_finish(self):
		return self.index >= self.data.shape[0]

	@staticmethod
	def generate_noise(x, y, z):
		return np.random.normal(x, 0.1), np.random.normal(y, 0.1), np.random.normal(z, 0.08)
