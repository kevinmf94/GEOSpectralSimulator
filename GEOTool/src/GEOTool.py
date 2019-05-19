import sys
from geotool import *

if __name__ == '__main__':
	config = GEOConfig(sys.argv[1])

	wcsClient = WCSClient(config.wcsUrl, config.coordinates, config.cellsize, config.bboxSize, config.offset)
	wcsData = wcsClient.send_request()

	if config.formatWcs == "raw":
		WCSSaverRAW().save(config.outputWcs, wcsData)
	elif config.formatWcs == "obj":
		WCSSaverOBJ().save(config.outputWcs, wcsData, config.meshQuality)
	else:
		raise Exception("WCS Format is not implemented")

	WCSSaver.generate_geojson(config.outputWcs, wcsData)

	print("")

	for wms_request in config.wmsRequests:
		wmsClient = WMSClient(wms_request[URL], config.coordinates, config.bboxSize,
		                      config.textureSize, wms_request[LAYERS], config.offset)

		data = wmsClient.send_request()
		WMSSaverJPG().save(wms_request[OUTPUT], data)
