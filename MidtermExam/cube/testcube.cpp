#include "test.h"
#include <Windows.h>

//중앙 400, 240 392 233

void Drawcube1(HWND hWnd, HDC hdc, POINT start, POINT end) {// 좌상
	POINT MINPOINT = { 0 };
	POINT MAXPOINT = { 0 };

	MINPOINT.x = min(start.x, end.x);
	MINPOINT.y = min(start.y, end.y);
	MAXPOINT.x = max(start.x, end.x);
	MAXPOINT.y = max(start.y, end.y);


	MoveToEx(hdc, 376, 0, NULL);
	LineTo(hdc, 376, 480);
	MoveToEx(hdc, 0, 184, NULL);
	LineTo(hdc, 800, 184);



	int width = abs(MINPOINT.x - MAXPOINT.x);
	int height = abs(MINPOINT.y - MAXPOINT.y);
	int centerX = width / 2;
	int centerY = height / 2;
	POINT centerPoint = { MINPOINT.x + centerX, MINPOINT.y + centerY };

	MoveToEx(hdc, MINPOINT.x, MAXPOINT.y, NULL); //밑면 반시계순
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MINPOINT.x, MAXPOINT.y);

	MoveToEx(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2, NULL); // 앞면 반시계순
	LineTo(hdc, MAXPOINT.x, MINPOINT.y);
	LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y);
	LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y - centerY / 2);

	MoveToEx(hdc, MINPOINT.x + centerX / 2, MINPOINT.y, NULL); // 옆면 우하시작 반시계
	LineTo(hdc, MINPOINT.x, MINPOINT.y + centerY / 2);
	LineTo(hdc, MINPOINT.x, MAXPOINT.y);
}
//1 완

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

	MoveToEx(hdc, MINPOINT.x, MINPOINT.y, NULL); //밑면
	LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y + centerY / 2);
	LineTo(hdc, MAXPOINT.x, MINPOINT.y + centerY / 2);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y);
	LineTo(hdc, MINPOINT.x, MINPOINT.y);//복귀

	MoveToEx(hdc, MINPOINT.x + centerX / 2, MINPOINT.y + centerY / 2, NULL); // 앞면
	LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x, MINPOINT.y + centerY / 2);
	LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y + centerY / 2);//하나는 이미 위에서 그려서 생략

	MoveToEx(hdc, MINPOINT.x, MINPOINT.y, NULL); // 옆면
	LineTo(hdc, MINPOINT.x, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y);
}
//2완

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

	MoveToEx(hdc, MINPOINT.x, MAXPOINT.y - centerY / 2, NULL); //밑면 반시계순
	LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MINPOINT.x, MAXPOINT.y - centerY / 2);

	MoveToEx(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y - centerY / 2, NULL); // 앞면 반시계순
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y);
	LineTo(hdc, MINPOINT.x, MINPOINT.y);
	LineTo(hdc, MINPOINT.x, MAXPOINT.y - centerY / 2);

	MoveToEx(hdc, MAXPOINT.x, MAXPOINT.y, NULL); // 옆면 우하시작 반시계
	LineTo(hdc, MAXPOINT.x, MINPOINT.y + centerY / 2);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y);
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