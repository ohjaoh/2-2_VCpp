#pragma once
#include <Windows.h>

HRGN Drawcube(HWND hWnd, HDC hdc, POINT MINPOINT, POINT MAXPOINT);// 큐브그리기 

void Movecube(POINT* minPoint, POINT* maxPoint, int deltaX, int deltaY);//큐브이동

void ScaleCube(POINT* minPoint, POINT* maxPoint, int deltaX);//큐브크기조정(주의 크기를 줄이고 나서 키우면 큐브의 비율이 달라짐)