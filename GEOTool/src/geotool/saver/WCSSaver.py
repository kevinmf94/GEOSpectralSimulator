from abc import ABC
from geotool.constants.Constants import *
from .FileSaver import FileSaver
import numpy as np


class WCSSaver(FileSaver, ABC):

    @staticmethod
    def parse_wcs(wcs_data, size, data_start=6):

        values = np.zeros((size[HEIGHT], size[WIDTH]))
        col = 0
        row = 0

        # -1 Magic number because the last line is empty line
        for line in wcs_data.split("\n")[data_start:-1]:
            for value in line.split(" "):
                values[row][col] = float(value)

                col += 1
                if col == size[1]:
                    row += 1
                    col = 0

        return values
