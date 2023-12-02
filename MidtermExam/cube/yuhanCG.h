#pragma once
#include <Windows.h>

void DrawBonobono(HWND hWnd, HDC hdc, int blink);

void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);

RECT MoveRactangle(LPARAM lParam, RECT ractangles, POINT start);

RECT ScaleCircle(LPARAM lParam, RECT Ellipse, POINT start);

RECT Drawrect(RECT rect, POINT startPoint, POINT endPoint);