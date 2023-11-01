#include <math.h>
#include <windows.h>

// ��ư���� L��ư�� Ŭ���� �Ǿ�� �׷����� ����
bool LbuttonPressed = false;
bool isMoving = false;
bool cubepressed = false;
bool Bonobono = false;
// �����ư
int color = 0;
int Shape = 0;

// �׸��µ� �ʿ��� �༮��
POINT startPoint = { 0 };
POINT endPoint = { 0 };
RECT rectangle1 = { 0,0,0,0 }; // �簢�� �ʱ�ȭ
RECT Eclip = { 0,0,0,0 }; // �� �ʱ�ȭ
RECT bono = { 200, 200, 600, 600 }; // ���뺸�� �ʱ�ȭ
RECT ryan = { 200, 200, 600, 600 }; // ���̾� �ʱ�ȭ
RECT Box = { 8, 8, 792, 472 }; // �׵θ�
RECT drawingArea = { 16, 72, 784, 464 };
HBRUSH hBrush_background = CreateSolidBrush(RGB(255, 240, 200));
HBRUSH hBrush_background1 = CreateSolidBrush(RGB(255, 255, 255));

// ������ ���ν���
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_GETMINMAXINFO: {
		RECT rect = { 0, 0, 800, 480 }; // ���ϴ� Ŭ���̾�Ʈ ������ ũ��
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

		MINMAXINFO* mmi = (MINMAXINFO*)lParam;
		mmi->ptMinTrackSize.x = rect.right - rect.left;
		mmi->ptMinTrackSize.y = rect.bottom - rect.top;
		mmi->ptMaxTrackSize.x = rect.right - rect.left;
		mmi->ptMaxTrackSize.y = rect.bottom - rect.top; }
		return 0;

	case WM_COMMAND:
		if (LOWORD(wParam) == 1) {
			rectangle1 = { 0,0,0,0 };
			// ù ��° ��ư Ŭ��
			Bonobono = false;
			Shape = 1;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == 2) {
			Eclip = { 0,0,0,0 };
			// �� ��° ��ư Ŭ��
			Bonobono = false;
			Shape = 2;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == 3) {
			// �� ��° ��ư Ŭ��
			Bonobono = true;
			Shape = 3;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == 4) {
			// �� ��° ��ư Ŭ��
			Bonobono = false;
			Shape = 4;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == 5) {
			Bonobono = false;
			Shape = 5;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_PAINT: {

		RECT rect;
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		FillRect(hdc, &rect, hBrush_background);


		SelectObject(hdc, hBrush_background);
		Rectangle(hdc, Box.left, Box.top, Box.right, Box.bottom);

		EndPaint(hWnd, &ps);
		break;
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


LRESULT CALLBACK CustomDrawingProc(HWND drawingView, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_KEYDOWN:
		if (wParam == VK_SPACE)
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(drawingView, &ps);
			HBRUSH bonobono = CreateSolidBrush(RGB(127, 200, 255));
			SelectObject(hdc, bonobono);
		}
		break;
	case WM_PAINT: {

		RECT rect;
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(drawingView, &ps);
		FillRect(hdc, &rect, hBrush_background1);



		if (Shape == 1) {
			FillRect(hdc, &rect, (HBRUSH)(hBrush_background));
			Rectangle(hdc, rectangle1.left, rectangle1.top, rectangle1.right, rectangle1.bottom);
		}
		if (Shape == 2) {
			FillRect(hdc, &rect, (HBRUSH)(hBrush_background));
			Ellipse(hdc, Eclip.left, Eclip.top, Eclip.right, Eclip.bottom);
		}

		if (Bonobono) {// ���뺸��
					// �Ǻλ�
			HBRUSH skinBrush = CreateSolidBrush(RGB(127, 200, 255));
			SelectObject(hdc, skinBrush);
			// �׸��� ���� �Ǻ� �κ��� �׸��ϴ�.
			Ellipse(hdc, 235, 67, 565, 397);

			// �� ��
			HBRUSH mouthBrush = CreateSolidBrush(RGB(255, 150, 255));
			SelectObject(hdc, mouthBrush);
			Ellipse(hdc, 380, 225, 420, 350);

			// �� �� �κ�
			HBRUSH Whites = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, Whites);
			Ellipse(hdc, 350, 240, 400, 280);
			Ellipse(hdc, 400, 240, 450, 280);

			// �� �κ� (�� ���� Ư���� ������� �ʾ����Ƿ� �⺻ �������� ����մϴ�.)
			HBRUSH Blacks = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, Blacks);
			Ellipse(hdc, 280, 200, 290, 220);
			Ellipse(hdc, 520, 200, 510, 220);

			// ���� �� �κ�
			Ellipse(hdc, 380, 220, 420, 260);

			// �� ������
			SelectObject(hdc, Whites);
			Ellipse(hdc, 282, 205, 288, 210);
			Ellipse(hdc, 512, 205, 518, 210);

			//����
			MoveToEx(hdc, 370, 255, NULL);
			LineTo(hdc, 340, 240);

			MoveToEx(hdc, 430, 255, NULL);
			LineTo(hdc, 460, 240);

			MoveToEx(hdc, 370, 265, NULL);
			LineTo(hdc, 340, 280);

			MoveToEx(hdc, 430, 265, NULL);
			LineTo(hdc, 460, 280);
			// ����� �귯�� ���ҽ��� �����մϴ�.
			DeleteObject(skinBrush);
			DeleteObject(mouthBrush);

			EndPaint(drawingView, &ps);
		}

		EndPaint(drawingView, &ps);
		break;
	}
				 break;
	case WM_LBUTTONDOWN: {
		LbuttonPressed = true;
		if (Shape == 1 || Shape == 2) {
			startPoint.x = LOWORD(lParam);
			startPoint.y = HIWORD(lParam);
		}
	}break;
	case WM_LBUTTONUP: {
		LbuttonPressed = false;
		endPoint.x = LOWORD(lParam);
		endPoint.y = HIWORD(lParam);
	}break;

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
				InvalidateRect(drawingView, NULL, TRUE);
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
			InvalidateRect(drawingView, NULL, TRUE);
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

	default:
		return CallWindowProc(DefWindowProc, drawingView, message, wParam, lParam);
	}
	return 0;
}

// ���α׷� ������
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {

	HWND hButton1, hButton2, hButton3, hButton4, hButton5;

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



	if (!RegisterClassEx(&wcex)) {
		exit(-1);
	}
	
	// Window viewport ���� ����
	RECT rect = { 0, 0, 800, 480 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// ������ ����
	HWND hWnd = CreateWindow(
		wcex.lpszClassName,
		TEXT("������"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
		NULL, NULL,
		hInstance,
		NULL
	);

	HWND drawingView = CreateWindow(
		L"STATIC", L"",
		WS_CHILD | WS_VISIBLE | SS_NOTIFY, // SS_NOTIFY ��Ÿ���� �߰�
		16, 98, 784, 464,
		hWnd, NULL, // �θ� �������� �ڵ�
		hInstance, NULL
	);

	SetWindowLongPtr(drawingView, GWLP_USERDATA, (LONG_PTR)hWnd); // �θ� ������ �ڵ� ����
	SetWindowLongPtr(drawingView, GWLP_WNDPROC, (LONG_PTR)CustomDrawingProc); // Ŀ���� ������ ���ν��� ����


	if (!drawingView) {
		return -1;
	}

	if (!hWnd) {
		return FALSE;
	}

	hButton1 = CreateWindow(
		L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		16, 16, 140, 64, hWnd, (HMENU)1, hInstance, NULL);

	hButton2 = CreateWindow(
		L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		172, 16, 140, 64, hWnd, (HMENU)2, hInstance, NULL);

	hButton3 = CreateWindow(
		L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		328, 16, 140, 64, hWnd, (HMENU)3, hInstance, NULL);

	hButton4 = CreateWindow(
		L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		484, 16, 140, 64, hWnd, (HMENU)4, hInstance, NULL);

	hButton5 = CreateWindow(
		L"BUTTON", L"ť��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		640, 16, 140, 64, hWnd, (HMENU)5, hInstance, NULL);


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}