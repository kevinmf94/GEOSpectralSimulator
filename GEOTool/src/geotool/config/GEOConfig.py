import json
import utm

# Constants GEOTool
URL = "url"
LAYERS = "layers"
HEIGHT = 0
WIDTH = 1
X = 0
Y = 1

class GEOConfig:

	def __init__(self, config_file):
		self.file = self.read_json(config_file)
		self.type = self.file["type"]
		self.coordinates = self.parse_coordinates()
		self.bboxSize = self.file["dimensions"]["bbox"]["height"], self.file["dimensions"]["bbox"][
			"width"]
		self.textureSize = self.file["dimensions"]["texture"]["height"], self.file["dimensions"]["texture"]["width"]
		self.wcsUrl = self.file["wcsUrl"]
		self.folderWcs = self.file["folderWcs"]
		self.outputWcs = self.file["outputWcs"]
		self.wmsRequests = self.file["wmsRequests"]
		self.formatWcs = self.file['formatWcs']
		# self.offset = self.file['offset']['x'], self.file['offset']['y']
		self.cellsize = self.file['cellsize']
		self.chunks = self.file['chunks']['height'], self.file['chunks']['width']

		if 'meshStep' not in self.file:
			self.meshStep = 1
		else:
			self.meshStep = self.file['meshStep']

	@staticmethod
	def read_json(file_name):
		f = open(file_name, "r")
		json_data = f.read()
		return json.loads(json_data)

	def parse_coordinates(self):
		if self.type == "latlong":
			xy = utm.from_latlon(self.file['coordinates']['lat'], self.file['coordinates']['long'])
			return xy[0], xy[1]
		else:
			return self.file['coordinates']['x'], self.file['coordinates']['y']
