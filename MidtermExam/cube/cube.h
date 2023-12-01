#pragma once
#include <Windows.h>

HRGN Drawcube(HWND hWnd, HDC hdc, POINT MINPOINT, POINT MAXPOINT);// 큐브그리기 

void Movecube(POINT* minPoint, POINT* maxPoint, int deltaX, int deltaY);//큐브이동

void Scalecube(POINT* minPoint, POINT* maxPoint, int deltaX, int deltaY);//큐브키우기