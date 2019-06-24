import numpy as np

header = "Time;x;y;z;LookX;LookY;LookZ"

steps = 1000


time = np.linspace(0, 16000, steps, dtype=np.int32)
x = np.linspace(461183, 468828, steps)
y = np.linspace(4660069, 4666119, steps)
z = np.array([1100]*steps)
xLook = x+10
yLook = y+10
zLook = z

data = np.column_stack((time, x, y, z, xLook, yLook, zLook))

np.savetxt("test.csv", data, delimiter=";", header=header, fmt="%s")


header = "Time;cameraId;LookX;LookY;LookZ;GetImage;Channel"
time = np.linspace(0, 16000, steps, dtype=np.int32)
camera = np.array([1]*steps)
x =	np.array([461183]*steps)
y = np.array([4660069]*steps)
z = np.array([0]*steps)
getImage = np.linspace(0, steps, steps, dtype=np.int32)
getImage = np.array((getImage % 100 == 0), dtype=np.int32) #Cada 100 steps
channel = ['rgb|ir']*steps;

data = np.column_stack((time, camera, x, y, z, getImage, channel))

np.savetxt("testcamera.csv", data, delimiter=";", header=header, fmt="%s")
