import numpy as np
from scipy import interpolate

steps = 1000

def Line():
	header = "Time;x;y;z;LookX;LookY;LookZ"

	time = np.linspace(0, 16000, steps, dtype=np.int32)
	x = np.linspace(461183, 468828, steps)
	y = np.linspace(4660069, 4666119, steps)
	z = np.linspace(1100, 3000, steps)
	xLook = x+10
	yLook = y+10
	zLook = z

	data = np.column_stack((time, x, y, z, xLook, yLook, zLook))

	np.savetxt("test3.csv", data, delimiter=";", header=header, fmt="%s")

def LineNoise():
	header = "Time;x;y;z;LookX;LookY;LookZ"

	time = np.linspace(0, 16000, steps, dtype=np.int32)
	x = np.linspace(461183, 468828, steps)
	y = np.linspace(4660069, 4666119, steps)
	z = np.linspace(1100, 3000, steps)
	xLook = x+10
	yLook = y+10
	zLook = z

	x = np.random.normal(x, 0.01)
	y = np.random.normal(y, 0.01)
	z = np.random.normal(z, 0.01)

	data = np.column_stack((time, x, y, z, xLook, yLook, zLook))

	np.savetxt("testnoise.csv", data, delimiter=";", header=header, fmt="%s")

def CameraLineNoise():
	header = "Time;cameraId;LookX;LookY;LookZ;GetImage;Channel"
	time = np.linspace(0, 16000, steps, dtype=np.int32)
	camera = np.array([1]*steps)
	x =	np.array([461183]*steps)
	y = np.array([4660069]*steps)
	z = np.array([0]*steps)
	getImage = np.linspace(0, steps, steps, dtype=np.int32)
	getImage = np.array((getImage % 100 == 0), dtype=np.int32) #Cada 100 steps
	channel = ['rgb|ir']*steps;

	x = np.random.normal(x, 0.05)
	y = np.random.normal(y, 0.05)
	z = np.random.normal(z, 0.05)

	data = np.column_stack((time, camera, x, y, z, getImage, channel))

	np.savetxt("testcameranoise.csv", data, delimiter=";", header=header, fmt="%s")

def CameraLine():
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

def Spline():
	x = [519123, 519331, 518494, 518018]
	y = [4673946, 4675332, 4676327, 4676592]
	xTotal = np.array([])
	yTotal = np.array([])
	for i in range(len(x)-1):
		xTotal = np.concatenate((xTotal, np.linspace(x[i], x[i+1], 50)) )
		yTotal = np.concatenate((yTotal, np.linspace(y[i], y[i+1], 50)) )

	xEje = np.linspace(0, 1, len(yTotal))
	interX = interpolate.splrep(xEje, xTotal)
	interY = interpolate.splrep(xEje, yTotal)

	xyF = np.column_stack((interX[1], interY[1]))

	dxy = interpolate.splev(xEje, interX, der=0)
	print(xyF, dxy)

def PlayaLineNoise():
	header = "Time;x;y;z;LookX;LookY;LookZ"

	time = np.linspace(0, 16000, steps, dtype=np.int32)
	x = np.linspace(521056, 518955, steps)
	y = np.linspace(4674299, 4675656, steps)
	z = np.linspace(434, 700, steps)
	xLook = x-10
	yLook = y+10
	zLook = z

	data = np.column_stack((time, x, y, z, xLook, yLook, zLook))

	np.savetxt("playatestnoise.csv", data, delimiter=";", header=header, fmt="%s")

def PlayaCameraLineNoise():
	header = "Time;cameraId;LookX;LookY;LookZ;GetImage;Channel"
	time = np.linspace(0, 16000, steps, dtype=np.int32)
	camera = np.array([1]*steps)
	x = np.linspace(521056, 518955, steps)
	y = np.linspace(4674299, 4675656, steps)
	z = np.array([0.0]*steps)
	getImage = np.linspace(0, steps, steps, dtype=np.int32)
	getImage = np.array((getImage % 100 == 0), dtype=np.int32) #Cada 100 steps
	channel = ['rgb|ir']*steps;

	x = np.random.normal(x, 1)
	y = np.random.normal(y, 1)

	data = np.column_stack((time, camera, x, y, z, getImage, channel))

	np.savetxt("playatestcameranoise.csv", data, delimiter=";", header=header, fmt="%s")

if __name__ == '__main__':
	PlayaLineNoise()
	PlayaCameraLineNoise()
