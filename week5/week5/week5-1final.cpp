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
RECT rectangle = { 0, 0, 0, 0 }; // 초기 사각형 위치 및 크기
bool isDrawing = false;
bool isMoving = false;

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) // UINT 로 윈도우에서 지정한 숫자들(여러 이벤트 관련인 듯)이 있다. 마우스한정 LPARAM로 좌표가 다 들어감
{
	switch (uMsg)
	{
	case WM_GETMINMAXINFO: // 창 크기 정보
	{
		MINMAXINFO* minMaxInfo = (MINMAXINFO*)lParam;
		minMaxInfo->ptMinTrackSize.x = 800; // 최소 너비와 최대를 같게 하여 고정
		minMaxInfo->ptMinTrackSize.y = 600; // 최소 높이와 최대를 같게 하여 고정
		minMaxInfo->ptMaxTrackSize.x = 800; // 최대 너비
		minMaxInfo->ptMaxTrackSize.y = 600; // 최대 높이
		return 0;
	}
	return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		RECT rect;
		GetClientRect(hwnd, &rect);
		FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1)); // 화면지우기

		HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
		SelectObject(hdc, hBrush);
		Rectangle(hdc, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);
		DeleteObject(hBrush);
		ReleaseDC(hwnd, hdc);
	}
	return 0;
	case WM_LBUTTONDOWN:

		isDrawing = true;
		startPoint.x = LOWORD(lParam);//롱파라미터의 절반의 처음 2바이트부분 (마우스의 x좌표)
		startPoint.y = HIWORD(lParam);//롱파라미터의 절반의 나중 2바이트부분 (마우스의 y좌표)
		endPoint = startPoint;
		return 0;

	case WM_RBUTTONDOWN:
	{
		if (PtInRect(&rectangle, { LOWORD(lParam), HIWORD(lParam) })) // PtInRect(rect *변수명, 포인트(x,y)좌표 ) -> 지정사각형 안에서 우클릭한 좌표가 있을 때
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

			// 사각형 크기 및 위치 설정 윈도우 api의 좌표는 좌상단을 (0, 0)으로 하고 아래로 시작위치에서 더 멀수록 큰 값임 
			rectangle.left = min(startPoint.x, endPoint.x);
			rectangle.top = min(startPoint.y, endPoint.y);
			rectangle.right = max(startPoint.x, endPoint.x);
			rectangle.bottom = max(startPoint.y, endPoint.y);


			// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
			InvalidateRect(hwnd, NULL, TRUE);
		}
		else if (isMoving)
		{
			int mouseX = LOWORD(lParam);
			int mouseY = HIWORD(lParam);

			// 이전 위치에서 현재 마우스 위치까지 이동한 거리 계산
			int deltaX = mouseX - startPoint.x;
			int deltaY = mouseY - startPoint.y;

			// 사각형 이동
			rectangle.left += deltaX;
			rectangle.top += deltaY;
			rectangle.right += deltaX;
			rectangle.bottom += deltaY;


			// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
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
		// else{}
	}
	UnregisterClass(wc.lpszClassName, wc.hInstance);
	//종료 메시지 보내기
	return (int)msg.wParam;

}