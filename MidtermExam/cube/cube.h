#pragma once
#include <Windows.h>

HRGN Drawcube(HWND hWnd, HDC hdc, POINT MINPOINT, POINT MAXPOINT);// ť��׸��� 

void Movecube(HWND hWnd, HDC hdc, LPARAM lParam, POINT start);//ť���̵�

void Scalecube(HWND hWnd, HDC hdc, LPARAM lParam, POINT start);//ť��Ű���