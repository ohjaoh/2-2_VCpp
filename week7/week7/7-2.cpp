#include <math.h>
#include <windows.h>

// 버튼에서 L버튼이 클릭이 되어야 그려지는 변수
bool LbuttonPressed = false;
// 색상버튼
int color = 0;
int Shape = 0;

// 그리는데 필요한 녀석들
POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT Point3 = { 0 };
POINT ver[5];
RECT rectangle = { 0,0,0,0 }; // 초기 사각형 위치 및 크기
HBRUSH hBrush;

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_COMMAND:
		if (LOWORD(wParam) == 1) {
			// 첫 번째 버튼 클릭
			Shape = 1;
		}
		else if (LOWORD(wParam) == 2) {
			// 두 번째 버튼 클릭
			Shape = 2;
		}
		else if (LOWORD(wParam) == 3) {
			// 세 번째 버튼 클릭
			Shape = 3;
		}
		else if (LOWORD(wParam) == 4) {
			// 네 번째 버튼 클릭
			Shape = 4;
		}
		else if (LOWORD(wParam) == 5) {
			// 오각형버튼 클릭
			Shape = 5;
		}
		else if (LOWORD(wParam) == 6) {
			// 빨강버튼 클릭
			Shape = 0;
			color = 1;
		}
		else if (LOWORD(wParam) == 7) {
			// 파랑버튼 클릭
			Shape = 0;
			color = 2;
		}
		else if (LOWORD(wParam) == 8) {
			// 초록버튼 클릭
			Shape = 0;
			color = 3;
		}
		else if (LOWORD(wParam) == 9) {
			// 노랑버튼 클릭
			Shape = 0;
			color = 4;
		}
		break;

	case WM_PAINT: {

		RECT rect;
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		if (color == 1) {
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hBrush);
		}
		else if (color == 2) {
			HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hBrush);
		}
		else if (color == 3) {
			HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hBrush);
		}
		else if (color == 4) {
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hBrush);
		}
		else {
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 100, 255));
			SelectObject(hdc, hBrush);

		}

		if (Shape == 1) {
			FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
			Rectangle(hdc, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);
		}
		if (Shape == 2) {
			FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
			Ellipse(hdc, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);
		}
		if (Shape == 3) {
			FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
			MoveToEx(hdc, startPoint.x, startPoint.y, NULL);
			LineTo(hdc, endPoint.x, endPoint.y);
		}
		if (Shape == 4) {
			FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
			Polygon(hdc, ver, 3);
		}
		if (Shape == 5) {
			FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
			Polygon(hdc, ver, 5);
		}

		DeleteObject(hBrush);
		EndPaint(hWnd, &ps);
		break;
	}
	break;
	case WM_LBUTTONDOWN: {
		LbuttonPressed = true;
		if (Shape) {
			startPoint.x = LOWORD(lParam);
			startPoint.y = HIWORD(lParam);
		}
	}break;
	case WM_LBUTTONUP: {
		LbuttonPressed = false;
		endPoint.x = LOWORD(lParam);
		endPoint.y = HIWORD(lParam);
	}break;
	case WM_MOUSEMOVE:
	{
		if (LbuttonPressed) {
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);
			if (Shape == 1 || Shape == 2)
			{
				// 사각형 크기 및 위치 설정
				rectangle.left = min(startPoint.x, endPoint.x);
				rectangle.top = min(startPoint.y, endPoint.y);
				rectangle.right = max(startPoint.x, endPoint.x);
				rectangle.bottom = max(startPoint.y, endPoint.y);
				// WM_PAINT 메시지를 유발하여 화면에 그립니다.
				InvalidateRect(hWnd, NULL, TRUE);
			}
			if (Shape == 3) {
				// WM_PAINT 메시지를 유발하여 화면에 그립니다.
				InvalidateRect(hWnd, NULL, TRUE);
			}
			if (Shape == 4) {
				Point3.x = (startPoint.x + endPoint.x) / 2;
				Point3.y = startPoint.y;
				ver[0] = { startPoint.x, endPoint.y };
				ver[1] = { Point3};
				ver[2] = { endPoint};
				/* 직각삼각형버전
				Point3.x = startPoint.x;
				Point3.y = endPoint.y;
				ver[0] = { startPoint.x, startPoint.y };
				ver[1] = { Point3.x, Point3.y };
				ver[2] = { endPoint.x, endPoint.y }; */
				// WM_PAINT 메시지를 유발하여 화면에 그립니다.
				InvalidateRect(hWnd, NULL, TRUE);
			}
			if (Shape == 5) {
				// 오각형 그리기
				int radius = abs(startPoint.x - endPoint.x);
				int centerX = (startPoint.x + endPoint.x) / 2;
				int centerY = (startPoint.y + endPoint.y) / 2;

				// 5개의 꼭지점 좌표 계산
				for (int i = 0; i < 5; i++) {
					double angle = 2 * 3.14159265358979323846 * i / 5;
					ver[i].x = centerX + int(radius * cos(angle));
					ver[i].y = centerY - int(radius * sin(angle));
					InvalidateRect(hWnd, NULL, TRUE);
				}
			}
		}
	}
	return 0;

	case WM_DRAWITEM:
	{
		DRAWITEMSTRUCT* pDIS = (DRAWITEMSTRUCT*)lParam;
		if (pDIS->CtlType == ODT_BUTTON) {
			HDC hdcButton = pDIS->hDC;
			RECT buttonRect = pDIS->rcItem;

			// 버튼의 배경색 설정 (노란색)
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 0)); // 노란색
			FillRect(hdcButton, &buttonRect, hBrush);
			DeleteObject(hBrush);

			// 버튼에 텍스트 그리기
			SetBkMode(hdcButton, TRANSPARENT);
			SetTextColor(hdcButton, RGB(0, 0, 0)); // 텍스트 색상 (검은색)
			DrawText(hdcButton, L"원", -1, &buttonRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
	break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



// 프로그램 진입점
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {

	HWND hWnd;
	HWND hButton1, hButton2, hButton3, hButton4, hButton5, hButton6, hButton7, hButton8, hButton9;

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"ButtonWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex)) {
		return 1;
	}

	hWnd = CreateWindow(
		L"ButtonWindowClass", L"Win32 Button Example", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd) {
		return FALSE;
	}

	hButton1 = CreateWindow(
		L"BUTTON", L"사각형", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 20, 200, 50, hWnd, (HMENU)1, hInstance, NULL);

	hButton2 = CreateWindow(
		L"BUTTON", L"원", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		20, 90, 200, 50, hWnd, (HMENU)2, hInstance, NULL);

	hButton3 = CreateWindow(
		L"BUTTON", L"직선", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 160, 200, 50, hWnd, (HMENU)3, hInstance, NULL);

	hButton4 = CreateWindow(
		L"BUTTON", L"삼각형", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 230, 200, 50, hWnd, (HMENU)4, hInstance, NULL);

	hButton5 = CreateWindow(
		L"BUTTON", L"오각형", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 300, 200, 50, hWnd, (HMENU)5, hInstance, NULL);

	hButton6 = CreateWindow(
		L"BUTTON", L"빨강", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 370, 100, 50, hWnd, (HMENU)6, hInstance, NULL);

	hButton7 = CreateWindow(
		L"BUTTON", L"파랑", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 440, 100, 50, hWnd, (HMENU)7, hInstance, NULL);

	hButton8 = CreateWindow(
		L"BUTTON", L"초록", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 510, 100, 50, hWnd, (HMENU)8, hInstance, NULL);

	hButton9 = CreateWindow(
		L"BUTTON", L"노랑", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		150, 370, 100, 50, hWnd, (HMENU)9, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}