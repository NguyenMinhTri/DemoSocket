#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include<iostream>
#include<string>
using namespace std;
int client()
{
	//Create winsock
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);

	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		cout << "Faild Startup" << endl;
	}

	while (true)
	{
		SOCKADDR_IN addr;
		int addrlen = sizeof(addr);
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		addr.sin_port = htons(1111);
		addr.sin_family = AF_INET;
		char buf[14] = "Hello world \0";
		SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
		if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)))
		{

		}

		string dem = "";
		getline(cin, dem);
		sendto(Connection, buf, sizeof(buf), 0, (sockaddr*)&addr, sizeof(addr));


	}
	return 0;
}