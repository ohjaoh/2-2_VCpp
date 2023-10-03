#ifdef _DEBUG_
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif

#include <windows.h>

int startPointx = 0;
int startPointy = 0;
int endPointx = 0;
int endPointy = 0;
int dragPointx = 0;
int dragPointy = 0;
int dragStartPointx = 0;
int dragStartPointy = 0;
int lenx = 0;
int leny = 0;
int tempx = 0, tempy = 0, tempxx = 0, tempyy = 0;
int isMouseLButtonPressed = 0;
int isMouseRButtonPressed = 0;

// �������� �̺�Ʈ�� ó���ϴ� �ݹ�(Callback) �Լ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_GETMINMAXINFO: // â ũ�� ����
	{
		MINMAXINFO* minMaxInfo = (MINMAXINFO*)lParam;
		minMaxInfo->ptMinTrackSize.x = 800; // �ּ� �ʺ�
		minMaxInfo->ptMinTrackSize.y = 600; // �ּ� ����
		minMaxInfo->ptMaxTrackSize.x = 800; // �ִ� �ʺ�
		minMaxInfo->ptMaxTrackSize.y = 600; // �ִ� ����
		return 0;
	}
	break;

	case WM_PAINT:
	{
		RECT rectangle = { startPointx, startPointy, endPointx, endPointy };
		HDC hdc = GetDC(hwnd);
		if (isMouseLButtonPressed)
		{
			RECT rect;
			GetClientRect(hwnd, &rect);
			FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1)); // ȭ�������
			MoveToEx(hdc, startPointx, startPointy, NULL);

			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
			SelectObject(hdc, hBrush);
			tempx = rectangle.left;
			tempy = rectangle.top;
			tempxx = rectangle.right;
			tempyy = rectangle.bottom;
			Rectangle(hdc, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);
			DeleteObject(hBrush);
		}
		ReleaseDC(hwnd, hdc);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		startPointx = LOWORD(lParam);
		startPointy = HIWORD(lParam);
		isMouseLButtonPressed = 1;
	}
	break;

	case WM_RBUTTONDOWN:
	{

		dragStartPointx = LOWORD(lParam);
		dragStartPointy = HIWORD(lParam);

		isMouseRButtonPressed = 1;

	}
	break;

	case WM_MOUSEMOVE:
	{
		// ��Ŭ�����콺 �̵� ��
		if (isMouseLButtonPressed)
		{
			endPointx = LOWORD(lParam);
			endPointy = HIWORD(lParam);


			// WM_PAINT �޽����� �����Ͽ� �׸� ȭ�鿡 �׸��ϴ�.
			InvalidateRect(hwnd, NULL, TRUE);
		}


		// ��Ŭ�����콺 �̵� ��
		if (isMouseRButtonPressed)
		{
			dragPointx = LOWORD(lParam);
			dragPointy = HIWORD(lParam);
			lenx = dragPointx - dragStartPointx;
			leny = dragPointy - dragStartPointy;

			tempx = dragStartPointx + lenx;
			tempy = dragStartPointy + leny;
			tempxx = endPointx + lenx;
			tempyy = endPointy + leny;


			// WM_PAINT �޽����� �����Ͽ� �׸� ȭ�鿡 �׸��ϴ�.
			InvalidateRect(hwnd, NULL, TRUE);
			dragStartPointx = dragPointx;
			dragStartPointy = dragPointy;

		}
	}
	break;

	case WM_LBUTTONUP:
	{

		endPointx = LOWORD(lParam);
		endPointy = HIWORD(lParam);

		isMouseLButtonPressed = 0;

		// WM_PAINT �޽����� �����Ͽ� �׸� ȭ�鿡 �׸��ϴ�.
		InvalidateRect(hwnd, NULL, TRUE);
	}
	break;

	case WM_RBUTTONUP:
	{
		isMouseRButtonPressed = 0;

		// WM_PAINT �޽����� �����Ͽ� �׸� ȭ�鿡 �׸��ϴ�.
		InvalidateRect(hwnd, NULL, TRUE);
	}
	break;


	case WM_DESTROY:
		PostQuitMessage(0);
		exit(-1);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}


	return S_OK;
}
#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
	/* ������ Ŭ���� ����.*/
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// ��� 0���� �ʱ�ȭ.

	// ������ Ŭ���� �� ����
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// ������ Ŭ���� ���.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//����
	}

	// Window viewport ���� ����
	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// ������ ����
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("201907022 ������"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
		NULL, NULL,
		hInstance,
		NULL
	);

	// ���� �˻�.
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// â ���̱�.
	ShowWindow(hwnd, SW_SHOW); // â ����
	UpdateWindow(hwnd); // ������Ʈ�ؾ� ����. �� ������ ���ٰ� ���� ��.



	// �޽��� ó�� ����.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		// �޽��� ó��.
		if (GetMessage(&msg, hwnd, 0, 0))
			//if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) // PM_REMOVE�� �ڸ��� �� �޼����� ���� ��Ұų�.�� �ǹ��ε� ����ٴ� ����.
		{

			// �޽��� �ؼ�����.
			TranslateMessage(&msg);
			// �޽����� ó���ؾ��� ���� ��������.
			DispatchMessage(&msg);

		}
		/*else
		{

		}*/
	}

	//���� �޽��� ������
	return (int)msg.wParam;

}