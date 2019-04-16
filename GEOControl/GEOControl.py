from mprpc import RPCClient
import numpy as np
import time

client = RPCClient('127.0.0.1', 9999, 1000)
print(client.call('test', 1999));

init = np.array([5.0, 5.0, 120.0]);
end = np.array([10.0, 10.0, 150.0]);
print(init)
print(end)
print()
seq = init
for i in range(0, 105, 5):
	seq = init + (end - init) * float(i/100)
	time.sleep(0.1)
	client.call('moveToXYZ', seq[0], seq[1], seq[2])


client.close();
