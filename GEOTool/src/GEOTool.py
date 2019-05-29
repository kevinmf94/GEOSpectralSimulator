import sys
from geotool import *

if __name__ == '__main__':
	config = GEOConfig(sys.argv[1])

	for h in range(config.chunks[0]):
		for w in range(config.chunks[1]):
			filename = config.outputWcs+"_"+str(h)+"_"+str(w)

			# Calculate offset for the chunk size
			offset = h*config.bboxSize[0], w*config.bboxSize[1]
			print(offset)

			wcsClient = WCSClient(config.wcsUrl, config.coordinates, config.cellsize, config.bboxSize, offset)
			wcsData = wcsClient.send_request()
			wcsData.save(filename, config.formatWcs, config.meshStep)
			WCSSaver.generate_geojson(filename, wcsData)

			for wms_request in config.wmsRequests:
				filename_tex = filename+"_"+wms_request["layers"]

				wmsClient = WMSClient(wms_request["url"], config.coordinates, config.bboxSize,
				                      config.textureSize, wms_request["layers"], offset, config.cellsize)

				data = wmsClient.send_request()
				WMSSaverJPG().save(filename_tex, data)
