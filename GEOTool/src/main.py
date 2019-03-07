import utm
from geotool import WCSClient
from geotool import WMSClient

res = utm.from_latlon(41.7333, 1.8333)
wcsClient = WCSClient("http://geoserveis.icc.cat/icc_mdt/wcs/service")
wmsClient = WMSClient("http://geoserveis.icc.cat/icc_ortohistorica/wms/service")

res = wcsClient.get_wcs_data(res[0], res[1], 1000, 1000)
#print(res.text)
resImg = wmsClient.get_wms_data(res[0], res[1], 20, 20)




"""print("TEST")
img = mpimg.imread('../cuadro.png')
imgplot = plt.imshow(img)
plt.show()"""