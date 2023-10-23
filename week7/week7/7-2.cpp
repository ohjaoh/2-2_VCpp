#include <windows.h>


// �ڽ��� ��Ÿ���� ����
bool Ractang = false;
// ��
bool eclipse = false;
// ����
bool Linang = false;
// �ﰢ��
bool trang = false;
// ��ư���� L��ư�� Ŭ���� �Ǿ�� �׷����� ����
bool LbuttonPressed = false;


// �׸��µ� �ʿ��� �༮��
POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT Point3 = { 0 };
POINT ver[3];
RECT rectangle = { 0,0,0,0 }; // �ʱ� �簢�� ��ġ �� ũ��

// ������ ���ν���
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_COMMAND:
		if (LOWORD(wParam) == 1) {
			// ù ��° ��ư Ŭ��
			Ractang = true;
			eclipse = false;
			Linang = false;
			trang = false;
		}
		else if (LOWORD(wParam) == 2) {
			// �� ��° ��ư Ŭ��
			Ractang = false;
			eclipse = true;
			Linang = false;
			trang = false;
		}
		else if (LOWORD(wParam) == 3) {
			// �� ��° ��ư Ŭ��
			Ractang = false;
			eclipse = false;
			Linang = true;
			trang = false;
		}
		else if (LOWORD(wParam) == 4) {
			// �� ��° ��ư Ŭ��
			Ractang = false;
			eclipse = false;
			Linang = false;
			trang = true;
		}
		break;

	case WM_PAINT: {
		RECT rect;
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 100, 255)); // ������ �ڽ�

		if (Ractang) {
			FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
			SelectObject(hdc, hBrush);
			Rectangle(hdc, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);
			DeleteObject(hBrush);
		}
		if (eclipse) {
			FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
			SelectObject(hdc, hBrush);
			Ellipse(hdc, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);
			DeleteObject(hBrush);
		}
		if (Linang) {
			FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
			MoveToEx(hdc, startPoint.x, startPoint.y, NULL);
			LineTo(hdc, endPoint.x, endPoint.y);
		}
		if (trang) {
			FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
			SelectObject(hdc, hBrush);
			Polygon(hdc, ver, 3);
			DeleteObject(hBrush);
		}

		EndPaint(hWnd, &ps);
		break;
	}
				 break;
	case WM_LBUTTONDOWN: {
		LbuttonPressed = true;
		if (Ractang == true || eclipse == true || Linang == true || trang == true) {
			startPoint.x = LOWORD(lParam);
			startPoint.y = HIWORD(lParam);
		}
	}break;
	case WM_LBUTTONUP: {
		LbuttonPressed = false;
		endPoint.x = LOWORD(lParam);
		endPoint.y = HIWORD(lParam);
		Ractang = false;
		eclipse = false;
		Linang = false;
		trang = false;
	}break;
	case WM_MOUSEMOVE:
	{
		if (LbuttonPressed) {
		endPoint.x = LOWORD(lParam);
		endPoint.y = HIWORD(lParam);
			if (Ractang || eclipse)
			{
				// �簢�� ũ�� �� ��ġ ����
				rectangle.left = min(startPoint.x, endPoint.x);
				rectangle.top = min(startPoint.y, endPoint.y);
				rectangle.right = max(startPoint.x, endPoint.x);
				rectangle.bottom = max(startPoint.y, endPoint.y);
				// WM_PAINT �޽����� �����Ͽ� �׸� ȭ�鿡 �׸��ϴ�.
				InvalidateRect(hWnd, NULL, TRUE);
			}
			if (Linang) {
				InvalidateRect(hWnd, NULL, TRUE);
			}
			if (trang) {
				Point3.x = (startPoint.x + endPoint.x) / 2;
				Point3.y = startPoint.y;
				ver[0] = { startPoint.x, endPoint.y };
				ver[1] = { Point3.x, Point3.y };
				ver[2] = { endPoint.x, endPoint.y };
				/* �����ﰢ������
				Point3.x = startPoint.x;
				Point3.y = endPoint.y;
				ver[0] = { startPoint.x, startPoint.y };
				ver[1] = { Point3.x, Point3.y };
				ver[2] = { endPoint.x, endPoint.y }; */
				InvalidateRect(hWnd, NULL, TRUE);
			}
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



// ���α׷� ������
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	HWND hWnd;
	HWND hButton1, hButton2, hButton3, hButton4;

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
		L"BUTTON", L"�簢��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 20, 200, 60, hWnd, (HMENU)1, hInstance, NULL);

	hButton2 = CreateWindow(
		L"BUTTON", L"��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 150, 200, 60, hWnd, (HMENU)2, hInstance, NULL);

	hButton3 = CreateWindow(
		L"BUTTON", L"����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 300, 200, 60, hWnd, (HMENU)3, hInstance, NULL);

	hButton4 = CreateWindow(
		L"BUTTON", L"�ﰢ��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 450, 200, 60, hWnd, (HMENU)4, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}