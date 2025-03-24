#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <tchar.h>

#define _MYDJ

int main(int argc, char* argv[])
{
	#ifdef _UNICODE    //유니코드 입력
		wchar_t strBuffer[128] = _T("Hello, World!!! 안녕, 세상!!!");
		wchar_t strTitle[32] = _T("MessageBox");
		wchar_t strTemp[128];
		int nSize = wcslen(strBuffer);
	#endif
	#ifdef _MBCS              //멀티바이트 입력
		char strBuffer[128] = "Hello, World!!!\n안녕, 세상!!!";
		char strTitle[32] = "MessageBox";
		char strTemp[128];
		int nSize = strlen(strBuffer);
	#endif

	#ifdef _UNICODE    //유니코드 출력
		std::locale::global(std::locale("kor"));
		printf_s("%ls %d\n", strBuffer, nSize);
		std::wcout << strBuffer << " " << nSize << "\n";
		wsprintf(strTemp, _T("%s %d"), strBuffer, nSize);
	#else              //멀티바이트 출력
		printf("%s %d\n", strBuffer, nSize);
		std::cout << strBuffer << " " << nSize << "\n";
		sprintf(strTemp, "%s %d", strBuffer, nSize);
	#endif
		MessageBox(NULL, strTemp, strTitle, MB_OK);
		return 0;

	#ifdef _MYDJ
		MessageBox(NULL, strTemp, strTitle, MB_OK);
	#endif
		return 0;
}

