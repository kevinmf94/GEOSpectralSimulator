from abc import ABC
from .FileSaver import FileSaver
import json


class WCSSaver(FileSaver, ABC):

    @staticmethod
    def generate_geojson(file_name, wcs_data):

        x = wcs_data.xllcorner
        y = wcs_data.yllcorner
        x2 = x + wcs_data.ncols * wcs_data.cellsize
        y2 = y + wcs_data.nrows * wcs_data.cellsize

        data = {
           'type': 'FeatureCollection',
           'name': file_name,
           'crs': {
              'type': 'name',
              'properties': {
                 'name': 'urn:ogc:def:crs:'+wcs_data.srs
              }
           },
           'features': [
              {
                 'type': 'Feature',
                 'properties': {},
                 'geometry': {
                    'type': 'Polygon',
                    'coordinates': [
                       [
                          [x, y],
                          [x, y2],
                          [x2, y2],
                          [x2, y],
                          [x, y]
                       ]
                    ]
                 }
              }
           ]
        }
        json_data = json.dumps(data, ensure_ascii=False)

        with open(file_name+".json", 'w') as f:
            f.write(json_data)


