#include <Windows.h>

HRGN Drawcube(HWND hWnd, HDC hdc, POINT startPoint, POINT endPoint) {
	// 중앙선 나중에 지울것
	MoveToEx(hdc, 376, 0, NULL);
	LineTo(hdc, 376, 480);
	MoveToEx(hdc, 0, 188, NULL);
	LineTo(hdc, 800, 188);

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

void Movecube(POINT* MINPOINT, POINT* MAXPOINT,int deltaX, int deltaY) {
	MINPOINT->x += deltaX; // MINPOINT의 X 좌표 이동
	MINPOINT->y += deltaY; // MINPOINT의 Y 좌표 이동
	MAXPOINT->x += deltaX; // MAXPOINT의 X 좌표 이동
	MAXPOINT->y += deltaY; // MAXPOINT의 Y 좌표 이동
}

void Scalecube(POINT* minPoint, POINT* maxPoint, int deltaX, int deltaY) {
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
	int width = maxPoint->x - minPoint->x;
	int height = maxPoint->y - minPoint->y;
	int centerX = minPoint->x + width / 2;
	int centerY = minPoint->y + height / 2;

	width = static_cast<int>(width * scaleFactor);
	height = static_cast<int>(height * scaleFactor);

	minPoint->x = centerX - width / 2;
	minPoint->y = centerY - height / 2;
	maxPoint->x = minPoint->x + width;
	maxPoint->y = minPoint->y + height;
}