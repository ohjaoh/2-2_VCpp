#include <windows.h>
#include <fstream>
#define ID_SAVE_BUTTON 1001  // ��ư ID�� ����� ����
#define ID_LOAD_BUTTON 1002  // ��ư ID�� ����� ����

wchar_t  textBuffer[2048] = { 0 }; // �ؽ�Ʈ ���� ����
int textLength = 0; // ���� �ؽ�Ʈ�� ����
int y = 10;
char test = '\n';

HBRUSH hBrush_background = CreateSolidBrush(RGB(204, 255, 153)); // ���귯��
HBRUSH hBrush_background1 = CreateSolidBrush(RGB(255, 255, 255));// �� ��� �귯��

// ������ ���ν���
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CHAR:
		if (textLength < sizeof(textBuffer) - 1) { // ���� �����÷ο� ����
			if (wParam == VK_RETURN) {
				textBuffer[textLength] = '\n';
				textLength++;
			}
			else {
				textBuffer[textLength] = (char)wParam; // ���� �߰�
				textLength++;
			}
			textBuffer[textLength] = '\0'; // �� ���ڷ� ���ڿ� ����
			InvalidateRect(hWnd, NULL, TRUE); // ȭ�� ���� ��û
		}
		if (wParam == VK_TAB) {
			// �� ���ڸ� ���� 4���� ��ȯ (�Ǵ� ���ϴ� ���� ��������)
			for (int i = 0; i < 4; ++i) {
				if (textLength < sizeof(textBuffer) - 1) {
					textBuffer[textLength] = ' ';
					textLength++;
				}
			}
			textBuffer[textLength] = '\0'; // �� ���ڷ� ���ڿ� ����
			InvalidateRect(hWnd, NULL, TRUE); // ȭ�� ���� ��û
		}
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
		switch (LOWORD(wParam)) {
		case ID_SAVE_BUTTON: {  // "�����ϱ�" ��ư�� ID
			OPENFILENAME ofn;       // ���� ��ȭ ���� ����ü
			wchar_t szFileName[MAX_PATH] = L"";

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFilter = L"�ؽ�Ʈ ���� (*.txt)\0*.txt\0��� ���� (*.*)\0*.*\0";
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
			ofn.lpstrDefExt = L"txt";

			// "�����ϱ�" ��ȭ ���ڸ� ǥ��
			if (GetSaveFileName(&ofn)) {
				std::wofstream file(szFileName);
				if (file.is_open()) {
					file << textBuffer;
					file.close();
				}
			}
		}
						   break;
		case ID_LOAD_BUTTON: {  // "�ҷ�����" ��ư�� ID
			OPENFILENAME ofn;
			wchar_t szFileName[MAX_PATH] = L"";

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFilter = L"�ؽ�Ʈ ���� (*.txt)\0*.txt\0��� ���� (*.*)\0*.*\0";
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

			// ���� ���� ��ȭ ���� ǥ��
			if (GetOpenFileName(&ofn)) {
				std::wifstream file(szFileName);
				if (file.is_open()) {
					textLength = 0; // ���� �ʱ�ȭ
					while (file.peek() != WEOF) {
						textBuffer[textLength++] = file.get();
						if (textLength >= sizeof(textBuffer) - 1) break; // ���� �����÷ο� ����
					}
					textBuffer[textLength] = '\0'; // �� ���ڷ� ���ڿ� ����
					file.close();
					SetFocus(hWnd);// ��Ŀ���� �θ��� �ϰ� ���� �Է��ϸ� ���ȭ���� ������
					InvalidateRect(hWnd, NULL, TRUE); // ȭ�� ���� ��û
				}
			}
		}
						   break;
		}
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
		// �ؽ�Ʈ �ٹٲ��� ���� ������
		int lineHeight = 20; // ���� ����
		int x = 10, y = 10; // ���� ��ġ
		wchar_t* lineStart = textBuffer; // �� ���� ��ġ
		wchar_t* p = textBuffer; // ���� ó�� ���� ���� ��ġ

		while (*p) {
			if (*p == L'\n') {
				// ���� ���� ȭ�鿡 �׸�
				TextOut(hdc, x, y, lineStart, p - lineStart);
				// ���� ���� ���� ��ġ�� y ��ǥ ������Ʈ
				lineStart = p + 1;
				y += lineHeight;
			}
			p++;
		}
		// ������ ���� ȭ�鿡 �׸�
		TextOut(hdc, x, y, lineStart, p - lineStart);

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
		L"BUTTON", L"�ҷ�����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 10, 100, 60, hWnd, (HMENU)ID_LOAD_BUTTON, hInstance, NULL);

	hButton2 = CreateWindow(
		L"BUTTON", L"����", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		120, 10, 100, 60, hWnd, (HMENU)ID_SAVE_BUTTON, hInstance, NULL);


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