from mprpc import RPCClient

client = RPCClient('127.0.0.1', 9999)
print(client.call('printHello'))