#include <windows.h>

wchar_t  textBuffer[1024] = { 0 }; // ���� ����
int textLength = 0; // ���� �ؽ�Ʈ�� ����

HBRUSH hBrush_background = CreateSolidBrush(RGB(204, 255, 153)); // ���귯��
HBRUSH hBrush_background1 = CreateSolidBrush(RGB(255, 255, 255));// �� ��� �귯��

// ������ ���ν���
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CHAR:
		if (textLength < sizeof(textBuffer) - 1) { // ���� �����÷ο� ����
			textBuffer[textLength] = (char)wParam; // ���� �߰�
			textLength++;
			textBuffer[textLength] = '\0'; // �� ���ڷ� ���ڿ� ����
			InvalidateRect(hWnd, NULL, TRUE); // ȭ�� ���� ��û
		}
		// �ڳ� �����쿡 �ؽ�Ʈ ������ �˸��� ���� ��û
		//SendMessage(WritingView, WM_USER_TEXT_UPDATE, (WPARAM)textBuffer, (LPARAM)textLength);

		break;

	case WM_GETMINMAXINFO: {
		RECT rect = { 0, 0, 700, 900 }; // ���ϴ� Ŭ���̾�Ʈ ������ ũ��
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

		MINMAXINFO* minmax = (MINMAXINFO*)lParam;
		minmax->ptMinTrackSize.x = rect.right - rect.left;
		minmax->ptMinTrackSize.y = rect.bottom - rect.top;
		minmax->ptMaxTrackSize.x = rect.right - rect.left;
		minmax->ptMaxTrackSize.y = rect.bottom - rect.top;
	}
						 return 0;
	case WM_COMMAND:
		break;
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		SelectObject(hdc, hBrush_background);

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

LRESULT CALLBACK WritingViewWndProc(HWND WritingView, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_PAINT: {
		RECT rect;
		GetClientRect(WritingView, &rect);
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(WritingView, &ps);
		FillRect(hdc, &rect, hBrush_background1);

		TextOut(hdc, 10, 10, textBuffer, textLength);

		EndPaint(WritingView, &ps);
		break;
	}
				 break;
	case WM_MOUSEMOVE:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(WritingView, &ps);
		POINT currentPoint = { 0 };

		currentPoint.x = LOWORD(lParam);
		currentPoint.y = HIWORD(lParam);

	}
	return 0;

	default:
		return CallWindowProc(DefWindowProc, WritingView, message, wParam, lParam);
	}
	return 0;
}

// ���α׷� ������
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {

	HWND hButton1, hButton2;

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
	RECT rect = { 0, 0, 700, 900 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// ������ ����
	HWND hWnd = CreateWindow(
		wcex.lpszClassName,
		TEXT("�޸���"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
		NULL, NULL,
		hInstance,
		NULL
	);

	WNDCLASSEX wcWriting;
	wcWriting.cbSize = sizeof(WNDCLASSEX);
	wcWriting.style = CS_HREDRAW | CS_VREDRAW;
	wcWriting.lpfnWndProc = WritingViewWndProc; // �ڽĺ��� �޽��� ó�� �Լ�
	wcWriting.cbClsExtra = 0;
	wcWriting.cbWndExtra = 0;
	wcWriting.hInstance = hInstance;
	wcWriting.hIcon = NULL;
	wcWriting.hCursor = LoadCursor(NULL, IDC_IBEAM); // ���콺 �����͸� ��������� ����
	wcWriting.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));
	wcWriting.lpszMenuName = NULL;
	wcWriting.lpszClassName = L"WritingViewClass";
	wcWriting.hIconSm = NULL;

	RegisterClassEx(&wcWriting);


	HWND WritingView = CreateWindow(
		L"WritingViewClass", L"", // Ŭ���� �̸��� â ����
		WS_CHILD | WS_VISIBLE,
		10, 80, 680, 810, // ��ġ�� ũ�� ����
		hWnd, NULL, // �θ� â�� �޴� �ڵ�
		hInstance, NULL
	);

	SetWindowLongPtr(WritingView, GWLP_USERDATA, (LONG_PTR)hWnd); // �θ� ������ �ڵ� ����
	SetWindowLongPtr(WritingView, GWLP_WNDPROC, (LONG_PTR)WritingViewWndProc); // Ŀ���� ������ ���ν��� ����

	if (!WritingView) {
		return -1;
	}

	if (!hWnd) {
		return FALSE;
	}

	hButton1 = CreateWindow(
		L"BUTTON", L"���ۼ�", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 10, 100, 60, hWnd, (HMENU)1, hInstance, NULL);

	hButton2 = CreateWindow(
		L"BUTTON", L"����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		120, 10, 100, 60, hWnd, (HMENU)2, hInstance, NULL);


	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// �޽��� ����
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) { // get���� �޽��� �����
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}