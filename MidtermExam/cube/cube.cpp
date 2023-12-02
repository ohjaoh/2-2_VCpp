#include <Windows.h>
#include <cmath>
HRGN Drawcube(HWND hWnd, HDC hdc, POINT startPoint, POINT endPoint) {
	// 중앙선 나중에 지울것
	/*
	MoveToEx(hdc, 376, 0, NULL);
	LineTo(hdc, 376, 480);
	MoveToEx(hdc, 0, 188, NULL);
	LineTo(hdc, 800, 188);
	*/

	int width = abs(startPoint.x - endPoint.x);
	int height = abs(startPoint.y - endPoint.y);
	int centerX = width / 2;
	int centerY = height / 2;

	POINT MINPOINT = { 0 };
	POINT MAXPOINT = { 0 };

	MINPOINT.x = min(startPoint.x, endPoint.x);
	MINPOINT.y = min(startPoint.y, endPoint.y);
	MAXPOINT.x = max(startPoint.x, endPoint.x);
	MAXPOINT.y = max(startPoint.y, endPoint.y);

	POINT centerPoint = { MINPOINT.x + centerX, MINPOINT.y + centerY };

	if (MINPOINT.x <= 376 && MINPOINT.y < 188) {//좌상
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

		POINT hexaPoints[6] = {
		   {MINPOINT.x, MAXPOINT.y}, // 1번 꼭짓점
		   {MAXPOINT.x - centerX / 2, MAXPOINT.y}, // 2번 꼭짓점
		   {MAXPOINT.x, MAXPOINT.y - centerY / 2}, // 3번 꼭짓점
		   {MAXPOINT.x, MINPOINT.y}, // 4번 꼭짓점
		   {MINPOINT.x + centerX / 2, MINPOINT.y}, // 5번 꼭짓점
		   {MINPOINT.x, MINPOINT.y + centerY / 2}  // 6번 꼭짓점
		};
		HRGN Hexa = CreatePolygonRgn(hexaPoints, 6, WINDING);
		return Hexa;
	}
	if (MINPOINT.x <= 376 && MINPOINT.y >= 188) {//좌하
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

		POINT hexaPoints[6] = {
		   {MINPOINT.x, MINPOINT.y}, // 1번 꼭짓점
		   {MINPOINT.x, MAXPOINT.y - centerY / 2}, // 2번 꼭짓점
		   {MINPOINT.x + centerX / 2, MAXPOINT.y}, // 3번 꼭짓점
		   {MAXPOINT.x, MAXPOINT.y}, // 4번 꼭짓점
		   {MAXPOINT.x, MINPOINT.y + centerY / 2}, // 5번 꼭짓점
		   {MAXPOINT.x - centerX / 2, MINPOINT.y}  // 6번 꼭짓점
		};
		HRGN Hexa = CreatePolygonRgn(hexaPoints, 6, WINDING);
		return Hexa;
	}
	if (MINPOINT.x > 376 && MINPOINT.y < 188) {//우상
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

		POINT hexaPoints[6] = {
		   {MINPOINT.x, MINPOINT.y}, // 1번 꼭짓점
		   {MINPOINT.x, MAXPOINT.y - centerY / 2}, // 2번 꼭짓점
		   {MINPOINT.x + centerX / 2, MAXPOINT.y}, // 3번 꼭짓점
		   {MAXPOINT.x, MAXPOINT.y}, // 4번 꼭짓점
		   {MAXPOINT.x, MINPOINT.y + centerY / 2}, // 5번 꼭짓점
		   {MAXPOINT.x - centerX / 2, MINPOINT.y}  // 6번 꼭짓점
		};
		HRGN Hexa = CreatePolygonRgn(hexaPoints, 6, WINDING);
		return Hexa;
	}
	if (MINPOINT.x > 376 && MINPOINT.y >= 188) {//우하
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

		POINT hexaPoints[6] = {
		   {MINPOINT.x + centerX / 2, MINPOINT.y}, // 1번 꼭짓점
		   {MINPOINT.x, MINPOINT.y + centerY / 2}, // 2번 꼭짓점
		   {MINPOINT.x, MAXPOINT.y}, // 3번 꼭짓점
		   {MAXPOINT.x - centerX / 2, MAXPOINT.y}, // 4번 꼭짓점
		   {MAXPOINT.x, MAXPOINT.y - centerY / 2}, // 5번 꼭짓점
		   {MAXPOINT.x, MINPOINT.y}  // 6번 꼭짓점
		};
		HRGN Hexa = CreatePolygonRgn(hexaPoints, 6, WINDING);
		return Hexa;
	}
}

void Movecube(POINT* MINPOINT, POINT* MAXPOINT, int deltaX, int deltaY) {
	MINPOINT->x += deltaX; // MINPOINT의 X 좌표 이동
	MINPOINT->y += deltaY; // MINPOINT의 Y 좌표 이동
	MAXPOINT->x += deltaX; // MAXPOINT의 X 좌표 이동
	MAXPOINT->y += deltaY; // MAXPOINT의 Y 좌표 이동
}

void ScaleCube(LPARAM lParam, POINT* minPoint, POINT* maxPoint, POINT standard) {
	int mouseX = LOWORD(lParam);
	int mouseY = HIWORD(lParam);

	// 이전 위치에서 현재 마우스 위치까지 이동한 거리 계산
	int deltaX = mouseX - standard.x;

	double scaleFactor = 1.0;
	if (deltaX > 0) {
		scaleFactor = 1.0 + static_cast<double>(deltaX) / 100.0;
	}
	else if (deltaX < 0) {
		scaleFactor = 1.0 / (1.0 - static_cast<double>(deltaX) / 100.0);
	}

	// 중심점을 double 타입으로 계산
	double centerX = minPoint->x + (maxPoint->x - minPoint->x) / 2.0;
	double centerY = minPoint->y + (maxPoint->y - minPoint->y) / 2.0;

	// 새로운 너비와 높이를 double 타입으로 계산
	double newWidth = (maxPoint->x - minPoint->x) * scaleFactor;
	double newHeight = (maxPoint->y - minPoint->y) * scaleFactor;

	// 새로운 위치를 계산하여 minPoint와 maxPoint를 업데이트
	// 사용자 정의 반올림 함수로 정수 좌표를 계산
	minPoint->x = static_cast<int>(std::round(centerX - newWidth / 2.0)); 
	minPoint->y = static_cast<int>(std::round(centerY - newHeight / 2.0));
	maxPoint->x = static_cast<int>(std::round(minPoint->x + newWidth));
	maxPoint->y = static_cast<int>(std::round(minPoint->y + newHeight));
}