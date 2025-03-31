#include <Windows.h> //윈도우즈 API 기본 헤더

#define WIDTH 640 //display size width
#define HEIGHT 480//heigh

//윈도우즈가 해야할 일을 기록하고 프로그래밍하는 프로시저
LRESULT CALLBACK //콜백 ===> 윈도우즈가 호출 // 시스템 호출
WndProc(HWND hwnd,//현재 연결된 윈도우 핸들
	UINT umsg, //윈도우즈 메시지 //WM_ 이 앞에 붙는다
	WPARAM wparam, //파라미터 //주로 문자에 관한 데이터 들어옴
	LPARAM lparam) {//파라미터 //주로 숫자에 관한 데이터 들어옴
	switch (umsg) { //윈도우 메시지를 분류
	case WM_CREATE: //만약 시작할떄? 윈도우가 생성될때?
		break;
	case WM_PAINT: //그림이 그려질 필요가 있을 때 // 자주 발생 안함
		break;
	case WM_COMMAND: //윈도우에 들어오는 명령 //메뉴 선택
		break;
	case WM_CLOSE: //온화한 종료
		break;
	case WM_DESTROY: //강제종료
			PostQuitMessage(0);
			return 0;
	default:
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}

	
}

//윈도우 메인 함수
int APIENTRY WinMain(HINSTANCE hinst, //윈도우 영혼에 해당
	 HINSTANCE hprevinst, //윈도즈 3.0, 3.1 이런시기에 이용 //지금은 안씀
	LPSTR lpCmdLine, //EXE 파일 뒤에 오는 CMD 명령어 //(EX : dir /w, format c: /s
	int nshowcmd) { //윈도우가 보이는 상태 여부

	HWND hwnd;
	WNDCLASSEX wcex; //윈도우 클래스 작성 정의 //주문서 작성
	HINSTANCE hinstance = GetModuleHandle(NULL); 

	wcex.cbSize = sizeof(WNDCLASSEX); //어떤 주문서를 이용할지 종류를 정의 //클래스의 크기 설정

	wcex.cbClsExtra = 0; // 항상 0또는 NULL
	wcex.cbWndExtra = 0; // 항상 0또는 NULL
	wcex.hInstance = hinstance; //윈도우 영혼 매칭
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 배경 색 지정
	wcex.hCursor = LoadCursor(0, IDC_ARROW); //커서 설정
	wcex.hIcon = LoadIcon(hinstance, (LPCTSTR)IDI_APPLICATION); // 아이콘 설정
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_APPLICATION); //작은 아이콘 설정
	wcex.lpfnWndProc = WndProc; //함수의 포인터 // 생성될 윈도우의 프로시저 정의
	wcex.lpszClassName = L"MyWindowClass"; //윈도우즈의 이름 설정
	wcex.lpszMenuName = NULL; //메뉴설정 지금 없음
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; //윈도우 스타일 정의

	RegisterClassEx(&wcex);//주문

	hwnd = CreateWindow(L"MyWindowClass", //윈도우 이름 //wcex의 클래스 이름과 동일하게 작성해야함
		L"MyWindow", //타이틀 이름 (아무렇게나 가능)
		WS_OVERLAPPEDWINDOW, //윈도우의 형태
		0, 0, //윈도우 창의 위치
		WIDTH, HEIGHT, //윈도우 width, height
		NULL, //항상 NULL, 0
		NULL, //메뉴 설정
		hinstance, //윈도우 영혼 
		NULL); //항상 널 또는 0


	ShowWindow(hwnd, SW_SHOW); //윈도우 보여주기 설정 WinAPI 함수
	UpdateWindow(hwnd); //현제 윈도우 갱신 WinAPI함수

	MSG msg; // 윈도우 메시지 정의

	while (GetMessage(&msg, 0, 0, 0)) //만약 메시지 있으면 True => 실행
	{
		TranslateMessage(&msg); //문자와 관련된 메시지를 해석하는 WinAPI 함수   //프로시저로 넘김
		DispatchMessage(&msg); //나머지의 모든 메시지를 해석하는 WinAPI 함수    //프로시저로 넘김
	}

	return 0; //While이 끝나고 프로그램이 종료될 떄
}