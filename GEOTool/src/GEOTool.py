import sys
from geotool import *

if __name__ == '__main__':
	config = GEOConfig(sys.argv[1])

	wcsClient = WCSClient(config.wcsUrl, config.coordinates, config.heightmapSize)
	data = wcsClient.send_request()
	data = WCSSaverRAW.parse_wcs(data, config.heightmapSize)
	WCSSaverOBJ().save(config.outputWcs, data)

	for wms_request in config.wmsRequests:
		wmsClient = WMSClient(wms_request[URL], config.coordinates, config.heightmapSize, config.textureSize, wms_request[LAYERS])
		data = wmsClient.send_request()
		WMSSaverJPG().save(wms_request[OUTPUT], data)
