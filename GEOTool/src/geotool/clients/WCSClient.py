from geotool.clients.GEOClient import GEOClient
from geotool.model.WCSData import *


class WCSClient(GEOClient):

    def __init__(self, url, coord, size, offset=(0, 0)):
        GEOClient.__init__(self, url, "WCS", "GetCoverage", "1.0.0", "ArcGrid", coord, size, 5, offset)
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
        data = super().send_request().text
        data = data.split("\n")

        ncols = int(data[0].split(" ")[1])
        nrows = int(data[1].split(" ")[1])
        xllcorner = float(data[2].split(" ")[1])
        yllcorner = float(data[3].split(" ")[1])
        cellsize = float(data[4].split(" ")[1])
        nodatavalue = float(data[5].split(" ")[1])
        values = WCSData.parse_wcs(data[6:-1], (nrows, ncols))

        return WCSData(ncols, nrows, xllcorner, yllcorner, cellsize, nodatavalue,
                     self.crs, values)
