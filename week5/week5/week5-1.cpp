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

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_GETMINMAXINFO: // 창 크기 고정
	{
		MINMAXINFO* minMaxInfo = (MINMAXINFO*)lParam;
		minMaxInfo->ptMinTrackSize.x = 800; // 최소 너비
		minMaxInfo->ptMinTrackSize.y = 600; // 최소 높이
		minMaxInfo->ptMaxTrackSize.x = 800; // 최대 너비
		minMaxInfo->ptMaxTrackSize.y = 600; // 최대 높이
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
			FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1)); // 화면지우기
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
		// 좌클릭마우스 이동 중
		if (isMouseLButtonPressed)
		{
			endPointx = LOWORD(lParam);
			endPointy = HIWORD(lParam);


			// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
			InvalidateRect(hwnd, NULL, TRUE);
		}


		// 우클릭마우스 이동 중
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


			// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
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

		// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
		InvalidateRect(hwnd, NULL, TRUE);
	}
	break;

	case WM_RBUTTONUP:
	{
		isMouseRButtonPressed = 0;

		// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
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
	/* 윈도우 클래스 선언.*/
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// 모두 0으로 초기화.

	// 윈도우 클래스 값 설정
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// 윈도우 클래스 등록.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//예외
	}

	// Window viewport 영역 조정
	RECT rect = { 0, 0, 800, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 윈도우 생성
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("201907022 오자현"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
		NULL, NULL,
		hInstance,
		NULL
	);

	// 오류 검사.
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// 창 보이기.
	ShowWindow(hwnd, SW_SHOW); // 창 띄우고
	UpdateWindow(hwnd); // 업데이트해야 보임. 한 쌍으로 쓴다고 보면 됨.



	// 메시지 처리 루프.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		// 메시지 처리.
		if (GetMessage(&msg, hwnd, 0, 0))
			//if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) // PM_REMOVE의 자리는 이 메세지를 쓰고 어떡할거냐.의 의미인데 지운다는 것임.
		{

			// 메시지 해석해줘.
			TranslateMessage(&msg);
			// 메시지를 처리해야할 곳에 전달해줘.
			DispatchMessage(&msg);

		}
		/*else
		{

		}*/
	}

	//종료 메시지 보내기
	return (int)msg.wParam;

}