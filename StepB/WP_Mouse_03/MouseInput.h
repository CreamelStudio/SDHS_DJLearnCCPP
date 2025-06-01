#pragma once

enum MouseMSG { NONE, LBD, LBU, RBD, RBU, MBD, MBU, LDBLK, RDBLK, MDBLK };

int OnMouseWheel(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseLBTNDBLCLK(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseRBTNDBLCLK(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseMBTNDBLCLK(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseLBTNDN(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseLBTNUP(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseRBTNDN(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseRBTNUP(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseMBTNDN(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseMBTNUP(HWND hWnd, WPARAM wParam, LPARAM lParam);
int OnMouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);