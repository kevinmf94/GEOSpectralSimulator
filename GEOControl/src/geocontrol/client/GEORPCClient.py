from mprpc.client import RPCClient


class GEORPCClient:

	def __init__(self, ip, port, timeout=1000):
		self.ip = ip
		self.port = port
		self.timeout = timeout
		self.client = None

	def connect(self):

		connect = True
		try:
			self.client = RPCClient(self.ip, self.port, self.timeout)
		except ConnectionRefusedError:
			connect = False
			print("\033[1;31m Can't connect to " + self.ip + " " + str(self.port)+" \033[0;0m")

		return connect

	def __del__(self):

		if self.client is not None:
			self.client.close()

	def get_image(self, camera_id, path, channel='rgb'):
		self.client.call("getImage", camera_id, path, channel)

	def set_location(self, x, y, z):
		self.client.call('setLocation', x, y, z)

	def set_rotation(self, x, y, z):
		self.client.call('setLookAt', x, y, z)

	def set_location_and_lookat(self, x, y, z, lx, ly, lz):
		self.client.call('setLocationAndLookAt', x, y, z, lx, ly, lz)

	def set_camera_lookat(self, camera_id, x, y, z): 
		self.client.call('setCameraLookAt', camera_id, x, y, z)
