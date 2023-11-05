#include <windows.h>

// ��ư���� L��ư�� Ŭ���� �Ǿ�� �׷����� ����
bool LbuttonPressed = false;
bool isMoving = false;
bool cubepressed = false;
bool spacepressed = false;
bool Bonobono = false;
bool Ryan = false;
int Shape = 0;


// �׸��µ� �ʿ��� �༮��
POINT startPoint = { 0 };
POINT endPoint = { 0 };
RECT rectangle1 = { 0,0,0,0 }; // �簢�� �ʱ�ȭ
RECT Eclip = { 0,0,0,0 }; // �� �ʱ�ȭ
RECT Box = { 8, 8, 792, 472 }; // �׵θ�
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
			Ryan = false;
			Shape = 1;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == 2) {
			Eclip = { 0,0,0,0 };
			// �� ��° ��ư Ŭ��
			Bonobono = false;
			Ryan = false;
			Shape = 2;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == 3) {
			// �� ��° ��ư Ŭ��
			Bonobono = true;
			Ryan = false;
			Shape = 3;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == 4) {
			// �� ��° ��ư Ŭ��
			Bonobono = false;
			Ryan = true;
			Shape = 4;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == 5) {
			Bonobono = false;
			Ryan = false;
			Shape = 5;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_PAINT: {

		RECT rect;
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

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


LRESULT CALLBACK drawingViewWndProc(HWND drawingView, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_KEYDOWN:
		if (wParam == VK_SPACE)
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(drawingView, &ps);
			HBRUSH bonobono = CreateSolidBrush(RGB(127, 200, 255));
			SelectObject(hdc, bonobono);
			if (spacepressed = false) {
				spacepressed = true;
			}
			else {
				spacepressed = false;
			}

		}
		break;
	case WM_PAINT: {
		RECT rect;
		GetClientRect(drawingView, &rect);
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(drawingView, &ps);
		FillRect(hdc, &rect, hBrush_background1);


		if (Shape == 1) {
			FillRect(hdc, &rect, (HBRUSH)(hBrush_background1));
			Rectangle(hdc, rectangle1.left, rectangle1.top, rectangle1.right, rectangle1.bottom);
		}
		if (Shape == 2) {
			FillRect(hdc, &rect, (HBRUSH)(hBrush_background1));
			Ellipse(hdc, Eclip.left, Eclip.top, Eclip.right, Eclip.bottom);
		}

		if (Bonobono && spacepressed == false) {// ���뺸�� ����
			// �Ǻλ�
			HBRUSH skinBrush = CreateSolidBrush(RGB(127, 200, 255));
			SelectObject(hdc, skinBrush);
			// �׸��� ���� �Ǻ� �κ��� �׸��ϴ�.
			Ellipse(hdc, 205, 37, 535, 367);

			// �� ��
			HBRUSH mouthBrush = CreateSolidBrush(RGB(255, 150, 255));
			SelectObject(hdc, mouthBrush);
			Ellipse(hdc, 350, 195, 390, 320);

			// �� �� �κ�
			HBRUSH Whites = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, Whites);
			Ellipse(hdc, 320, 210, 370, 250);
			Ellipse(hdc, 370, 210, 420, 250);

			// �� �κ� (�� ���� Ư���� ������� �ʾ����Ƿ� �⺻ �������� ����մϴ�.)
			HBRUSH Blacks = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, Blacks);
			Ellipse(hdc, 250, 170, 260, 190);
			Ellipse(hdc, 490, 170, 480, 190);

			// ���� �� �κ�
			Ellipse(hdc, 350, 190, 390, 230);

			// �� ������
			SelectObject(hdc, Whites);
			Ellipse(hdc, 252, 175, 258, 180);
			Ellipse(hdc, 482, 175, 488, 180);

			//����
			MoveToEx(hdc, 340, 225, NULL);
			LineTo(hdc, 310, 210);

			MoveToEx(hdc, 400, 225, NULL);
			LineTo(hdc, 430, 210);

			MoveToEx(hdc, 340, 235, NULL);
			LineTo(hdc, 310, 250);

			MoveToEx(hdc, 400, 235, NULL);
			LineTo(hdc, 430, 250);
			// ����� �귯�� ���ҽ��� �����մϴ�.
			DeleteObject(skinBrush);
			DeleteObject(mouthBrush);

			EndPaint(drawingView, &ps);
		}
		else if (Bonobono && spacepressed == true) {// ���뺸�� ������
			// �Ǻλ�
			HBRUSH skinBrush = CreateSolidBrush(RGB(127, 200, 255));
			SelectObject(hdc, skinBrush);
			// �׸��� ���� �Ǻ� �κ��� �׸��ϴ�.
			Ellipse(hdc, 205, 37, 535, 367);


			// �� ��
			HBRUSH mouthBrush = CreateSolidBrush(RGB(255, 150, 255));
			SelectObject(hdc, mouthBrush);
			Ellipse(hdc, 350, 195, 390, 320);

			// �� �� �κ�
			HBRUSH Whites = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, Whites);
			Ellipse(hdc, 320, 210, 370, 250);
			Ellipse(hdc, 370, 210, 420, 250);

			// �� �κ� 
			//�޴�
			MoveToEx(hdc, 250, 170, NULL);
			LineTo(hdc, 220, 210);
			//������
			MoveToEx(hdc, 490, 170, NULL);
			LineTo(hdc, 510, 210);

			// ���� �� �κ�
			Ellipse(hdc, 350, 190, 390, 230);

			// �� ������
			SelectObject(hdc, Whites);
			Ellipse(hdc, 252, 175, 258, 180);
			Ellipse(hdc, 482, 175, 488, 180);

			//����
			MoveToEx(hdc, 340, 225, NULL);
			LineTo(hdc, 310, 210);

			MoveToEx(hdc, 400, 225, NULL);
			LineTo(hdc, 430, 210);

			MoveToEx(hdc, 340, 235, NULL);
			LineTo(hdc, 310, 250);

			MoveToEx(hdc, 400, 235, NULL);
			LineTo(hdc, 430, 250);
			// ����� �귯�� ���ҽ��� �����մϴ�.
			DeleteObject(skinBrush);
			DeleteObject(mouthBrush);

			EndPaint(drawingView, &ps);
		}

		if (Ryan) {
			// �Ǻλ�
			HBRUSH RskinBrush = CreateSolidBrush(RGB(255, 200, 15));
			SelectObject(hdc, RskinBrush);

			// �ͺκ�
			// �ޱ�
			Ellipse(hdc, 185, 15, 300, 135);
			// ������
			Ellipse(hdc, 440, 15, 555, 135);
			// ��
			Ellipse(hdc, 205, 37, 535, 367);

			// ��
			HBRUSH Blacks = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, Blacks);
			Ellipse(hdc, 290, 150, 310, 170);
			Ellipse(hdc, 457, 150, 437, 170);

			// ����3����
			MoveToEx(hdc, 270, 130, NULL);
			LineTo(hdc, 335, 130);
			MoveToEx(hdc, 270, 132, NULL);
			LineTo(hdc, 335, 132);
			MoveToEx(hdc, 270, 134, NULL);
			LineTo(hdc, 335, 134);


			MoveToEx(hdc, 412, 130, NULL);
			LineTo(hdc, 477, 130);
			MoveToEx(hdc, 412, 132, NULL);
			LineTo(hdc, 477, 132);
			MoveToEx(hdc, 412, 134, NULL);
			LineTo(hdc, 477, 134);


			// ��
			HBRUSH Whites = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, Whites);
			Ellipse(hdc, 376, 198, 416, 238);
			Ellipse(hdc, 336, 198, 376, 238);


			/*
			// �߾Ӽ� ���߿� �����
			MoveToEx(hdc, 376, 0, NULL);
			LineTo(hdc, 376, 480);
			MoveToEx(hdc, 0, 184, NULL);
			LineTo(hdc, 800, 184);*/
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
				// ���� ũ�� �� ��ġ ����
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

			double scaleFactor = 1;
			if (deltaX > 0) {
				scaleFactor = 1.0 + static_cast<double>(deltaX) / 100.0;  // ���������� �̵��� ������ ũ�⸦ ������ŵ�ϴ�.
			}
			else if (deltaX < 0) {
				scaleFactor = 1.0 / (1.0 - static_cast<double>(deltaX) / 100.0);  // �������� �̵��� ������ ũ�⸦ ���ҽ�ŵ�ϴ�.
			}
			else {
				scaleFactor = 1.0;  // ���� �̵��� ���� ��� ũ��� ������ �ʽ��ϴ�.
			}
			int width = Eclip.right - Eclip.left;
			int height = Eclip.bottom - Eclip.top;
			int centerX = Eclip.left + width / 2;
			int centerY = Eclip.top + height / 2;

			width = static_cast<int>(width * scaleFactor);
			height = static_cast<int>(height * scaleFactor);

			Eclip.left = centerX - width / 2;
			Eclip.top = centerY - height / 2;
			Eclip.right = Eclip.left + width;
			Eclip.bottom = Eclip.top + height;
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

	WNDCLASSEX wcexDrawing;
	wcexDrawing.cbSize = sizeof(WNDCLASSEX);
	wcexDrawing.style = CS_HREDRAW | CS_VREDRAW;
	wcexDrawing.lpfnWndProc = drawingViewWndProc; // ����� ���� �޽��� ó�� �Լ�
	wcexDrawing.cbClsExtra = 0;
	wcexDrawing.cbWndExtra = 0;
	wcexDrawing.hInstance = hInstance;
	wcexDrawing.hIcon = NULL;
	wcexDrawing.hCursor = LoadCursor(NULL, IDC_CROSS); // ���콺 �����͸� ���ڰ��� ����
	wcexDrawing.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));
	wcexDrawing.lpszMenuName = NULL;
	wcexDrawing.lpszClassName = L"DrawingViewClass";
	wcexDrawing.hIconSm = NULL;

	RegisterClassEx(&wcexDrawing);

	HWND drawingView = CreateWindow(
		L"DrawingViewClass", L"", // Ŭ���� �̸��� â ����
		WS_CHILD | WS_VISIBLE,
		16, 98, 768, 368, // ��ġ�� ũ��
		hWnd, NULL, // �θ� â�� �޴� �ڵ�
		hInstance, NULL
	);

	SetWindowLongPtr(drawingView, GWLP_USERDATA, (LONG_PTR)hWnd); // �θ� ������ �ڵ� ����
	SetWindowLongPtr(drawingView, GWLP_WNDPROC, (LONG_PTR)drawingViewWndProc); // Ŀ���� ������ ���ν��� ����


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