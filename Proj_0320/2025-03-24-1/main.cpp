#include <Windows.h>
#include <CommCtrl.h>  // DateTimePicker 컨트롤을 사용하기 위해 필요
#include "resource.h"
#include <tchar.h>

#pragma comment(lib, "comctl32.lib")  // Common Controls 라이브러리 링크

// 다이얼로그 프로시저 선언
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

// 선택된 날짜를 저장할 문자열 버퍼
TCHAR timeStr[100];

int main(int argc, char* argv[])
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

    // 공용 컨트롤 초기화 (DateTimePicker 사용을 위해 필요)
    InitCommonControls();

    // 다이얼로그 실행
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);

    return 0;
}

// 다이얼로그 프로시저 정의
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

    switch (message)
    {
    case WM_INITDIALOG:
    {
        // 다이얼로그 초기화 시 현재 시간을 DateTimePicker에 설정
        SYSTEMTIME st;
        GetLocalTime(&st);
        SendDlgItemMessage(hDlg, IDC_DATETIMEPICKER1, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)&st);

        return (INT_PTR)TRUE;
    }

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            // DateTimePicker에서 선택된 날짜 가져오기
            SYSTEMTIME st;
            LRESULT result = SendDlgItemMessage(hDlg, IDC_DATETIMEPICKER1, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);

            if (result == GDT_VALID) // 유효한 날짜인지 확인
            {
                // 날짜를 문자열로 포맷팅 (YYYY-MM-DD 형식)
                _stprintf_s(timeStr, 100, _T("%04d-%02d-%02d"), st.wYear, st.wMonth, st.wDay);

                // 선택된 날짜를 메시지 박스로 출력
                MessageBox(hDlg, timeStr, _T("선택된 날짜"), MB_OK);
            }
            else
            {
                // 유효하지 않은 날짜가 선택되었을 경우 오류 메시지 표시
                MessageBox(hDlg, _T("유효한 날짜를 선택하세요!"), _T("오류"), MB_OK | MB_ICONERROR);
            }
            return (INT_PTR)TRUE;
        }

        case IDCANCEL:
            // 다이얼로그 종료
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;

    case WM_CLOSE:
        // 다이얼로그 닫기
        EndDialog(hDlg, 0);
        return (INT_PTR)TRUE;
    }

    return (INT_PTR)FALSE;
}