#include "yuhanCG.h"
#include <Windows.h>
void Drawcube1(HWND hWnd, HDC hdc, POINT start, POINT end) {// 좌상
	POINT MINPOINT = { 0 };
	POINT MAXPOINT = { 0 };

	MINPOINT.x = min(start.x, end.x);
	MINPOINT.y = min(start.y, end.y);
	MAXPOINT.x = max(start.x, end.x);
	MAXPOINT.y = max(start.y, end.y);

	int width = abs(MINPOINT.x - MAXPOINT.x);
	int height = abs(MINPOINT.y - MAXPOINT.y);
	int centerX = width / 2;
	int centerY = height / 2;
	POINT centerPoint = { MINPOINT.x + centerX, MINPOINT.y + centerY };

	MoveToEx(hdc, MINPOINT.x, MAXPOINT.y, NULL); //밑면 완
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y);

	MoveToEx(hdc, MINPOINT.x, MINPOINT.y + centerY / 2, NULL); // 앞면
	LineTo(hdc, MINPOINT.x, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y + centerY / 2);//하나는 이미 위에서 그려서 생략

	MoveToEx(hdc, MAXPOINT.x, MINPOINT.y, NULL); // 옆면
	LineTo(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
}
void Drawcube2(HWND hWnd, HDC hdc, POINT start, POINT end) {// 좌하
	POINT MINPOINT = { 0 };
	POINT MAXPOINT = { 0 };

	MINPOINT.x = min(start.x, end.x);
	MINPOINT.y = min(start.y, end.y);
	MAXPOINT.x = max(start.x, end.x);
	MAXPOINT.y = max(start.y, end.y);

	int width = abs(MINPOINT.x - MAXPOINT.x);
	int height = abs(MINPOINT.y - MAXPOINT.y);
	int centerX = width / 2;
	int centerY = height / 2;
	POINT centerPoint = { MINPOINT.x + centerX, MINPOINT.y + centerY };

	MoveToEx(hdc, MINPOINT.x + centerX / 2, MINPOINT.y, NULL); //밑면
	LineTo(hdc, MINPOINT.x, MINPOINT.y + centerY / 2);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y + centerY / 2);
	LineTo(hdc, MAXPOINT.x, MINPOINT.y);
	LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y);

	MoveToEx(hdc, MINPOINT.x, MINPOINT.y + centerY / 2, NULL); // 앞면
	LineTo(hdc, MINPOINT.x, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y + centerY / 2);//하나는 이미 위에서 그려서 생략

	MoveToEx(hdc, MAXPOINT.x, MINPOINT.y, NULL); // 옆면
	LineTo(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
}
void Drawcube3(HWND hWnd, HDC hdc, POINT start, POINT end) {// 우상
	POINT MINPOINT = { 0 };
	POINT MAXPOINT = { 0 };

	MINPOINT.x = min(start.x, end.x);
	MINPOINT.y = min(start.y, end.y);
	MAXPOINT.x = max(start.x, end.x);
	MAXPOINT.y = max(start.y, end.y);

	int width = abs(MINPOINT.x - MAXPOINT.x);
	int height = abs(MINPOINT.y - MAXPOINT.y);
	int centerX = width / 2;
	int centerY = height / 2;
	POINT centerPoint = { MINPOINT.x + centerX, MINPOINT.y + centerY };

	MoveToEx(hdc, MINPOINT.x + centerX / 2, MINPOINT.y, NULL); //밑면
	LineTo(hdc, MINPOINT.x, MINPOINT.y + centerY / 2);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y + centerY / 2);
	LineTo(hdc, MAXPOINT.x, MINPOINT.y);
	LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y);

	MoveToEx(hdc, MINPOINT.x, MINPOINT.y + centerY / 2, NULL); // 앞면
	LineTo(hdc, MINPOINT.x, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y + centerY / 2);//하나는 이미 위에서 그려서 생략

	MoveToEx(hdc, MAXPOINT.x, MINPOINT.y, NULL); // 옆면
	LineTo(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
}
void Drawcube4(HWND hWnd, HDC hdc, POINT start, POINT end) {// 우하 완성
	POINT MINPOINT = { 0 };
	POINT MAXPOINT = { 0 };

	MINPOINT.x = min(start.x, end.x);
	MINPOINT.y = min(start.y, end.y);
	MAXPOINT.x = max(start.x, end.x);
	MAXPOINT.y = max(start.y, end.y);

	int width = abs(MINPOINT.x - MAXPOINT.x);
	int height = abs(MINPOINT.y - MAXPOINT.y);
	int centerX = width / 2;
	int centerY = height / 2;
	POINT centerPoint = { MINPOINT.x + centerX, MINPOINT.y + centerY };

	MoveToEx(hdc, MINPOINT.x + centerX / 2, MINPOINT.y, NULL); //밑면
	LineTo(hdc, MINPOINT.x, MINPOINT.y + centerY / 2);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y + centerY / 2);
	LineTo(hdc, MAXPOINT.x, MINPOINT.y);
	LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y);

	MoveToEx(hdc, MINPOINT.x, MINPOINT.y + centerY / 2, NULL); // 앞면
	LineTo(hdc, MINPOINT.x, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y + centerY / 2);//하나는 이미 위에서 그려서 생략

	MoveToEx(hdc, MAXPOINT.x, MINPOINT.y, NULL); // 옆면
	LineTo(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
}