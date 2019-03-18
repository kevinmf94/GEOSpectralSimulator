import json
import sys
import utm
import struct
import numpy as np
from geotool import *


def readJson(file):
    f = open(file, "r")
    json_data = f.read()
    data = json.loads(json_data)
    return data


def writeRaw(fileName, data, h, w):
    file = open(fileName, "wb")

    heightValues = np.zeros((h, w))
    cCols = 0
    cRows = 0
    for line in data.split("\n")[6:-1]:
        for value in line.split(" "):
            heightValues[cRows][cCols] = float(value)

            cCols += 1
            if cCols == w:
                cRows += 1
                cCols = 0

    heightValues = heightValues.astype(np.int16)
    print(heightValues)

    for row in heightValues:
        for item in row:
            bValue = struct.pack("!H", item)
            file.write(bValue)

    file.close()


def writeInFile(fileName, data):
    file = open(fileName, "w")
    file.write(data)
    file.close()


def latLonToUTM(data):
    xy = utm.from_latlon(data['coordinates']['lat'], data['coordinates']['long'])
    return xy[0], xy[1]


def testDownloadWCS(data):

    if data["type"] == "latlon":
        x,y = latLonToUTM(data)
    else:
        x,y = data['x'], data['y']

    wcsClient = WCSClient(data['wcsClient'])
    res = wcsClient.get_wcs_data(x, y, data['dimensions']['heightmap']['height'], data['dimensions']['heightmap']['width'])
    return res.text

def testDownloadWMS(data):

    if data["type"] == "latlon":
        x,y = latLonToUTM(data)
    else:
        x,y = data['x'], data['y']

    wmsClient = WMSClient(data['wmsClient'])
    wmsClient.add_param("LAYERS", data['wmsLayer'])
    res = wmsClient.get_wms_data(x, y, data['dimensions']['heightmap']['height'], data['dimensions']['heightmap']['width'],
                                 data['dimensions']['texture']['height'], data['dimensions']['texture']['width'])
    return res._content


if __name__ == '__main__':
    jsonFile = sys.argv[1]
    data = readJson(jsonFile)
    h = data['dimensions']['heightmap']['height']
    w = data['dimensions']['heightmap']['width']
    
    wmsData = testDownloadWMS(data)
    file = open(data['outputWms'], "wb")
    file.write(wmsData)
    file.close()

    wcsData = testDownloadWCS(data)
    #writeInFile(data['outputWcs'], wcsData)
    writeRaw(data['outputWcs'], wcsData, h, w)


"""import utm
import cv2
import matplotlib.pyplot as plt

from geotool import WCSClient, WMSClient

res = utm.from_latlon(41.7333, 1.8333)
wcsClient = WCSClient("http://geoserveis.icc.cat/icc_mdt/wcs/service")
wmsClient = WMSClient("http://geoserveis.icc.cat/icc_ortohistorica/wms/service")


#print(res.text)
#resImg = wmsClient.get_wms_data(res[0], res[1], 20, 20)

img = cv2.imread('Heightmap.png')
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
print(gray)
imgplot = plt.imshow(gray)
plt.show()"""