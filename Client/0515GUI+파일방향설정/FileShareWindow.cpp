#include "FileShareWindow.h"

Adopter::Adopter(Position window_potion, Position window_size, HINSTANCE hInstance) :user_id_(0) {
	hwnd_ = CreateWindow(L"Window Class Name", L"File Transfer", WS_POPUP, window_potion.x, window_potion.y, window_size.x, window_size.y, NULL, NULL, hInstance, NULL);
	DragAcceptFiles(hwnd_, TRUE);
	SetWindowLong(hwnd_, GWL_EXSTYLE, GetWindowLong(hwnd_, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hwnd_, 0, 130, LWA_ALPHA);
	is_show(false);
	UpdateWindow(hwnd_);
}

void Adopter::attach(int user_id)  { user_id_ = user_id; is_show(true); }  //user_id입력받은것이 0일땐 is_show안하고 user+id private의 user_id랑 비교해서 같으면 is_show동작
void Adopter::detach() { user_id_ = 0; is_show(false); }

void Adopter::run( WPARAM wParam, int pos) {
	TCHAR szPathName[MAX_PATH] = { '\0', }; //szPathName : 파일의 경로를 얻을 변수
	UINT num = DragQueryFile((HDROP)wParam, -1, 0, 0);  //드래그 된 파일의 경로를 얻을거임
	for (UINT n = 0; n < num; ++n) {
		UINT result = DragQueryFile((HDROP)wParam, n, szPathName, MAX_PATH);
	}
	DragFinish((HDROP)wParam);  //드래그 끝

	SOCKET clientsock; //소켓생성
	WSADATA wsa; //소켓프로그래밍 함수사용위한 선언
	struct sockaddr_in sockinfo;//소켓 주소 구조체 선언
	char message[30];
	int strlen;
	/*	if (argc != 3)
		{
			printf("Usage : %s <IP> <PORT> \n", argv[0]);
			//	exit(1);
		}*/

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)  //소켓프로그래밍 초기화
		printf("초기화 실패\n");

	clientsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //주소체계 , 소켓타입(TCP/IP라서 STREAM), 프로토콜:TCP
	//인터넷 영역을 사용하는 TCP방식의 프로토콜 소켓 생성 =>clientsock
	if (clientsock == INVALID_SOCKET) //INVALID_SOCKET : 에러코드값
		printf("소켓 생성 실패\n");

	memset(&sockinfo, 0, sizeof(sockinfo));
	sockinfo.sin_family = AF_INET;

	//class 객체새로 만들고 함수 호출
	FileTransfer obj(clientsock,sockinfo,pos); //생성자에서 포트랑 아이피 설정해줌..
	obj.file_go(clientsock,szPathName);

	//MessageBox(hwnd_, szPathName, (LPCWSTR)"a", MB_OK); // 여기에 파일전송 함수 호출
}

FileShareWindow& FileShareWindow::get_instance(HINSTANCE hInstance) {
	static FileShareWindow instance(hInstance);
	return instance;
}

FileShareWindow::FileShareWindow(HINSTANCE hInstance) 
	: system_screen_height_(GetSystemMetrics(SM_CXSCREEN))
	, system_screen_width_(GetSystemMetrics(SM_CYSCREEN))
	, adopters{
		   {{500,0}, {system_screen_width_*2-1250, 40}, hInstance}  //top
		 , {{0,200}, {40,system_screen_height_-1250}, hInstance} //left
		 , {{system_screen_width_ *2 - 280,200}, {40,system_screen_height_-1250}, hInstance} //right
		 , {{0,system_screen_height_-1000}, {system_screen_width_*2,40},  hInstance} //bottom
	}
{ }

void FileShareWindow::add_user(int user_id, AdPos pos) {
	adopters[pos].attach(user_id);
}

void FileShareWindow::detach(AdPos pos) {
	adopters[pos].detach();
}

void FileShareWindow::run(HWND hWnd, WPARAM wParam) {
	for (int i = 0; i < 4; ++i) {
		if (adopters[i].get_hwnd() == hWnd) adopters[i].run(wParam,i);
	}
}

FileShareWindow::~FileShareWindow() { }
