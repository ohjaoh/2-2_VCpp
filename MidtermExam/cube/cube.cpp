#include "yuhanCG.h"
#include <Windows.h>
void Drawcube1(HWND hWnd, HDC hdc, POINT start, POINT end) {// �»�
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

	MoveToEx(hdc, MINPOINT.x, MAXPOINT.y, NULL); //�ظ� ��
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y);

	MoveToEx(hdc, MINPOINT.x, MINPOINT.y + centerY / 2, NULL); // �ո�
	LineTo(hdc, MINPOINT.x, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y + centerY / 2);//�ϳ��� �̹� ������ �׷��� ����

	MoveToEx(hdc, MAXPOINT.x, MINPOINT.y, NULL); // ����
	LineTo(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
}
void Drawcube2(HWND hWnd, HDC hdc, POINT start, POINT end) {// ����
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

	MoveToEx(hdc, MINPOINT.x + centerX / 2, MINPOINT.y, NULL); //�ظ�
	LineTo(hdc, MINPOINT.x, MINPOINT.y + centerY / 2);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y + centerY / 2);
	LineTo(hdc, MAXPOINT.x, MINPOINT.y);
	LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y);

	MoveToEx(hdc, MINPOINT.x, MINPOINT.y + centerY / 2, NULL); // �ո�
	LineTo(hdc, MINPOINT.x, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y + centerY / 2);//�ϳ��� �̹� ������ �׷��� ����

	MoveToEx(hdc, MAXPOINT.x, MINPOINT.y, NULL); // ����
	LineTo(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
}
void Drawcube3(HWND hWnd, HDC hdc, POINT start, POINT end) {// ���
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

	MoveToEx(hdc, MINPOINT.x + centerX / 2, MINPOINT.y, NULL); //�ظ�
	LineTo(hdc, MINPOINT.x, MINPOINT.y + centerY / 2);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y + centerY / 2);
	LineTo(hdc, MAXPOINT.x, MINPOINT.y);
	LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y);

	MoveToEx(hdc, MINPOINT.x, MINPOINT.y + centerY / 2, NULL); // �ո�
	LineTo(hdc, MINPOINT.x, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y + centerY / 2);//�ϳ��� �̹� ������ �׷��� ����

	MoveToEx(hdc, MAXPOINT.x, MINPOINT.y, NULL); // ����
	LineTo(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
}
void Drawcube4(HWND hWnd, HDC hdc, POINT start, POINT end) {// ���� �ϼ�
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

	MoveToEx(hdc, MINPOINT.x + centerX / 2, MINPOINT.y, NULL); //�ظ�
	LineTo(hdc, MINPOINT.x, MINPOINT.y + centerY / 2);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y + centerY / 2);
	LineTo(hdc, MAXPOINT.x, MINPOINT.y);
	LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y);

	MoveToEx(hdc, MINPOINT.x, MINPOINT.y + centerY / 2, NULL); // �ո�
	LineTo(hdc, MINPOINT.x, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y + centerY / 2);//�ϳ��� �̹� ������ �׷��� ����

	MoveToEx(hdc, MAXPOINT.x, MINPOINT.y, NULL); // ����
	LineTo(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2);
	LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
}