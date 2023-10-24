#include <math.h>
#include <windows.h>

// ��ư���� L��ư�� Ŭ���� �Ǿ�� �׷����� ����
bool LbuttonPressed = false;
// �����ư
int color = 0;
int Shape = 0;

// �׸��µ� �ʿ��� �༮��
POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT Point3 = { 0 };
POINT ver[3];
POINT five[5];
RECT rectangle = { 0,0,0,0 }; // �ʱ� �簢�� ��ġ �� ũ��
HBRUSH hBrush;

// ������ ���ν���
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_COMMAND:
		if (LOWORD(wParam) == 1) {
			// ù ��° ��ư Ŭ��
			Shape = 1;
		}
		else if (LOWORD(wParam) == 2) {
			// �� ��° ��ư Ŭ��
			Shape = 2;
		}
		else if (LOWORD(wParam) == 3) {
			// �� ��° ��ư Ŭ��
			Shape = 3;
		}
		else if (LOWORD(wParam) == 4) {
			// �� ��° ��ư Ŭ��
			Shape = 4;
		}
		else if (LOWORD(wParam) == 5) {
			// �� ��° ��ư Ŭ��
			Shape = 5;
		}
		else if (LOWORD(wParam) == 6) {
			// �ټ� ��° ��ư Ŭ��
			Shape = 0;
			color = 6;
		}
		else if (LOWORD(wParam) == 7) {
			// ���� ��° ��ư Ŭ��
			Shape = 0;
			color = 7;
		}
		break;

	case WM_PAINT: {

		RECT rect;
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		if (color == 6) {
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hBrush);
		}
		else if (color == 7) {
			HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
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
			Polygon(hdc, five, 5);
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
		Shape = 0;
	}break;
	case WM_MOUSEMOVE:
	{
		if (LbuttonPressed) {
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);
			if (Shape == 1 || Shape == 2)
			{
				// �簢�� ũ�� �� ��ġ ����
				rectangle.left = min(startPoint.x, endPoint.x);
				rectangle.top = min(startPoint.y, endPoint.y);
				rectangle.right = max(startPoint.x, endPoint.x);
				rectangle.bottom = max(startPoint.y, endPoint.y);
				// WM_PAINT �޽����� �����Ͽ� ȭ�鿡 �׸��ϴ�.
				InvalidateRect(hWnd, NULL, TRUE);
			}
			if (Shape == 3) {
				// WM_PAINT �޽����� �����Ͽ� ȭ�鿡 �׸��ϴ�.
				InvalidateRect(hWnd, NULL, TRUE);
			}
			if (Shape == 4) {
				Point3.x = (startPoint.x + endPoint.x) / 2;
				Point3.y = startPoint.y;
				ver[0] = { startPoint.x, endPoint.y };
				ver[1] = { Point3};
				ver[2] = { endPoint};
				/* �����ﰢ������
				Point3.x = startPoint.x;
				Point3.y = endPoint.y;
				ver[0] = { startPoint.x, startPoint.y };
				ver[1] = { Point3.x, Point3.y };
				ver[2] = { endPoint.x, endPoint.y }; */
				// WM_PAINT �޽����� �����Ͽ� ȭ�鿡 �׸��ϴ�.
				InvalidateRect(hWnd, NULL, TRUE);
			}
			if (Shape == 5) {
				// ������ �׸���
				int radius = abs(startPoint.x - endPoint.x);
				int centerX = (startPoint.x + endPoint.x) / 2;
				int centerY = (startPoint.y + endPoint.y) / 2;

				// 5���� ������ ��ǥ ���
				for (int i = 0; i < 5; i++) {
					double angle = 2 * 3.14159265358979323846 * i / 5;
					five[i].x = centerX + int(radius * cos(angle));
					five[i].y = centerY - int(radius * sin(angle));
					InvalidateRect(hWnd, NULL, TRUE);
				}
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
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {

	HWND hWnd;
	HWND hButton1, hButton2, hButton3, hButton4, hButton5, hButton6, hButton7;

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
		20, 120, 200, 60, hWnd, (HMENU)2, hInstance, NULL);

	hButton3 = CreateWindow(
		L"BUTTON", L"����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 220, 200, 60, hWnd, (HMENU)3, hInstance, NULL);

	hButton4 = CreateWindow(
		L"BUTTON", L"�ﰢ��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 320, 200, 60, hWnd, (HMENU)4, hInstance, NULL);

	hButton5 = CreateWindow(
		L"BUTTON", L"������", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 420, 200, 60, hWnd, (HMENU)5, hInstance, NULL);

	hButton6 = CreateWindow(
		L"BUTTON", L"����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 520, 200, 60, hWnd, (HMENU)6, hInstance, NULL);

	hButton7 = CreateWindow(
		L"BUTTON", L"�Ķ�", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 620, 200, 60, hWnd, (HMENU)7, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}