from geotool.clients.GEOClient import GEOClient
from geotool.constants.Constants import *


class WMSClient(GEOClient):

    def __init__(self, url, coord, size, texture_size, layer):
        GEOClient.__init__(self, url, "WMS", "GetMap", "1.1.0", "JPEG", coord, size, 5)
        self.srs = "EPSG:23031"
        self.layers = layer
        self.styles = ""
        self.exception = "INIMAGE"
        self.bgcolor = "0xFFFFFF"
        self.transparent = True
        self.texture_size = texture_size

    def generate_params(self):
        super().generate_params()
        self.add_param("SRS", self.srs)
        self.add_param("LAYERS", self.layers)
        self.add_param("STYLES", self.styles)
        self.add_param("EXCEPTION", self.exception)
        self.add_param("BGCOLOR", self.bgcolor)
        self.add_param("TRANSPARENT", self.transparent)
        self.add_param("HEIGHT", self.texture_size[HEIGHT])
        self.add_param("WIDTH", self.texture_size[WIDTH])

    def send_request(self):
        return super().send_request().content
