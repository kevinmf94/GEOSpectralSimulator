import json
import utm

# Constants GEOConfig
URL = "url"
LAYERS = "layers"
OUTPUT = "output"


class GEOConfig:

	def __init__(self, config_file):
		self.file = self.read_json(config_file)
		self.type = self.file["type"]
		self.coordinates = self.parse_coordinates()
		self.bboxSize = self.file["dimensions"]["bbox"]["height"], self.file["dimensions"]["bbox"][
			"width"]
		self.textureSize = self.file["dimensions"]["texture"]["height"], self.file["dimensions"]["texture"]["width"]
		self.wcsUrl = self.file["wcsUrl"]
		self.outputWcs = self.file["outputWcs"]
		self.wmsRequests = self.file["wmsRequests"]
		self.formatWcs = self.file['formatWcs']

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
