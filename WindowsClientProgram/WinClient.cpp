#include <winsock2.h>
#include <stdio.h>
#include <iostream>
#include <string>

#define SEVER_IP_ADDRESSE "60.135.230.52"
#define SERVER_PORT 11110

#define BUFSIZE 256
#define RECVSIZE 65536

#define SLEEP_TIME 1

using namespace std;

int main() {

	// セットアップ
	WSADATA wsaDate;
	// サーバー情報
	SOCKADDR_IN server;

	// 初期化
	WSAStartup(MAKEWORD(2, 0), &wsaDate);

	// ソケット生成
	int soc;
	char sendBuf[BUFSIZE];
	char recvBuf[RECVSIZE];
	int recvLen = 0;
	
	soc = socket(AF_INET, SOCK_STREAM, 0);

	// サーバーアドレス情報
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.S_un.S_addr = inet_addr(SEVER_IP_ADDRESSE);

	// サーバーに接続
	/*if ( connect(soc,(LPSOCKADDR)&server, sizeof(server)) < 0);
	{
		printf("サーバーへの接続失敗です%d\n",WSAGetLastError());
		closesocket(soc);
		return -1;
	}
*/


	// データをサーバーに送信
	

	while (true)
	{
	string sendText;
	connect(soc, (LPSOCKADDR)&server, sizeof(server));

		cin >> sendText;
		cout << "send:" << sendText << endl;
		if (send(soc, sendText.c_str(), sendText.size(), 0) == SOCKET_ERROR)
		{
			printf("サーバーへの送信失敗です%d\n", WSAGetLastError());
			closesocket(soc);
			sendText.clear();
			return -1;
		}
		else
		{
			// 受信
			recvLen = recv(soc, recvBuf, RECVSIZE, 0);
			string receive(recvBuf, recvLen);
			cout << "receve:" << receive << WSAGetLastError() << endl;
		}
		Sleep(SLEEP_TIME);

	}

	// 終了
	closesocket(soc);
	WSACleanup();
	return 0;
}