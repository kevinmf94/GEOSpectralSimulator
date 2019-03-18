import sys
import struct

file = open("../Heightmap.raw", "rb")

count = 0
bytes = file.read(2)
while bytes:
    dataParsed = struct.unpack('!h', bytes)
    print(str(dataParsed[0])+" ", end='')
    count += 1
    if count % 15 == 0:
        print()
    bytes = file.read(2)

print("EXIT")
