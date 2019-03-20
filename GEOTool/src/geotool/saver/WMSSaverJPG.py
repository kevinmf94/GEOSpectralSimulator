from .WMSSaver import WMSSaver


class WMSSaverJPG(WMSSaver):

	def save(self, file_name, data):
		file = open(file_name, "wb")
		file.write(data)
		file.close()
