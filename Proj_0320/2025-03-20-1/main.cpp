//C, C++, Windows MessageBox
#include <stdio.h>
#include <iostream>
#include <Windows.h>

int main(int argc, char* argv[])
{
	printf("Hello, C World!!! \n");
	std::cout << "Hello, C++ World!!!" << std::endl;
	MessageBox(NULL, L"Hello, Window World!!!", L"MessageBox", MB_OK);
	
	return 0;
}