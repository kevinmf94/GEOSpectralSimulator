import requests


class WCSClient:
    __url = ""
    __params = "?SERVICE=WCS&REQUEST=GetCoverage&VERSION=1.0.0&CRS=EPSG:25831&" \
               "COVERAGE=icc:met&FORMAT=ArcGrid&EXCEPTIONS=XML"

    def __init__(self, url):
        self.__url = url

    def get_wcs_data(self, x, y, height, width, block_size=5):

        #self.add_params("&WIDTH=1&HEIGHT=1")
        #self.add_params("&BBOX=370626,4654129.5,370631,4654134.5")

        x2 = x+block_size*width
        y2 = y+block_size*height

        self.add_param("WIDTH", width)
        self.add_param("HEIGHT", height)

        bbox_str = "{},{},{},{}".format(x, y, x2, y2)
        print(bbox_str)
        self.add_param("BBOX", bbox_str)

        print("Request to: " + str(self.__url) + str(self.__params))
        data = requests.get(self.__url+self.__params)

        return data

    def add_param(self, key, value):
        self.__params = self.__params + "&" + str(key) + "=" + str(value)
