#pragma once
#include <Windows.h>

HRGN Drawcube(HWND hWnd, HDC hdc, POINT MINPOINT, POINT MAXPOINT);// ť��׸��� 

void Movecube(POINT* minPoint, POINT* maxPoint, int deltaX, int deltaY);//ť���̵�

void Scalecube(POINT* minPoint, POINT* maxPoint, int deltaX, int deltaY);//ť��Ű���