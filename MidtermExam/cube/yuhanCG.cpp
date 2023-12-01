#include "yuhanCG.h"
#include <Windows.h>
void DrawBonobono(HWND drawingView, HDC hdc, int blink) {
	if (blink == 0) {// 보노보노 눈떠
		PAINTSTRUCT ps;
		// 피부색
		HBRUSH skinBrush = CreateSolidBrush(RGB(127, 200, 255));
		SelectObject(hdc, skinBrush);
		// 그림의 원형 피부 부분을 그립니다.
		Ellipse(hdc, 212, 23, 543, 363);//x+2 y-14

		// 입 색
		HBRUSH mouthBrush = CreateSolidBrush(RGB(255, 150, 255));
		SelectObject(hdc, mouthBrush);
		Ellipse(hdc, 357, 181, 397, 306);

		// 흰 코 부분
		HBRUSH Whites = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hdc, Whites);
		Ellipse(hdc, 328, 196, 378, 236); 
		Ellipse(hdc, 378, 196, 426, 236);

		// 눈 부분 (눈 색을 특별히 명시하지 않았으므로 기본 검은색을 사용합니다.)
		HBRUSH Blacks = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hdc, Blacks);
		Ellipse(hdc, 258, 156, 268, 176);
		Ellipse(hdc, 498, 156, 488, 176);

		// 검은 코 부분
		Ellipse(hdc, 358, 176, 398, 216);

		// 흰 눈동자
		SelectObject(hdc, Whites);
		Ellipse(hdc, 260, 161, 268, 166);
		Ellipse(hdc, 490, 161, 498, 166);
		//수염
		MoveToEx(hdc, 348, 211, NULL);
		LineTo(hdc, 318, 196);

		MoveToEx(hdc, 408, 211, NULL);
		LineTo(hdc, 438, 196);
		
		MoveToEx(hdc, 348, 221, NULL);
		LineTo(hdc, 318, 236);

		MoveToEx(hdc, 408, 221, NULL);
		LineTo(hdc, 438, 236);
		// 사용한 브러시 리소스를 해제합니다.
		DeleteObject(skinBrush);
		DeleteObject(mouthBrush);
		DeleteObject(Whites);
		DeleteObject(Blacks);
		//x + 2 y - 14
		/*// 중앙선 나중에 지울것
		MoveToEx(hdc, 376, 0, NULL);
		LineTo(hdc, 376, 480);
		MoveToEx(hdc, 0, 188, NULL);
		LineTo(hdc, 800, 188);*/


		EndPaint(drawingView, &ps);
	}
	else if (blink == 1) {// 보노보노 눈감아
		PAINTSTRUCT ps;
		// 피부색
		HBRUSH skinBrush = CreateSolidBrush(RGB(127, 200, 255));
		SelectObject(hdc, skinBrush);
		// 그림의 원형 피부 부분을 그립니다.
		Ellipse(hdc, 212, 23, 543, 363);
		// 입 색
		HBRUSH mouthBrush = CreateSolidBrush(RGB(255, 150, 255));
		SelectObject(hdc, mouthBrush);
		Ellipse(hdc, 357, 181, 397, 306);

		// 흰 코 부분
		HBRUSH Whites = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(hdc, Whites);
		Ellipse(hdc, 328, 196, 378, 236);
		Ellipse(hdc, 378, 196, 426, 236);

		// 눈 부분
		//왼눈
		MoveToEx(hdc, 263, 161, NULL);
		LineTo(hdc, 248, 151);
		MoveToEx(hdc, 263, 161, NULL);
		LineTo(hdc, 248, 171);
		//오른눈
		MoveToEx(hdc, 493, 161, NULL);
		LineTo(hdc, 508, 151);
		MoveToEx(hdc, 493, 161, NULL);
		LineTo(hdc, 508, 171);

		// 검은 코 부분//x+2 y-14
		HBRUSH Blacks = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hdc, Blacks);
		Ellipse(hdc, 358, 176, 398, 216);

		//수염
		MoveToEx(hdc, 348, 211, NULL);
		LineTo(hdc, 318, 196);

		MoveToEx(hdc, 408, 211, NULL);
		LineTo(hdc, 438, 196);

		MoveToEx(hdc, 348, 221, NULL);
		LineTo(hdc, 318, 236);

		MoveToEx(hdc, 408, 221, NULL);
		LineTo(hdc, 438, 236);
		// 사용한 브러시 리소스를 해제합니다.
		DeleteObject(skinBrush);
		DeleteObject(mouthBrush);
		DeleteObject(Whites);
		DeleteObject(Blacks);

		/*// 중앙선 나중에 지울것
		MoveToEx(hdc, 376, 0, NULL);
		LineTo(hdc, 376, 480);
		MoveToEx(hdc, 0, 188, NULL);
		LineTo(hdc, 800, 188);*/

		EndPaint(drawingView, &ps);
	}
}

void DrawRyan(HWND drawingView, HDC hdc, int left, int top, int right, int bottom) {
	{ // 라이언은 위치를 전부 계산으로 만들어야함
		int startPointX = left;
		int startPointY = top;
		int endPointX = right;
		int endPointY = bottom;
		//얼굴은 시작과 끝을 가져와서 만든다.
		POINT MINPOINT = { 0 };
		POINT MAXPOINT = { 0 };

		// 얼굴 위치 설정
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

		// 피부색
		HBRUSH RskinBrush = CreateSolidBrush(RGB(255, 200, 15));
		SelectObject(hdc, RskinBrush);

		// 귀부분 좌상에서 정상
		RECT L_ear = { MINPOINT.x , MINPOINT.y, MINPOINT.x + width / 3, MINPOINT.y + height / 3 };
		RECT R_ear = { MAXPOINT.x , MINPOINT.y, MAXPOINT.x - width / 3, MINPOINT.y + height / 3 };

		// 왼귀
		Ellipse(hdc, L_ear.left, L_ear.top, L_ear.right, L_ear.bottom);
		// 오른귀
		Ellipse(hdc, R_ear.left, R_ear.top, R_ear.right, R_ear.bottom);
		// 얼굴
		Ellipse(hdc, face.left, face.top, face.right, face.bottom);

		POINT L_eye = { MINPOINT.x + centerX / 2, MINPOINT.y + (centerY / 6 * 5) };
		POINT R_eye = { MAXPOINT.x - centerX / 2, MINPOINT.y + (centerY / 6 * 5) };
		RECT L_eyes = { L_eye.x, L_eye.y, L_eye.x + width / 20, L_eye.y + height / 20 };
		RECT R_eyes = { R_eye.x, R_eye.y, R_eye.x - width / 20, R_eye.y + height / 20 };

		// 눈
		HBRUSH Blacks = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hdc, Blacks);
		Ellipse(hdc, L_eyes.left, L_eyes.top, L_eyes.right, L_eyes.bottom);
		Ellipse(hdc, R_eyes.left, R_eyes.top, R_eyes.right, R_eyes.bottom);

		// 눈썹3가닥
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

		// 코
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

	// 이전 위치에서 현재 마우스 위치까지 이동한 거리 계산
	int deltaX = mouseX - start.x;//여기서의 start는 WM_RBUTTONDOWN에서 값을 넘겨준 녀석 즉 우클릭이 시작된지점
	int deltaY = mouseY - start.y;

	// 사각형 이동
	ractangles.left += deltaX;
	ractangles.top += deltaY;
	ractangles.right += deltaX;
	ractangles.bottom += deltaY;

	return ractangles;
}

RECT ScaleCircle(HWND hWnd, HDC hdc, LPARAM lParam, RECT Eclip, POINT start) {
	int mouseX = LOWORD(lParam);
	int mouseY = HIWORD(lParam);

	// 이전 위치에서 현재 마우스 위치까지 이동한 거리 계산
	int deltaX = mouseX - start.x;
	int deltaY = mouseY - start.y;
	double scaleFactor = 1;
	if (deltaX > 0) {
		scaleFactor = 1.0 + static_cast<double>(deltaX) / 100.0;  // 오른쪽으로 이동할 때마다 크기를 증가시킵니다.
	}
	else if (deltaX < 0) {
		scaleFactor = 1.0 / (1.0 - static_cast<double>(deltaX) / 100.0);  // 왼쪽으로 이동할 때마다 크기를 감소시킵니다.
	}
	else {
		scaleFactor = 1.0;  // 가로 이동이 없을 경우 크기는 변하지 않습니다.
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