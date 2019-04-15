from mprpc import RPCClient

client = RPCClient('127.0.0.1', 9999)
print(client.call('test', 1));
print(client.call('moveTo', 15.5, 15.6));