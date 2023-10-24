#include <math.h>
#include <windows.h>

// 버튼에서 L버튼이 클릭이 되어야 그려지는 변수
bool LbuttonPressed = false;
bool isMoving = false;
bool cubepressed = false;
// 색상버튼
int color = 0;
int Shape = 0;

// 그리는데 필요한 녀석들
POINT startPoint = { 0 };
POINT endPoint = { 0 };
RECT rectangle1 = { 0, 0, 0, 0 }; // 사각형 초기화
RECT Eclip = { 0, 0, 0, 0 }; // 원 초기화
RECT bono = { 200, 200, 600, 600 }; // 보노보노 초기화
RECT ryan = { 200, 200, 600, 600 }; // 라이언 초기화
HBRUSH hBrush;
HBRUSH hBrush_background = CreateSolidBrush(RGB(255, 240, 200));

HWND box; // 박스 뷰 핸들
HWND drawing; // 드로잉 뷰 핸들

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_GETMINMAXINFO: // 창 크기 정보
	{
		MINMAXINFO* minMaxInfo = (MINMAXINFO*)lParam;
		minMaxInfo->ptMinTrackSize.x = 800; // 최소 너비와 최대를 같게 하여 고정
		minMaxInfo->ptMinTrackSize.y = 480; // 최소 높이와 최대를 같게 하여 고정
		minMaxInfo->ptMaxTrackSize.x = 800; // 최대 너비
		minMaxInfo->ptMaxTrackSize.y = 480; // 최대 높이
		return 0;
	}
	return 0;

	case WM_CREATE: {
		// 박스 뷰 생성
		box = CreateWindow(L"EDIT", L"Hello, Child View", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE,
			8, 8, 792, 472, hWnd, (HMENU)101, NULL, NULL);

		// 드로잉 뷰 생성
		drawing = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
			16, 220, 300, 200, hWnd, (HMENU)102, NULL, NULL);

		// 버튼 생성
		CreateWindow(L"BUTTON", L"Draw", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			320, 10, 80, 30, hWnd, (HMENU)1, NULL, NULL);
		CreateWindow(L"BUTTON", L"Clear", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			320, 50, 80, 30, hWnd, (HMENU)2, NULL, NULL);
	}
				  break;

	case WM_COMMAND:
		if (LOWORD(wParam) == 1) {
			// Draw 버튼 클릭
			// 여기에서 그림을 그리는 작업을 수행합니다.
		}
		else if (LOWORD(wParam) == 2) {
			// Clear 버튼 클릭
			// 여기에서 그림을 지우는 작업을 수행합니다.
		}
		break;

	case WM_PAINT: {
		RECT rect;
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		FillRect(hdc, &rect, hBrush_background);

		HBRUSH hBrush = CreateSolidBrush(RGB(255, 100, 255));
		SelectObject(hdc, hBrush);

		if (Shape == 1) {
			FillRect(hdc, &rect, (HBRUSH)(hBrush_background));
			Rectangle(hdc, rectangle1.left, rectangle1.top, rectangle1.right, rectangle1.bottom);
		}
		if (Shape == 2) {
			FillRect(hdc, &rect, (HBRUSH)(hBrush_background));
			Ellipse(hdc, Eclip.left, Eclip.top, Eclip.right, Eclip.bottom);
		}

		for (int x = 10; x < 800; x += 10) {
			MoveToEx(hdc, x, 0, NULL);
			LineTo(hdc, x, 480);
		}

		for (int y = 10; y < 480; y += 10) {
			MoveToEx(hdc, 0, y, NULL);
			LineTo(hdc, 800, y);
		}

		DeleteObject(hBrush);
		EndPaint(hWnd, &ps);
	}
				 break;

	case WM_LBUTTONDOWN: {
		LbuttonPressed = true;
		if (Shape) {
			startPoint.x = LOWORD(lParam);
			startPoint.y = HIWORD(lParam);
		}
	}
					   break;

	case WM_LBUTTONUP: {
		LbuttonPressed = false;
		endPoint.x = LOWORD(lParam);
		endPoint.y = HIWORD(lParam);
	}
					 break;

	case WM_RBUTTONDOWN:
	{
		if (PtInRect(&rectangle1, { LOWORD(lParam), HIWORD(lParam) })) // 만약 상자내부에서 클릭하면
		{
			isMoving = true;
			startPoint.x = LOWORD(lParam);
			startPoint.y = HIWORD(lParam);
		}
	}
	return 0;

	case WM_MOUSEMOVE:
	{
		if (LbuttonPressed) {
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);
			if (Shape == 1 || Shape == 2)
			{
				// 사각형 크기 및 위치 설정
				rectangle1.left = min(startPoint.x, endPoint.x);
				rectangle1.top = min(startPoint.y, endPoint.y);
				rectangle1.right = max(startPoint.x, endPoint.x);
				rectangle1.bottom = max(startPoint.y, endPoint.y);
				// 사각형 크기 및 위치 설정
				Eclip.left = min(startPoint.x, endPoint.x);
				Eclip.top = min(startPoint.y, endPoint.y);
				Eclip.right = max(startPoint.x, endPoint.x);
				Eclip.bottom = max(startPoint.y, endPoint.y);
				// WM_PAINT 메시지를 유발하여 화면에 그립니다.
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
		if (isMoving)
		{
			int mouseX = LOWORD(lParam);
			int mouseY = HIWORD(lParam);

			// 이전 위치에서 현재 마우스 위치까지 이동한 거리 계산
			int deltaX = mouseX - startPoint.x;
			int deltaY = mouseY - startPoint.y;

			// 사각형 이동
			rectangle1.left += deltaX;
			rectangle1.top += deltaY;
			rectangle1.right += deltaX;
			rectangle1.bottom += deltaY;

			double scaleFactor;
			if (deltaX > 0)
				scaleFactor = pow(2.0, deltaX / 100.0);     // 오른쪽으로 이동할 때마다 크기를 2배씩 증가시킵니다.
			else if (deltaX < 0)
				scaleFactor = pow(0.5, abs(deltaX) / 100.0); // 왼쪽으로 이동할 때마다 크기를 절반으로 줄입니다.
			else
				scaleFactor = 1.0;                            // 가로 이동이 없을 경우 크기는 변하지 않습니다.

			// 비율에 따라 원의 좌표 업데이트
			Eclip.left -= static_cast<int>((Eclip.right - Eclip.left) * (scaleFactor - 1));
			Eclip.top -= static_cast<int>((Eclip.bottom - Eclip.top) * (scaleFactor - 1));
			Eclip.right += static_cast<int>((Eclip.right - Eclip.left) * scaleFactor);
			Eclip.bottom += static_cast<int>((Eclip.bottom - Eclip.top) * scaleFactor);

			// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
			InvalidateRect(hWnd, NULL, TRUE);
			startPoint.x = mouseX;
			startPoint.y = mouseY;
		}
	}
	return 0;
	case WM_RBUTTONUP:
	{
		if (isMoving)
		{
			isMoving = false;
		}
	}
	return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {

	HWND hWnd;
	// HWND hButton1, hButton2, hButton3, hButton4, hButton5;

	HBRUSH hBrush_background = CreateSolidBrush(RGB(255, 240, 200));
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(hBrush_background);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"ButtonWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);


	// 윈도우 핸들을 먼저 초기화
	hWnd = CreateWindow(
		L"ButtonWindowClass", L"곰돌이", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL, NULL, hInstance, NULL);

	// 초기화된 hWnd을 사용하여 DPI 설정을 고려한 화면 크기를 계산
	if (hWnd) {
		int dpi = GetDpiForWindow(hWnd); // 현재 윈도우의 DPI 설정을 가져옴
		float scale = static_cast<float>(dpi) / 96.0f; // 96 DPI에서 100% 크기로 설정

		// 클라이언트 영역 크기를 DPI에 맞게 조정
		int clientWidth = static_cast<int>(800 * scale);
		int clientHeight = static_cast<int>(480 * scale);

		// 클라이언트 영역 크기를 포함한 전체 윈도우 크기 계산
		RECT windowRect = { 0, 0, clientWidth, clientHeight };
		AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
	}


	if (!RegisterClassEx(&wcex)) {
		return 1;
	}

	if (!hWnd) {
		return FALSE;
	}

	// 윈도우 생성 코드

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
