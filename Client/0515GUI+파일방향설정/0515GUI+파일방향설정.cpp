#include "framework.h"
#define WINVER 0x500  
#define _WIN32_WINNT 0x500  
#include <windows.h>
#include <shellapi.h>
#include "FileShareWindow.h"
	//콜백 - 운영체제에 의하여 호출
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	MSG msg; //메시지
	WNDCLASS WndClass; //윈도우클래스
	WndClass.style = CS_HREDRAW | CS_VREDRAW; //윈도우 스타일
	WndClass.lpfnWndProc = WndProc; //프로시저 함수
	WndClass.cbClsExtra = 0; //여분 메모리
	WndClass.cbWndExtra = 0; //여분 메모리
	WndClass.hInstance = hInstance; //핸들 인스턴스
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //윈도우 아이콘
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //마우스 커서 아이콘
	WndClass.hbrBackground = CreateSolidBrush(RGB(0, 0, 0)); //배경 색
	WndClass.lpszMenuName = NULL; //메뉴
	WndClass.lpszClassName = L"Window Class Name"; //클래스이름
	RegisterClass(&WndClass); //내가 사용할 클래스를 등록 (운영체제의 커널에 등록됨)

	auto file_window = FileShareWindow::get_instance(hInstance); //FileShareWindow라는 객체생성
	
												

	file_window.add_user(1, AdPos::top); //user추가 add_user에서 user_id 와 방향을 확인하여 adaptor객체생성함
	file_window.add_user(2, AdPos::left); //
	file_window.add_user(3, AdPos::right); //

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); //키보드 해석
		DispatchMessage(&msg); //메시지 전달
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	
	switch (iMsg) //메시지 처리
	{
	case WM_CREATE:
		break;
	case WM_CHAR:
		//obj.user_ip_id_setting(hwnd, wParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_DROPFILES:
		FileShareWindow::get_instance().run(hwnd, wParam);
		break;

	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);   //처리되지 않은 메시지 반환
}