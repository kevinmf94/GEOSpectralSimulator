import requests


class WMSClient:
    __url = ""
    __params = "?SERVICE=WMS&REQUEST=GetMap&VERSION=1.0.0&SRS=EPSG:23031" \
               "&STYLES=&FORMAT=JPEG&BGCOLOR=0xFFFFFF&TRANSPARENT=TRUE" \
               "&EXCEPTION=INIMAGE"

    def __init__(self, url):
        self.__url = url

    def get_wms_data(self, x, y, height, width, heightTxt, widthTxt, block_size=5):

        x2 = x+block_size*width
        y2 = y+block_size*height

        self.add_param("WIDTH", widthTxt)
        self.add_param("HEIGHT", heightTxt)

        bbox_str = "{},{},{},{}".format(x, y, x2, y2)
        self.add_param("BBOX", bbox_str)

        print("Request to: "+str(self.__url)+str(self.__params))
        data = requests.get(self.__url+self.__params)

        return data

    def add_param(self, key, value):
        self.__params = self.__params + "&" + str(key) + "=" + str(value)
