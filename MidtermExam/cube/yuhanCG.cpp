#include "yuhanCG.h"
#include <Windows.h>
void DrawBonobono(HWND drawingView, HDC hdc, int blink) {
	if (blink == 0) {// ���뺸�� ����
		PAINTSTRUCT ps;
		// �Ǻλ�
		HBRUSH skinBrush = CreateSolidBrush(RGB(127, 200, 255));
		SelectObject(hdc, skinBrush);
		// �׸��� ���� �Ǻ� �κ��� �׸��ϴ�.
		Ellipse(hdc, 212, 23, 543, 363);//x+2 y-14

		// �� ��
		HBRUSH mouthBrush = CreateSolidBrush(RGB(255, 150, 255));
		SelectObject(hdc, mouthBrush);
		Ellipse(hdc, 357, 181, 397, 306);

		// �� �� �κ�
		HBRUSH Whites = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hdc, Whites);
		Ellipse(hdc, 328, 196, 378, 236); 
		Ellipse(hdc, 378, 196, 426, 236);

		// �� �κ� (�� ���� Ư���� ������� �ʾ����Ƿ� �⺻ �������� ����մϴ�.)
		HBRUSH Blacks = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hdc, Blacks);
		Ellipse(hdc, 258, 156, 268, 176);
		Ellipse(hdc, 498, 156, 488, 176);

		// ���� �� �κ�
		Ellipse(hdc, 358, 176, 398, 216);

		// �� ������
		SelectObject(hdc, Whites);
		Ellipse(hdc, 260, 161, 268, 166);
		Ellipse(hdc, 490, 161, 498, 166);
		//����
		MoveToEx(hdc, 348, 211, NULL);
		LineTo(hdc, 318, 196);

		MoveToEx(hdc, 408, 211, NULL);
		LineTo(hdc, 438, 196);
		
		MoveToEx(hdc, 348, 221, NULL);
		LineTo(hdc, 318, 236);

		MoveToEx(hdc, 408, 221, NULL);
		LineTo(hdc, 438, 236);
		// ����� �귯�� ���ҽ��� �����մϴ�.
		DeleteObject(skinBrush);
		DeleteObject(mouthBrush);
		DeleteObject(Whites);
		DeleteObject(Blacks);
		//x + 2 y - 14
		/*// �߾Ӽ� ���߿� �����
		MoveToEx(hdc, 376, 0, NULL);
		LineTo(hdc, 376, 480);
		MoveToEx(hdc, 0, 188, NULL);
		LineTo(hdc, 800, 188);*/


		EndPaint(drawingView, &ps);
	}
	else if (blink == 1) {// ���뺸�� ������
		PAINTSTRUCT ps;
		// �Ǻλ�
		HBRUSH skinBrush = CreateSolidBrush(RGB(127, 200, 255));
		SelectObject(hdc, skinBrush);
		// �׸��� ���� �Ǻ� �κ��� �׸��ϴ�.
		Ellipse(hdc, 212, 23, 543, 363);
		// �� ��
		HBRUSH mouthBrush = CreateSolidBrush(RGB(255, 150, 255));
		SelectObject(hdc, mouthBrush);
		Ellipse(hdc, 357, 181, 397, 306);

		// �� �� �κ�
		HBRUSH Whites = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hdc, Whites);
		Ellipse(hdc, 328, 196, 378, 236);
		Ellipse(hdc, 378, 196, 426, 236);

		// �� �κ�
		//�޴�
		MoveToEx(hdc, 263, 161, NULL);
		LineTo(hdc, 248, 151);
		MoveToEx(hdc, 263, 161, NULL);
		LineTo(hdc, 248, 171);
		//������
		MoveToEx(hdc, 493, 161, NULL);
		LineTo(hdc, 508, 151);
		MoveToEx(hdc, 493, 161, NULL);
		LineTo(hdc, 508, 171);

		// ���� �� �κ�//x+2 y-14
		HBRUSH Blacks = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hdc, Blacks);
		Ellipse(hdc, 358, 176, 398, 216);

		//����
		MoveToEx(hdc, 348, 211, NULL);
		LineTo(hdc, 318, 196);

		MoveToEx(hdc, 408, 211, NULL);
		LineTo(hdc, 438, 196);

		MoveToEx(hdc, 348, 221, NULL);
		LineTo(hdc, 318, 236);

		MoveToEx(hdc, 408, 221, NULL);
		LineTo(hdc, 438, 236);
		// ����� �귯�� ���ҽ��� �����մϴ�.
		DeleteObject(skinBrush);
		DeleteObject(mouthBrush);
		DeleteObject(Whites);
		DeleteObject(Blacks);

		/*// �߾Ӽ� ���߿� �����
		MoveToEx(hdc, 376, 0, NULL);
		LineTo(hdc, 376, 480);
		MoveToEx(hdc, 0, 188, NULL);
		LineTo(hdc, 800, 188);*/

		EndPaint(drawingView, &ps);
	}
}

void DrawRyan(HWND drawingView, HDC hdc, int left, int top, int right, int bottom) {
	{ // ���̾��� ��ġ�� ���� ������� ��������
		int startPointX = left;
		int startPointY = top;
		int endPointX = right;
		int endPointY = bottom;
		//���� ���۰� ���� �����ͼ� �����.
		POINT MINPOINT = { 0 };
		POINT MAXPOINT = { 0 };

		// �� ��ġ ����
		MINPOINT.x = min(startPointX, endPointX);
		MINPOINT.y = min(startPointY, endPointY);
		MAXPOINT.x = max(startPointX, endPointX);
		MAXPOINT.y = max(startPointY, endPointY);

		RECT face = { MINPOINT.x, MINPOINT.y,MAXPOINT.x,MAXPOINT.y };

		int width = abs(MINPOINT.x - MAXPOINT.x);
		int height = abs(MINPOINT.y - MAXPOINT.y);
		int centerX = width / 2;
		int centerY = height / 2;
		POINT centerPoint = { MINPOINT.x + centerX, MINPOINT.y + centerY };

		// �Ǻλ�
		HBRUSH RskinBrush = CreateSolidBrush(RGB(255, 200, 15));
		SelectObject(hdc, RskinBrush);

		// �ͺκ� �»󿡼� ����
		RECT L_ear = { MINPOINT.x , MINPOINT.y, MINPOINT.x + width / 3, MINPOINT.y + height / 3 };
		RECT R_ear = { MAXPOINT.x , MINPOINT.y, MAXPOINT.x - width / 3, MINPOINT.y + height / 3 };

		// �ޱ�
		Ellipse(hdc, L_ear.left, L_ear.top, L_ear.right, L_ear.bottom);
		// ������
		Ellipse(hdc, R_ear.left, R_ear.top, R_ear.right, R_ear.bottom);
		// ��
		Ellipse(hdc, face.left, face.top, face.right, face.bottom);

		POINT L_eye = { MINPOINT.x + centerX / 2, MINPOINT.y + (centerY / 6 * 5) };
		POINT R_eye = { MAXPOINT.x - centerX / 2, MINPOINT.y + (centerY / 6 * 5) };
		RECT L_eyes = { L_eye.x, L_eye.y, L_eye.x + width / 20, L_eye.y + height / 20 };
		RECT R_eyes = { R_eye.x, R_eye.y, R_eye.x - width / 20, R_eye.y + height / 20 };

		// ��
		HBRUSH Blacks = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hdc, Blacks);
		Ellipse(hdc, L_eyes.left, L_eyes.top, L_eyes.right, L_eyes.bottom);
		Ellipse(hdc, R_eyes.left, R_eyes.top, R_eyes.right, R_eyes.bottom);

		// ����3����
		MoveToEx(hdc, MINPOINT.x + centerX / 4, MINPOINT.y + centerY / 3 * 2, NULL);
		LineTo(hdc, MINPOINT.x + (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2));
		MoveToEx(hdc, MINPOINT.x + centerX / 4, MINPOINT.y + centerY / 3 * 2 + 2, NULL);
		LineTo(hdc, MINPOINT.x + (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2) + 2);
		MoveToEx(hdc, MINPOINT.x + centerX / 4, MINPOINT.y + centerY / 3 * 2 + 4, NULL);
		LineTo(hdc, MINPOINT.x + (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2) + 4);

		MoveToEx(hdc, MAXPOINT.x - centerX / 4, MINPOINT.y + centerY / 3 * 2, NULL);
		LineTo(hdc, MAXPOINT.x - (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2));
		MoveToEx(hdc, MAXPOINT.x - centerX / 4, MINPOINT.y + centerY / 3 * 2 + 2, NULL);
		LineTo(hdc, MAXPOINT.x - (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2) + 2);
		MoveToEx(hdc, MAXPOINT.x - centerX / 4, MINPOINT.y + centerY / 3 * 2 + 4, NULL);
		LineTo(hdc, MAXPOINT.x - (centerX / 4 * 3), MINPOINT.y + (centerY / 3 * 2) + 4);

		// ��
		RECT L_nose = { centerPoint.x - centerX / 5, centerPoint.y, centerPoint.x, centerPoint.y + centerY / 5 };
		RECT R_nose = { centerPoint.x, centerPoint.y, centerPoint.x + centerX / 5, centerPoint.y + centerY / 5 };
		HBRUSH Whites = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hdc, Whites);
		Ellipse(hdc, L_nose.left, L_nose.top, L_nose.right, L_nose.bottom);
		Ellipse(hdc, R_nose.left, R_nose.top, R_nose.right, R_nose.bottom);

		DeleteObject(RskinBrush);
		DeleteObject(Whites);
		DeleteObject(Blacks);

	}
}

RECT MoveRactangle(HWND hWnd, HDC hdc, LPARAM lParam, RECT ractangles, POINT start) {

	int mouseX = LOWORD(lParam);
	int mouseY = HIWORD(lParam);

	// ���� ��ġ���� ���� ���콺 ��ġ���� �̵��� �Ÿ� ���
	int deltaX = mouseX - start.x;//���⼭�� start�� WM_RBUTTONDOWN���� ���� �Ѱ��� �༮ �� ��Ŭ���� ���۵�����
	int deltaY = mouseY - start.y;

	// �簢�� �̵�
	ractangles.left += deltaX;
	ractangles.top += deltaY;
	ractangles.right += deltaX;
	ractangles.bottom += deltaY;

	return ractangles;
}

RECT ScaleCircle(HWND hWnd, HDC hdc, LPARAM lParam, RECT Eclip, POINT start) {
	int mouseX = LOWORD(lParam);
	int mouseY = HIWORD(lParam);

	// ���� ��ġ���� ���� ���콺 ��ġ���� �̵��� �Ÿ� ���
	int deltaX = mouseX - start.x;
	int deltaY = mouseY - start.y;
	double scaleFactor = 1;
	if (deltaX > 0) {
		scaleFactor = 1.0 + static_cast<double>(deltaX) / 100.0;  // ���������� �̵��� ������ ũ�⸦ ������ŵ�ϴ�.
	}
	else if (deltaX < 0) {
		scaleFactor = 1.0 / (1.0 - static_cast<double>(deltaX) / 100.0);  // �������� �̵��� ������ ũ�⸦ ���ҽ�ŵ�ϴ�.
	}
	else {
		scaleFactor = 1.0;  // ���� �̵��� ���� ��� ũ��� ������ �ʽ��ϴ�.
	}
	int width = Eclip.right - Eclip.left;
	int height = Eclip.bottom - Eclip.top;
	int centerX = Eclip.left + width / 2;
	int centerY = Eclip.top + height / 2;

	width = static_cast<int>(width * scaleFactor);
	height = static_cast<int>(height * scaleFactor);

	Eclip.left = centerX - width / 2;
	Eclip.top = centerY - height / 2;
	Eclip.right = Eclip.left + width;
	Eclip.bottom = Eclip.top + height;
	return Eclip;
}