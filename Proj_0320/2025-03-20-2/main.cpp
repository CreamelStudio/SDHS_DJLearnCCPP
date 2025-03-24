#include <Windows.h>
#include <tchar.h>

int WINAPI WinMain(HINSTANCE , HINSTANCE , PSTR , int )
{
	MessageBox(NULL, _T("Hello, Window World!!!"), _T("MessageBox"), MB_OK);
	return 0;
}