#ifdef _DEBUG_
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif

#include <windows.h>

POINT startPoint = { 0 };
POINT endPoint = { 0 };
RECT rectangle = { 0, 0, 0, 0 }; // �ʱ� �簢�� ��ġ �� ũ��
bool isDrawing = false;
bool isMoving = false;

// �������� �̺�Ʈ�� ó���ϴ� �ݹ�(Callback) �Լ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) // UINT �� �����쿡�� ������ ���ڵ�(���� �̺�Ʈ ������ ��)�� �ִ�. ���콺���� LPARAM�� ��ǥ�� �� ��
{
	switch (uMsg)
	{
	case WM_GETMINMAXINFO: // â ũ�� ����
	{
		MINMAXINFO* minMaxInfo = (MINMAXINFO*)lParam;
		minMaxInfo->ptMinTrackSize.x = 800; // �ּ� �ʺ�� �ִ븦 ���� �Ͽ� ����
		minMaxInfo->ptMinTrackSize.y = 600; // �ּ� ���̿� �ִ븦 ���� �Ͽ� ����
		minMaxInfo->ptMaxTrackSize.x = 800; // �ִ� �ʺ�
		minMaxInfo->ptMaxTrackSize.y = 600; // �ִ� ����
		return 0;
	}
	return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		RECT rect;
		GetClientRect(hwnd, &rect);
		FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1)); // ȭ�������

		HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
		SelectObject(hdc, hBrush);
		Rectangle(hdc, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);
		DeleteObject(hBrush);
		ReleaseDC(hwnd, hdc);
	}
	return 0;
	case WM_LBUTTONDOWN:

		isDrawing = true;
		startPoint.x = LOWORD(lParam);//���Ķ������ ������ ó�� 2����Ʈ�κ� (���콺�� x��ǥ)
		startPoint.y = HIWORD(lParam);//���Ķ������ ������ ���� 2����Ʈ�κ� (���콺�� y��ǥ)
		endPoint = startPoint;
		return 0;

	case WM_RBUTTONDOWN:
	{
		if (PtInRect(&rectangle, { LOWORD(lParam), HIWORD(lParam) })) // PtInRect(rect *������, ����Ʈ(x,y)��ǥ ) -> �����簢�� �ȿ��� ��Ŭ���� ��ǥ�� ���� ��
		{
			isMoving = true;
			startPoint.x = LOWORD(lParam);
			startPoint.y = HIWORD(lParam);
		}


	}
	return 0;

	case WM_MOUSEMOVE:
	{
		if (isDrawing)
		{
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);

			// �簢�� ũ�� �� ��ġ ���� ������ api�� ��ǥ�� �»���� (0, 0)���� �ϰ� �Ʒ��� ������ġ���� �� �ּ��� ū ���� 
			rectangle.left = min(startPoint.x, endPoint.x);
			rectangle.top = min(startPoint.y, endPoint.y);
			rectangle.right = max(startPoint.x, endPoint.x);
			rectangle.bottom = max(startPoint.y, endPoint.y);


			// WM_PAINT �޽����� �����Ͽ� �׸� ȭ�鿡 �׸��ϴ�.
			InvalidateRect(hwnd, NULL, TRUE);
		}
		else if (isMoving)
		{
			int mouseX = LOWORD(lParam);
			int mouseY = HIWORD(lParam);

			// ���� ��ġ���� ���� ���콺 ��ġ���� �̵��� �Ÿ� ���
			int deltaX = mouseX - startPoint.x;
			int deltaY = mouseY - startPoint.y;

			// �簢�� �̵�
			rectangle.left += deltaX;
			rectangle.top += deltaY;
			rectangle.right += deltaX;
			rectangle.bottom += deltaY;


			// WM_PAINT �޽����� �����Ͽ� �׸� ȭ�鿡 �׸��ϴ�.
			InvalidateRect(hwnd, NULL, TRUE);
			startPoint.x = mouseX;
			startPoint.y = mouseY;

		}
	}
	return 0;

	case WM_LBUTTONUP:
	{
		if (isDrawing)
		{
			isDrawing = false;
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
		exit(-1);
		return 0;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		return 0;
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
		// else{}
	}
	UnregisterClass(wc.lpszClassName, wc.hInstance);
	//���� �޽��� ������
	return (int)msg.wParam;

}