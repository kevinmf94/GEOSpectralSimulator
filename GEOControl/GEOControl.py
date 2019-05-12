from mprpc import RPCClient
import numpy as np
import time
import json

def testClient(client):
	print(client.call('test', 1999));

def testMovement(client):
	init = np.array([354.0, 652.0, 337.0]);
	end = np.array([1830.0, 652.0, 337.0]);
	id = 0
	print(init)
	print(end)
	print()
	seq = init
	for i in range(0, 101, 1):
		seq = init + (end - init) * float(i/100)
		time.sleep(0.05)
		client.call('setLocation', seq[0], seq[1], seq[2])
		if i % 10 == 0:
			print(client.call("getImage", 'C:\\Users\\Kevin\\Desktop\\TFGWorkspace\\TestImages\\'+str(id)+'.png'));
		id = id + 1

def testPutCamera(client):
	client.call('putCamera', 1);

def stopServer(client):
	client.call('stopServer');


if __name__ == '__main__':
	client = RPCClient('127.0.0.1', 9999, 1000)

	##print(client.call("getImage", 'prueba'));

	"""finish = False
	while(not finish):
		data = client.call("nextData")
		print(data)
		finish = data[1]"""

	#stopServer(client);
	testMovement(client);

	#print(client.call("getImage", 'C:\\Users\\Kevin\\Desktop\\TFGWorkspace\\TestImages\\1.png'));
	client.close();
