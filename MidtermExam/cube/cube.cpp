#include <Windows.h>
struct CubeState
{
	POINT go = {0};
	POINT to = { 0 };
};

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

	CubeState cubestatus; //이동하는 거랑 논리상 꼬여있음 오늘은 여기까지 내일부터 수정

	cubestatus.go = MINPOINT;
	cubestatus.to = MAXPOINT;

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
		HRGN Hexa = CreatePolygonRgn(hexaPoints, 6,WINDING);
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
void Movecube(HWND hWnd, HDC hdc, LPARAM lParam, POINT start) {

	int mouseX = LOWORD(lParam);
	int mouseY = HIWORD(lParam);
	POINT end = { mouseX, mouseY };

	// 이전 위치에서 현재 마우스 위치까지 이동한 거리 계산
	int deltaX = mouseX - start.x;
	int deltaY = mouseY - start.y;

	CubeState cubestatus;
	POINT MINPOINT = { cubestatus.go };
	POINT MAXPOINT = { cubestatus.to };

	MINPOINT.x += deltaX;
	MINPOINT.y += deltaY;
	MAXPOINT.x += deltaX;
	MAXPOINT.y += deltaY;

	Drawcube(hWnd, hdc, MINPOINT, MAXPOINT);
}
void Scalecube(HWND hWnd, HDC hdc, LPARAM lParam, POINT start) {
	int mouseX = LOWORD(lParam);
	int mouseY = HIWORD(lParam);
	POINT end = { mouseX, mouseY };

	// 이전 위치에서 현재 마우스 위치까지 이동한 거리 계산
	int deltaX = mouseX - start.x;
	int deltaY = mouseY - start.y;

	POINT MINPOINT = { 0 };
	POINT MAXPOINT = { 0 };

	MINPOINT.x = min(start.x, end.x);
	MINPOINT.y = min(start.y, end.y);
	MAXPOINT.x = max(start.x, end.x);
	MAXPOINT.y = max(start.y, end.y);
	MINPOINT.x += deltaX;
	MINPOINT.y += deltaY;
	MAXPOINT.x += deltaX;
	MAXPOINT.y += deltaY;

	Drawcube(hWnd, hdc, MINPOINT, MAXPOINT);

}