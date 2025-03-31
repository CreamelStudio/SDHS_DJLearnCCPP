// WindowsProject1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100 // 글자 수 최대값

// Global Variables:
HINSTANCE hInst;                                // 현재 인스턴스
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, //윈도우 인스턴스 //메모리 상에서 활성화
                     _In_opt_ HINSTANCE hPrevInstance, //필요없음 윈도우 3.0에서만 이용가능
                     _In_ LPWSTR    lpCmdLine, //커멘드 명령 //추가 명령
                     _In_ int       nCmdShow) //윈도우가 보일지 말지 //어떻게 보일지
{
    UNREFERENCED_PARAMETER(hPrevInstance); //사용하지 않는 파라미터 처리 //매크로 함수 (디파인)
    UNREFERENCED_PARAMETER(lpCmdLine); //사용하지 않는 파라미터 처리 //매크로 함수 (디파인)

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING); //100개의 스트링을
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0)) //메시지가 있으면 트루, 없으면 대기
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) //엑셀레이터 실행
        {
            TranslateMessage(&msg); //문자와 관련된 메시지 처리
            DispatchMessage(&msg); //나머지 메시지 처리
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; //윈도우 스타일, 더블클릭(마지막꺼)
    wcex.lpfnWndProc    = WndProc; //함수의 포인터
    wcex.cbClsExtra     = 0; //항상 0 또는 널
    wcex.cbWndExtra     = 0; //항상 0 또는 널
    wcex.hInstance      = hInstance; //윈도우 영혼 
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1)); //아이콘 적용
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW); //커서 적용 (화살표)
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1); //배경 색
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1); //메뉴
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); //작은 아이콘

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, //이곳의 정의와 윈도우 클래스의 정의가 같아야함
       szTitle, //윈도우 타이틀 표시
       WS_OVERLAPPEDWINDOW, //윈도우 모양
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, //x y w h 를 나타냄
       nullptr, nullptr, //
       hInstance, //윈도우 인스턴스
       nullptr);

   if (!hWnd) //만약 윈도우 핸들이 널이면 종료 // 아니면 건너뜀
   {
      return FALSE; //종료
   }

   ShowWindow(hWnd, nCmdShow); //윈도우 보이기 여부
   UpdateWindow(hWnd); //윈도우 리플레시

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int x = 0;
    static int y = 0;

    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_MENU1:
            MessageBox(hWnd, L"첫번째 메뉴", L"MENU", MB_OK);
            break;
        case IDM_MENU2:
            MessageBox(hWnd, L"두번째 메뉴", L"MENU", MB_OK);
            break;
        }
        break;
    }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다..
            TextOut(hdc, x, 0, L"첫 번째 윈도우 글자 출력 입니다..", 19);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_KEYDOWN:
        if (wParam == VK_LEFT) x += 10;
        if (wParam == VK_RIGHT) x -= 10;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case IDM_EXIT:
        DestroyWindow(hWnd);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
