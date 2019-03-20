from geotool.clients.GEOClient import GEOClient
from geotool.constants.Constants import *


class WCSClient(GEOClient):

    def __init__(self, url, coord, size):
        GEOClient.__init__(self, url, "WCS", "GetCoverage", "1.0.0", "ArcGrid", coord, size, 5)
        self.crs = "EPSG:23031"
        self.coverage = "icc:met"
        self.exceptions = "XML"

    def generate_params(self):
        super().generate_params()
        self.add_param("HEIGHT", self.size[HEIGHT])
        self.add_param("WIDTH", self.size[WIDTH])
        self.add_param("CRS", self.crs)
        self.add_param("COVERAGE", self.coverage)
        self.add_param("EXCEPTIONS", self.exceptions)

    def send_request(self):
        return super().send_request().text
