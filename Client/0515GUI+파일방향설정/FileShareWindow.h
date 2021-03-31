#include<stdio.h>
#include <stdlib.h>
#include<winsock.h>
#include<iostream> //
#include<fstream> //
#include<string>
#include <cstdlib>//

#pragma warning(disable:4996) 
//버퍼크기 정의efds
#define BUFSIZE 4096
#define _WINSOCK_DEPREATED_NO_WARNINGS
#pragma comment(lib,"Ws2_32.lib")
//#define user_ip "192.168.0.80 " //테스트용으로 define해줬던 거임
//#define user_Port 1234 //테스트용으로 define해줬던 거임

enum AdPos : int {
	top    = 0,
	left   = 1,
	right  = 2,
	bottom = 3
};
struct Position { int x, y; };

class Adopter {
public:
	Adopter(Position window_potion, Position window_size, HINSTANCE hInstance); //생성자
	void attach(int user_id); //id 로 부착
	void detach(); //없애기
	void run(WPARAM wParam, int pos); //동작
	void is_show(bool is_show) { is_show ? ShowWindow(hwnd_, SW_SHOW) : ShowWindow(hwnd_, SW_HIDE); }
	HWND& get_hwnd() { return hwnd_; }
private:
	HWND hwnd_;
	int user_id_;
};

class FileShareWindow //singleton class
{ 
public:
	static FileShareWindow& get_instance(HINSTANCE hInstance = NULL);
	void add_user(int user_id, AdPos pos);
	void detach(AdPos pos);
	void run(HWND hWnd, WPARAM wParam);
	~FileShareWindow();
private:
	FileShareWindow(HINSTANCE hInstance);
	int system_screen_width_;
	int system_screen_height_;
	Adopter adopters[4];
};


class FileTransfer
{
public:
	FileTransfer(SOCKET clientsock, sockaddr_in sockinfo, int pos) {
		// 초기화 시켜주는 작업을 여기서해

		//ip주소 초기화 자바에서 파일 생성하면 그거 읽어오는거 //////씨쁠쁠 소스 있는 폴더에다가 파일 생성해놓고 테스트
		char user_ip[13];

		FILE* filefp = fopen("UserIP.txt", "r"); //파일이름 설정 잘 해주기
		fgets(user_ip, sizeof(user_ip), filefp);
		fclose(filefp);
		
		//포트번호는 그냥 방향 따라서 (컴퓨터 다를테니까) 다르게 주자
		int user_Port;
		if(pos == 0) user_Port = 1234; //top으로 설정할 컴퓨터 포트번호를 1234로 설정
		else if (pos == 1) user_Port = 2345; //left
		else if (pos == 2) user_Port = 3456; //right
		else user_Port = 4567; //이거는 진짜 else임 bottom없으니까.. 쓸일이 없을것같음 
	
		sockinfo.sin_port = htons(user_Port); //포트번호 지정 (서버입장에서 클라이언트가 접속할 때 IP와 포트번호로 서비스 제공함)
		sockinfo.sin_addr.s_addr = inet_addr(user_ip); //IP주소 지정

		//서버에 연결 시도
		if (connect(clientsock, (SOCKADDR*)& sockinfo, sizeof(sockinfo)) == SOCKET_ERROR)
			printf(" 서버 접속 실패 ");
		if (connect(clientsock, (SOCKADDR*)& sockinfo, sizeof(sockinfo)))
			printf("서버에 접속 성공!\n");
	}

	void file_go(SOCKET clientsock, TCHAR *szPathName) {
		// 여기에 파일전송하는 함수 구현 반복문 오지게 넣어서 하는거
		
		//보낼 파일 설정
		char myFile[256];
		WideCharToMultiByte(CP_ACP, 0, szPathName, MAX_PATH, myFile, 256, NULL, NULL);

		//파일 열기
		FILE* fp;
		fp = fopen(myFile, "rb");
		//ifstream fileopen("");
		char filename[256];
		//strcpy_s(filename, sizeof(filename) ,myFile);
		ZeroMemory(filename, 256);
		sprintf(filename, myFile);

		// 여기서 파일이름 설정해주기 절대경로에서 뒤부터 읽어서 \ 표시 있으면 그 뒤를 끝까지 읽는다.
		char realFileName[256]; //강의.mp4와 같이 정말 파일 이름만 전송하려고 만든 변수임 
		int indexCheck=0;
		for (int i = 255; i >= 0; i--) {
			if (filename[i] == '\\') {
				indexCheck = i;
				break;
			}
		}
		int k = 0;
		while (1){
			indexCheck++;
			realFileName[k] = filename[indexCheck];
			k++;
			if (filename[indexCheck] == '\0') break;
		}
		
		//소켓으로 파일이름을 전송
		send(clientsock, realFileName, 256, 0); //여기서만 하면 
		//파일 크기 얻기
		fseek(fp, 0, SEEK_END);

		int totalbytes = ftell(fp);
		//파일 크기 소켓으로 보내기
		send(clientsock, (char*)& totalbytes, sizeof(totalbytes), 0); 
		

		//파일 데이터 전송에 사용할 변수
		char buf[BUFSIZE];
		int numread;
		int numtotal = 0;
		//파일 포인터를 제일 앞으로 이동
		rewind(fp);

		//반복적으로 파일 데이터 보내기
		while (1) {
			//파일의 내용을 버퍼에 담음
			numread = fread(buf, 1, BUFSIZE, fp);
			//파일 데이터가 조금이라도 남은경우
			if (numread > 0) {
				send(clientsock, buf, numread, 0);
				numtotal = numread;
			}
			//파일을 모두 전송한 경우/
			else if (numread == 0 && numtotal == totalbytes) {
				printf("총 %d바이트 파일 전송을 완료했습니다.\n", numtotal);
				break;
			}
		}
		fclose(fp);
		// 소켓폐기
		closesocket(clientsock);
		printf("서버에 접속 종료");
		//윈속종료
		WSACleanup();
	}
private:
	int strlen;
	FILE* fp;
	char myFile[256];
	char filename[256];

};