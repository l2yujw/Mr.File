#include <stdio.h>
#include <WinSock2.h>
#include <stdlib.h>

//버퍼크기 정의
#define BUFSIZE 4096
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")

int dataReceive(SOCKET s, char* buf, int len, int flags);

int main(int argc, char* argv[]) {
	//데이터 크기를 담을 변수
	int retval;

	SOCKET sock, clientsock;
	WSADATA wsa;
	struct sockaddr_in sockinfo, clientinfo;
	int clientsize;
	char message[] = "success";
	char buf[BUFSIZE];

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		printf("초기화 실패\n");

	//연결용 소켓 생성 및 초기화.
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sock == INVALID_SOCKET)
		printf("소켓 생성 실패\n");
	//소바인딩 처리 변수 초기화
	ZeroMemory(&sockinfo, sizeof(sockinfo));
	sockinfo.sin_family = AF_INET;
	sockinfo.sin_port = htons(1234);
	sockinfo.sin_addr.s_addr = htonl(INADDR_ANY);

	//바인딩
	if (bind(sock, (SOCKADDR*)& sockinfo, sizeof(sockinfo)) == SOCKET_ERROR)
		printf(" bind 실패 ");
	//연결함수 시작
	if (listen(sock, SOMAXCONN) == SOCKET_ERROR)
		printf(" 대기열 실패 ");

	//반복적으로 클라이언트로부터 소켓 요청 받기

	while (1) {
		clientsize = sizeof(clientinfo);

		printf("클라이언트로부터 접속을 기다리고 있습니다...\n");

		clientsock = accept(sock, (SOCKADDR*)& clientinfo, &clientsize);

		if (clientsock == INVALID_SOCKET)
			printf(" 클라이언트 소켓 연결 실패 ");
		printf("클라이언트 접속");
		//파일 이름 받기
		char filename[256]= "URF4C2.jpg";
		ZeroMemory(filename, 256);
		dataReceive(clientsock, filename, 256, 0);
		printf("받을 파일 이름: %s\n", filename);
		int totalbytes; //받을 파일의 크기는
		dataReceive(clientsock, (char*)& totalbytes, sizeof(totalbytes), 0);
		printf("받을 파일 크기:%d 바이트\n", totalbytes);

		//file opens
		errno_t err; //이거 왜썻ㅆ었는지 좀 알아봐라 기억도안난다.
		FILE* fp;
	//	fp = fopen(filename, "wb");

		err = fopen_s(&fp, filename, "wb"); //여기서 왜 안되냐 fp = fopen (filename, "wb") 로 하면 왜  또 널값들어가는가 뭐감 문제야
		if (err == 0) //err의 근본이 무너데?
			puts("파일오픈 성공!\n");
		else {
			puts("파일 오픈 실패\n");
			return -1;
		}

		int numtotal = 0;
		while (1) {
			retval = dataReceive(clientsock, buf, BUFSIZE, 0);
			//더 받을 데이터가 없을때
			if (retval == 0) break;
			else {
				fwrite(buf, 1, retval, fp); //////fp가 null 이라서 안되는중임
				//받은 데이터 크기만큼 변수에 더해줌
				numtotal += retval;
			}
		}
		//전송결과
		if (numtotal == totalbytes)
			printf("파일을 성공적으로 받았습니다.\n");
		else printf("파일을 제대로 받지 못했습니다.\n");
		//해당 클라이언트 소켓 폐기
		closesocket(clientsock);
		printf("클라이언트 종료");
	
	}
	//send(clientsock, message, sizeof(message), 0);
	closesocket(sock);

	printf("성공\n");

	WSACleanup();
}
int dataReceive(SOCKET s, char* buf, int len, int flags) {
	//통신에 필요한 변수 선언
	int received;
	char* ptr = buf;
	int left = len;
	//남아있는 데이터가 있는 경우 반복적으로 시행
	while (left > 0) {
		received = recv(s, ptr, left, flags);
		//더 이상 데이터를 받아오지 못하는 경우
		if (received == 0) break;
		//받아온 데이터가 존재하는 경우
		left -= received;
		ptr += received;
	}
	//더 받을 수 있는데이터길이를 반환 데이터를 한번이라도 받았으면 0이아닌수를 반환하게된
	return (len - left);
}