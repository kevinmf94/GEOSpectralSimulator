import sys
from geotool import *

if __name__ == '__main__':
	config = GEOConfig(sys.argv[1])

	wcsClient = WCSClient(config.wcsUrl, config.coordinates, config.bboxSize)
	data = wcsClient.send_request()
	data = WCSSaverRAW.parse_wcs(data, config.bboxSize)

	if config.formatWcs == "raw":
		WCSSaverRAW().save(config.outputWcs, data)
	elif config.formatWcs == "obj":
		WCSSaverOBJ().save(config.outputWcs, data)
	else:
		raise Exception("WCS Format is not implemented")

	for wms_request in config.wmsRequests:
		wmsClient = WMSClient(wms_request[URL], config.coordinates, config.bboxSize, config.textureSize, wms_request[LAYERS])
		data = wmsClient.send_request()
		WMSSaverJPG().save(wms_request[OUTPUT], data)
