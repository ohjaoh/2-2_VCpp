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
POINT ver[5];
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
			// ��������ư Ŭ��
			Shape = 5;
		}
		else if (LOWORD(wParam) == 6) {
			// ������ư Ŭ��
			Shape = 0;
			color = 1;
		}
		else if (LOWORD(wParam) == 7) {
			// �Ķ���ư Ŭ��
			Shape = 0;
			color = 2;
		}
		else if (LOWORD(wParam) == 8) {
			// �ʷϹ�ư Ŭ��
			Shape = 0;
			color = 3;
		}
		else if (LOWORD(wParam) == 9) {
			// �����ư Ŭ��
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

			// ��ư�� ���� ���� (�����)
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 0)); // �����
			FillRect(hdcButton, &buttonRect, hBrush);
			DeleteObject(hBrush);

			// ��ư�� �ؽ�Ʈ �׸���
			SetBkMode(hdcButton, TRANSPARENT);
			SetTextColor(hdcButton, RGB(0, 0, 0)); // �ؽ�Ʈ ���� (������)
			DrawText(hdcButton, L"��", -1, &buttonRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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



// ���α׷� ������
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
		L"BUTTON", L"�簢��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 20, 200, 50, hWnd, (HMENU)1, hInstance, NULL);

	hButton2 = CreateWindow(
		L"BUTTON", L"��", WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
		20, 90, 200, 50, hWnd, (HMENU)2, hInstance, NULL);

	hButton3 = CreateWindow(
		L"BUTTON", L"����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 160, 200, 50, hWnd, (HMENU)3, hInstance, NULL);

	hButton4 = CreateWindow(
		L"BUTTON", L"�ﰢ��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 230, 200, 50, hWnd, (HMENU)4, hInstance, NULL);

	hButton5 = CreateWindow(
		L"BUTTON", L"������", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 300, 200, 50, hWnd, (HMENU)5, hInstance, NULL);

	hButton6 = CreateWindow(
		L"BUTTON", L"����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 370, 100, 50, hWnd, (HMENU)6, hInstance, NULL);

	hButton7 = CreateWindow(
		L"BUTTON", L"�Ķ�", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 440, 100, 50, hWnd, (HMENU)7, hInstance, NULL);

	hButton8 = CreateWindow(
		L"BUTTON", L"�ʷ�", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		20, 510, 100, 50, hWnd, (HMENU)8, hInstance, NULL);

	hButton9 = CreateWindow(
		L"BUTTON", L"���", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
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