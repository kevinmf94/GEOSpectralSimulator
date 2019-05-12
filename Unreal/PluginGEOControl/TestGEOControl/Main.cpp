#include <stdio.h>
#include <string.h>
#include "GEORPCServer.h"

#include "rpc/server.h"

using namespace geocontrol;

struct SendData {
	int data;
	bool finish = false;
	MSGPACK_DEFINE_ARRAY(data, finish);
};

int main()
{
	GEORPCServer* server = GEORPCServer::getInstance();
	server->bind("test", [](int x) { printf("Hello %d\n", x); });
	server->bind("moveToXYZ", [](double x, double y, double z) { printf("moveToXYZ %f %f %f\n", x, y, z); });

	int* arr;
	arr = (int*) malloc(sizeof(int) * 10);
	int i = 0;

	for (int j = 0; j < 10; j++)
	{
		arr[j] = 5;
		printf("%d\n", arr[j]);
	}

	/*server->bind("nextData", [arr, &i]() {
		/*SendData data;
		data.data = arr[i];
		i++;
		data.finish = (i == 10) ? true : false;
		printf("Sending %d %d\n", data.data, data.finish);
		return "{\"array\": [1,2,3,4]}";
	});*/
	server->bind("getImage", [](std::string text) {
		printf("%s\n", text);
	});
	server->run();

	char c;
	do
	{
		c = getchar();
	} while (c != 'c');

	server->stop();

	free(arr);

	return 0;
}