#include <windows.h>


// 박스를 나타내는 변수
bool Ractang = false;
// 삼각형
bool Trang = false;
// 직선
bool Linang = false;

// 그리는데 필요한 녀석들
POINT startPoint = { 0 };
POINT endPoint = { 0 };
RECT rectangle = { 0,0,0,0 }; // 초기 사각형 위치 및 크기

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_COMMAND:
		if (LOWORD(wParam) == 1) {
			// 첫 번째 버튼 클릭
			Ractang = true;
			Trang = false;
			Linang = false;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == 2) {
			// 두 번째 버튼 클릭
			Ractang = false;
			Trang = true;
			Linang = false;
			
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == 3) {
			// 세 번째 버튼 클릭
			Ractang = false;
			Trang = false;
			Linang = true;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // 빨간색 박스

		SelectObject(hdc, hBrush);
		Rectangle(hdc, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);
		DeleteObject(hBrush);

		EndPaint(hWnd, &ps);
		break;
	}
	break;
	case WM_LBUTTONDOWN: {
		startPoint.x = LOWORD(lParam);
		startPoint.y = HIWORD(lParam);
	}break;
	case WM_MOUSEMOVE:
	{
		if (Ractang)
		{
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);

			// 사각형 크기 및 위치 설정
			rectangle.left = min(startPoint.x, endPoint.x);
			rectangle.top = min(startPoint.y, endPoint.y);
			rectangle.right = max(startPoint.x, endPoint.x);
			rectangle.bottom = max(startPoint.y, endPoint.y);

			// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
			InvalidateRect(hWnd, NULL, TRUE);
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



// 프로그램 진입점
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	HWND hWnd;
	HWND hButton1, hButton2, hButton3;

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
		20, 20, 200, 60, hWnd, (HMENU)1, hInstance, NULL);

	hButton2 = CreateWindow(
		L"BUTTON", L"삼각형", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 200, 200, 60, hWnd, (HMENU)2, hInstance, NULL);

	hButton3 = CreateWindow(
		L"BUTTON", L"직선", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 400, 200, 60, hWnd, (HMENU)2, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}