import sys
import json
from geotool import *

if __name__ == '__main__':
	config = GEOConfig(sys.argv[1])

	mapData = []

	for h in range(config.chunks[0]):
		for w in range(config.chunks[1]):
			name = config.outputWcs+"_"+str(h)+"_"+str(w)
			filename = config.folderWcs+"/"+name
			# Calculate offset for the chunk size
			offset = h * config.bboxSize[0], w * config.bboxSize[1]
			print(offset)

			wcsClient = WCSClient(config.wcsUrl, config.coordinates, config.cellsize, config.bboxSize, offset)
			wcsData = wcsClient.send_request()
			wcsData.save(filename, config.formatWcs, config.meshStep)
			WCSSaver.generate_geojson(filename, wcsData)
		
			textures = []
			for wms_request in config.wmsRequests:
				filename_tex = filename+"_"+wms_request["name"]

				wmsClient = WMSClient(wms_request["url"], config.coordinates, config.bboxSize,
									  config.textureSize, wms_request["layers"], offset, config.cellsize)

				data = wmsClient.send_request()
				WMSSaverJPG().save(filename_tex, data)
				
				textures.append({
					"name": wms_request["name"],
					"file": name+"_"+wms_request["name"]+"."+wms_request['format']
				})

			mapData.append({
				"file": name+"."+config.formatWcs,
				"x": wcsData.xllcorner,
				"y": wcsData.yllcorner,
				"textures": textures
			})

	with open(config.folderWcs+"/"+config.outputWcs+'.json', 'w') as outfile:
		json.dump(mapData, outfile, indent=4)
