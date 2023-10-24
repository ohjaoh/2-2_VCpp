#include <math.h>
#include <windows.h>

// ��ư���� L��ư�� Ŭ���� �Ǿ�� �׷����� ����
bool LbuttonPressed = false;
bool isMoving = false;
bool cubepressed = false;
// �����ư
int color = 0;
int Shape = 0;

// �׸��µ� �ʿ��� �༮��
POINT startPoint = { 0 };
POINT endPoint = { 0 };
RECT rectangle1 = { 0, 0, 0, 0 }; // �簢�� �ʱ�ȭ
RECT Eclip = { 0, 0, 0, 0 }; // �� �ʱ�ȭ
RECT bono = { 200, 200, 600, 600 }; // ���뺸�� �ʱ�ȭ
RECT ryan = { 200, 200, 600, 600 }; // ���̾� �ʱ�ȭ
HBRUSH hBrush;
HBRUSH hBrush_background = CreateSolidBrush(RGB(255, 240, 200));

HWND box; // �ڽ� �� �ڵ�
HWND drawing; // ����� �� �ڵ�

// ������ ���ν���
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_GETMINMAXINFO: // â ũ�� ����
	{
		MINMAXINFO* minMaxInfo = (MINMAXINFO*)lParam;
		minMaxInfo->ptMinTrackSize.x = 800; // �ּ� �ʺ�� �ִ븦 ���� �Ͽ� ����
		minMaxInfo->ptMinTrackSize.y = 480; // �ּ� ���̿� �ִ븦 ���� �Ͽ� ����
		minMaxInfo->ptMaxTrackSize.x = 800; // �ִ� �ʺ�
		minMaxInfo->ptMaxTrackSize.y = 480; // �ִ� ����
		return 0;
	}
	return 0;

	case WM_CREATE: {
		// �ڽ� �� ����
		box = CreateWindow(L"EDIT", L"Hello, Child View", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE,
			8, 8, 792, 472, hWnd, (HMENU)101, NULL, NULL);

		// ����� �� ����
		drawing = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
			16, 220, 300, 200, hWnd, (HMENU)102, NULL, NULL);

		// ��ư ����
		CreateWindow(L"BUTTON", L"Draw", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			320, 10, 80, 30, hWnd, (HMENU)1, NULL, NULL);
		CreateWindow(L"BUTTON", L"Clear", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			320, 50, 80, 30, hWnd, (HMENU)2, NULL, NULL);
	}
				  break;

	case WM_COMMAND:
		if (LOWORD(wParam) == 1) {
			// Draw ��ư Ŭ��
			// ���⿡�� �׸��� �׸��� �۾��� �����մϴ�.
		}
		else if (LOWORD(wParam) == 2) {
			// Clear ��ư Ŭ��
			// ���⿡�� �׸��� ����� �۾��� �����մϴ�.
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
		if (PtInRect(&rectangle1, { LOWORD(lParam), HIWORD(lParam) })) // ���� ���ڳ��ο��� Ŭ���ϸ�
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
				// �簢�� ũ�� �� ��ġ ����
				rectangle1.left = min(startPoint.x, endPoint.x);
				rectangle1.top = min(startPoint.y, endPoint.y);
				rectangle1.right = max(startPoint.x, endPoint.x);
				rectangle1.bottom = max(startPoint.y, endPoint.y);
				// �簢�� ũ�� �� ��ġ ����
				Eclip.left = min(startPoint.x, endPoint.x);
				Eclip.top = min(startPoint.y, endPoint.y);
				Eclip.right = max(startPoint.x, endPoint.x);
				Eclip.bottom = max(startPoint.y, endPoint.y);
				// WM_PAINT �޽����� �����Ͽ� ȭ�鿡 �׸��ϴ�.
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
		if (isMoving)
		{
			int mouseX = LOWORD(lParam);
			int mouseY = HIWORD(lParam);

			// ���� ��ġ���� ���� ���콺 ��ġ���� �̵��� �Ÿ� ���
			int deltaX = mouseX - startPoint.x;
			int deltaY = mouseY - startPoint.y;

			// �簢�� �̵�
			rectangle1.left += deltaX;
			rectangle1.top += deltaY;
			rectangle1.right += deltaX;
			rectangle1.bottom += deltaY;

			double scaleFactor;
			if (deltaX > 0)
				scaleFactor = pow(2.0, deltaX / 100.0);     // ���������� �̵��� ������ ũ�⸦ 2�辿 ������ŵ�ϴ�.
			else if (deltaX < 0)
				scaleFactor = pow(0.5, abs(deltaX) / 100.0); // �������� �̵��� ������ ũ�⸦ �������� ���Դϴ�.
			else
				scaleFactor = 1.0;                            // ���� �̵��� ���� ��� ũ��� ������ �ʽ��ϴ�.

			// ������ ���� ���� ��ǥ ������Ʈ
			Eclip.left -= static_cast<int>((Eclip.right - Eclip.left) * (scaleFactor - 1));
			Eclip.top -= static_cast<int>((Eclip.bottom - Eclip.top) * (scaleFactor - 1));
			Eclip.right += static_cast<int>((Eclip.right - Eclip.left) * scaleFactor);
			Eclip.bottom += static_cast<int>((Eclip.bottom - Eclip.top) * scaleFactor);

			// WM_PAINT �޽����� �����Ͽ� �׸� ȭ�鿡 �׸��ϴ�.
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


	// ������ �ڵ��� ���� �ʱ�ȭ
	hWnd = CreateWindow(
		L"ButtonWindowClass", L"������", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL, NULL, hInstance, NULL);

	// �ʱ�ȭ�� hWnd�� ����Ͽ� DPI ������ ����� ȭ�� ũ�⸦ ���
	if (hWnd) {
		int dpi = GetDpiForWindow(hWnd); // ���� �������� DPI ������ ������
		float scale = static_cast<float>(dpi) / 96.0f; // 96 DPI���� 100% ũ��� ����

		// Ŭ���̾�Ʈ ���� ũ�⸦ DPI�� �°� ����
		int clientWidth = static_cast<int>(800 * scale);
		int clientHeight = static_cast<int>(480 * scale);

		// Ŭ���̾�Ʈ ���� ũ�⸦ ������ ��ü ������ ũ�� ���
		RECT windowRect = { 0, 0, clientWidth, clientHeight };
		AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
	}


	if (!RegisterClassEx(&wcex)) {
		return 1;
	}

	if (!hWnd) {
		return FALSE;
	}

	// ������ ���� �ڵ�

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
