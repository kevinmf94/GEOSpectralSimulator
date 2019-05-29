from geotool import *
import numpy as np


class WCSData:

	def __init__(self, ncols, nrows, xllcorner, yllcorner, cellsize, nodatavalue, srs, data):
		self.ncols = ncols
		self.nrows = nrows
		self.xllcorner = xllcorner
		self.yllcorner = yllcorner
		self.cellsize = cellsize
		self.nodatavalue = nodatavalue
		self.srs = srs
		self.data = data

	@staticmethod
	def parse_wcs(wcs_data, size):

		values = np.zeros((size[0], size[1]))
		col = 0
		row = 0

		# -1 Magic number because the last line is empty line
		for line in wcs_data:
			for value in line.split(" "):
				values[row][col] = float(value)

				col += 1
				if col == size[1]:
					row += 1
					col = 0

		return values

	def save(self, filename, format='obj', mesh_step=1):
		if format == "raw":
			WCSSaverRAW().save(filename, self)
		elif format == "obj":
			WCSSaverOBJ().save(filename, self, mesh_step)
		else:
			raise Exception("WCS Format is not implemented")

