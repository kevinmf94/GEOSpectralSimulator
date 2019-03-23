from .WCSSaver import WCSSaver
import numpy as np
import struct


class WCSSaverRAW(WCSSaver):

	def save(self, file_name, data):

		file = open(file_name, "wb")
		values = data.astype(np.int16)
		values = values+128
		for row in values:
			for item in row:
				value = struct.pack("!H", item)
				file.write(value)

		file.close()
