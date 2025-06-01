#pragma once
enum MouseMSG { NONE, LBD, LBU, RBD, RBU, MBD, MBU, LDBLK, RDBLK, MDBLK };

int OnMouseWheel(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseLBUTTONDBLCLK(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseRBUTTONDBLCLK(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseMBUTTONDBLCLK(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseLBUTTONDOWN(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseLBUTTONUP(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseRBUTTONDOWN(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseRBUTTONUP(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseMBUTTONDOWN(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseMBUTTONUP(HWND hWnd, WPARAM wParam, LPARAM lParam);