#pragma once
#include <Windows.h>

HRGN Drawcube(HWND hWnd, HDC hdc, POINT MINPOINT, POINT MAXPOINT);// 큐브그리기 

void Movecube(HWND hWnd, HDC hdc, LPARAM lParam, POINT start);//큐브이동

void Scalecube(HWND hWnd, HDC hdc, LPARAM lParam, POINT start);//큐브키우기