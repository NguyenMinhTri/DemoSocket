#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
using namespace std;
int SetupIPWS(SOCKET& ListenSock, sockaddr_in& MyListenIP) {

	MyListenIP.sin_family = AF_INET;
	MyListenIP.sin_port = htons(1111);       // PORT 80
	MyListenIP.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP của mình

	int nResult = bind(ListenSock, (sockaddr*)&MyListenIP, sizeof(MyListenIP));  // Gán IP PORT vào SOCKET
	if (nResult == -1) {
		cout << "Loi khi thiet lap IP va PORT\n";
		WSAGetLastError();
		closesocket(ListenSock);
		return 1;
	}

	return 0;
}

void LoopListen(SOCKET& ListenSock, sockaddr_in& MyListenIP) {
	SOCKET NewConnection;
	sockaddr_in ConnectClient;
	int nSizeAddr;

	int nResult = listen(ListenSock, 10);           // Lắng nghe kết nối
	if (nResult == -1) {
		cout << "Khong the lang nghe ket noi\n";
		WSAGetLastError();
		return;
	}

	cout << "Dang lang nghe ket noi... tai IP: " << inet_ntoa(MyListenIP.sin_addr)
		<< " PORT: " << MyListenIP.sin_port << "\nCTRL + C de STOP SERVER\n\n";


	char lpBuffRevc[1024] = { 0 }; // Nội dung nhận từ  CLIENT (REQUEST)

								   // Nội dung gửi trả lại  CLIENT
	char headers[] = "HTTP/1.0 200 OK\r\n"
		"Server: eXecutive Winsock Server\r\n"
		"Date: Sat, 3 November 2007\r\n"
		"Content-Type: text/html\r\n"
		"Accept-Ranges: bytes\r\n"
		"Content-Length: 187\r\n"
		"\r\n";           // Kết thức Header \n

	char html[] = "<html>"
		"<head><title>DEMO WEBSERVER - WINSOCK C++ - CopyRight eXecutive</title></head> \r\n"
		"<body>\r\n"
		"<h1>Hello eXecutve!</h1>\r\n"
		"<br>\r\n"
		"CopyRight 2007 by eXecutive<br> \r\n"
		"stairwaytoheaven187@yahoo.com\r\n"
		"</body>\r\n"
		"</html>\r\n\n"; // Kết thúc trang web bằng \n\n

	while (1) {
		nSizeAddr = sizeof(sockaddr);        // Quan trọng! Xác định kích thước sockaddr

		NewConnection = accept(ListenSock, (sockaddr*)&ConnectClient, &nSizeAddr);    // Chấp nhận 1 kết nối

		if (NewConnection == -1) {
			cout << "Loi ket noi tu Client\n";
			continue;
		}

		cout << "Nhan ket noi tu: " << inet_ntoa(ConnectClient.sin_addr) << "\n";
		cout << "\nNoi dung nhan:\n\n";

		// Xóa nội dung REQUEST trước và nhận  REQUEST mới.
	//	memset(lpBuffRevc, 0, sizeof(lpBuffRevc));
		recv(NewConnection, lpBuffRevc, sizeof(lpBuffRevc), 0);
		/*

		XỬ  LÝ REQUEST => Ở ĐÂY MÌNH 1 KHÔNG 1 WEBSERVER CHUYỆN NGHIỆP NÊN BỎ QUA.
		*/
		// Gửi HEADER của SERVER và trang HTML
		

		cout << lpBuffRevc << "\n";

		// Đóng kết nối!
		//closesocket(NewConnection);
	}
}

int main()
{
	//Create winsock
	WORD DllVersion = MAKEWORD(2, 1);
	WSAData wsaData;
	if(WSAStartup(DllVersion, &wsaData) != 0)
	{
		cout << "Faild Startup" << endl;
	}

	SOCKADDR_IN addr;
	SOCKET sLinten = socket(AF_INET, SOCK_STREAM, NULL);
	SetupIPWS(sLinten, addr);
	LoopListen(sLinten, addr);
	return 0;
}