from mprpc import RPCClient
import numpy as np
import time

def testClient(client):
	print(client.call('test', 1999));

def testMovement(client):
	init = np.array([250.0, 1372.0, 762.0]);
	end = np.array([2250.0, 1372.0, 762.0]);
	print(init)
	print(end)
	print()
	seq = init
	for i in range(0, 101, 1):
		seq = init + (end - init) * float(i/100)
		time.sleep(0.05)
		client.call('moveToXYZ', seq[0], seq[1], seq[2])

def testPutCamera(client):
	client.call('putCamera', 1);

def stopServer(client):
	client.call('stopServer');


if __name__ == '__main__':
	client = RPCClient('127.0.0.1', 9999, 1000)
	stopServer(client);
	client.close();
