from .GEORPCClient import GEORPCClient


class MockGEORPCClient(GEORPCClient):

	def __init__(self, ip, port):
		GEORPCClient.__init__(self, ip, port)

	def connect(self):
		print("Mock connect to "+self.ip+" port: "+str(self.port))
		return True

	def get_image(self, camera_id, path, channel):
		print("Call to getImage "+str(camera_id)+" "+path+" "+channel)

	def set_location(self, x, y, z):
		print("setLocation " + str(x) + " " + str(y) + " " + str(z))

	def set_rotation(self, x, y, z):
		print("setLookAt " + str(x) + " " + str(y) + " " + str(z))

	def set_location_and_lookat(self, x, y, z, lx, ly, lz):
		print("setLocation " + str(x) + " " + str(y) + " " + str(z))
		print("setLookAt " + str(lx) + " " + str(ly) + " " + str(lz))

	def set_camera_lookat(self, camera_id, x, y, z):
		print("setCameraLookAt " + str(camera_id) + " " + str(x) + " " + str(y)+ " " + str(z))
