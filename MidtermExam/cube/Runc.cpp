#include <windows.h>
#include "yuhanCG.h"
#include "cube.h"

// 버튼에서 L버튼이 클릭이 되어야 그려지는 변수
bool LbuttonPressed = false;
bool SpacePressed = false;
bool LbuttonCube = false;
int Shape = 0;
int isMoving = 0;

// 그리는데 필요한 녀석들
POINT startPoint = { 0 };
POINT endPoint = { 0 };
RECT rectangle1 = { 0,0,0,0 }; // 사각형 초기화
RECT Eclip = { 0,0,0,0 }; // 원 초기화
RECT Box = { 8, 8, 792, 472 }; // 테두리
HRGN cube = { 0 };
POINT test = { 0 };

HBRUSH hBrush_background = CreateSolidBrush(RGB(255, 240, 200)); // 배경브러쉬
HBRUSH hBrush_background1 = CreateSolidBrush(RGB(255, 255, 255));// 흰 배경 브러쉬

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_KEYDOWN:
		if (wParam == VK_SPACE)
		{
			if (SpacePressed == false) {
				SpacePressed = true;
			}

			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_KEYUP:
		if (wParam == VK_SPACE) {
			if (SpacePressed == true) {
				SpacePressed = false;
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_GETMINMAXINFO: {
		RECT rect = { 0, 0, 800, 480 }; // 원하는 클라이언트 영역의 크기
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

		MINMAXINFO* minmax = (MINMAXINFO*)lParam;
		minmax->ptMinTrackSize.x = rect.right - rect.left;
		minmax->ptMinTrackSize.y = rect.bottom - rect.top;
		minmax->ptMaxTrackSize.x = rect.right - rect.left;
		minmax->ptMaxTrackSize.y = rect.bottom - rect.top; }
						 return 0;

	case WM_COMMAND:
		if (LOWORD(wParam) == 1) {
			rectangle1 = { 0,0,0,0 };
			// 첫 번째 버튼 클릭
			Shape = 1;
			SetFocus(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == 2) {
			Eclip = { 0,0,0,0 };
			// 두 번째 버튼 클릭
			Shape = 2;
			SetFocus(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == 3) {
			// 세 번째 버튼 클릭
			Shape = 3;
			SetFocus(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == 4) {
			// 네 번째 버튼 클릭
			Shape = 4;
			SetFocus(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
			startPoint = { 0 };
			endPoint = { 0 };
		}
		else if (LOWORD(wParam) == 5) {
			Shape = 5;
			SetFocus(hWnd);
			InvalidateRect(hWnd, NULL, TRUE);
			startPoint = { 0 };
			endPoint = { 0 };
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

		if (Shape == 3) {
			FillRect(hdc, &rect, (HBRUSH)(hBrush_background1));
			int blink = SpacePressed;
			DrawBonobono(drawingView, hdc, blink);
		}

		if (Shape == 4) {
			FillRect(hdc, &rect, (HBRUSH)(hBrush_background1));
			int left = startPoint.x;
			int top = startPoint.y;
			int right = endPoint.x;
			int bottom = endPoint.y;

			DrawRyan(drawingView, hdc, left, top, right, bottom);
		}

		if (Shape == 5) {
			cube = Drawcube(drawingView, hdc, startPoint, endPoint);
		}

		EndPaint(drawingView, &ps);
		break;
	}
				 break;
	case WM_LBUTTONDOWN: {
		if (Shape == 1 || Shape == 2 || Shape == 4 || Shape == 5) {
			startPoint.x = LOWORD(lParam);
			startPoint.y = HIWORD(lParam);
		}
		if (PtInRegion(cube, LOWORD(lParam), HIWORD(lParam))) {
			LbuttonCube = true;
			test.x = LOWORD(lParam);
			test.y = HIWORD(lParam);
		}
		else {
			LbuttonPressed = true;
		}
	}break;
	case WM_LBUTTONUP: {
		LbuttonPressed = false;
		endPoint.x = LOWORD(lParam);
		endPoint.y = HIWORD(lParam);
		if (LbuttonCube)
		{
			LbuttonCube = false;
		}
	}break;

	case WM_RBUTTONDOWN:
	{
		if (PtInRect(&rectangle1, { LOWORD(lParam), HIWORD(lParam) })) // 만약 도형내부에서 클릭하면
		{
			// 도형내부에 클릭한 지점을 기준으로 사각형을 이동시킴
			isMoving = 1;
			startPoint.x = LOWORD(lParam);
			startPoint.y = HIWORD(lParam);

		}
		if (PtInRegion(cube, LOWORD(lParam), HIWORD(lParam))) {
			// cube는 lParam으로 startpoint를 변경하면 크기가 변함
			isMoving = 2;
			test.x = LOWORD(lParam);
			test.y = HIWORD(lParam);
		}

	}
	return 0;

	case WM_RBUTTONUP:
	{
		if (isMoving > 0)
		{
			isMoving = 0;
		}
	}
	return 0;
	case WM_MOUSEMOVE:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(drawingView, &ps);
		POINT currentPoint = { 0 };

		currentPoint.x = LOWORD(lParam);
		currentPoint.y = HIWORD(lParam);

		// startPoint와 currentPoint 사이의 차이를 계산
		int deltaX = 0; deltaX = currentPoint.x - test.x;
		int deltaY = 0; deltaY = currentPoint.y - test.y;

		if (LbuttonPressed) {
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);
			if (Shape == 1 || Shape == 2)
			{
				rectangle1 = Drawrect(rectangle1, startPoint, endPoint);
				Eclip = Drawrect(Eclip, startPoint, endPoint);
				// WM_PAINT 메시지를 유발하여 화면에 그립니다.
				InvalidateRect(drawingView, NULL, TRUE);
			}
			if (Shape == 4 || Shape == 5) {
				InvalidateRect(drawingView, NULL, TRUE);
			}
		}

		if (isMoving == 1)
		{
			rectangle1 = MoveRactangle(lParam, rectangle1, startPoint);
			Eclip = ScaleCircle(lParam, Eclip, startPoint);

			int mouseX = LOWORD(lParam);
			int mouseY = HIWORD(lParam);
			startPoint.x = mouseX;
			startPoint.y = mouseY;

			// WM_PAINT 메시지를 유발하여 도형을 화면에 그립니다.
			InvalidateRect(drawingView, NULL, TRUE);
		}
		if (isMoving == 2) {
			// 도형 이동
			Movecube(&startPoint, &endPoint, deltaX, deltaY);
			cube = Drawcube(drawingView, hdc, startPoint, endPoint);

			test = currentPoint;
			// WM_PAINT 메시지를 유발하여 도형을 화면에 그립니다.
			InvalidateRect(drawingView, NULL, TRUE);
		}

		if (LbuttonCube) {
			ScaleCube(&startPoint, &endPoint, deltaX);
			cube = Drawcube(drawingView, hdc, startPoint, endPoint);

			test = currentPoint;
			// WM_PAINT 메시지를 유발하여 도형을 화면에 그립니다.
			InvalidateRect(drawingView, NULL, TRUE);
		}

	}
	return 0;

	default:
		return CallWindowProc(DefWindowProc, drawingView, message, wParam, lParam);
	}
	return 0;
}

// 프로그램 진입점
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

	// Window viewport 영역 조정
	RECT rect = { 0, 0, 800, 480 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 윈도우 생성
	HWND hWnd = CreateWindow(
		wcex.lpszClassName,
		TEXT("곰돌이"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
		NULL, NULL,
		hInstance,
		NULL
	);

	WNDCLASSEX wcDrawing;
	wcDrawing.cbSize = sizeof(WNDCLASSEX);
	wcDrawing.style = CS_HREDRAW | CS_VREDRAW;
	wcDrawing.lpfnWndProc = drawingViewWndProc; // 드로잉 뷰의 메시지 처리 함수
	wcDrawing.cbClsExtra = 0;
	wcDrawing.cbWndExtra = 0;
	wcDrawing.hInstance = hInstance;
	wcDrawing.hIcon = NULL;
	wcDrawing.hCursor = LoadCursor(NULL, IDC_CROSS); // 마우스 포인터를 십자가로 설정
	wcDrawing.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));
	wcDrawing.lpszMenuName = NULL;
	wcDrawing.lpszClassName = L"DrawingViewClass";
	wcDrawing.hIconSm = NULL;

	RegisterClassEx(&wcDrawing);


	HWND drawingView = CreateWindow(
		L"DrawingViewClass", L"", // 클래스 이름과 창 제목
		WS_CHILD | WS_VISIBLE,
		16, 88, 768, 376, // 위치와 크기 수정
		hWnd, NULL, // 부모 창과 메뉴 핸들
		hInstance, NULL
	);

	SetWindowLongPtr(drawingView, GWLP_USERDATA, (LONG_PTR)hWnd); // 부모 윈도우 핸들 저장
	SetWindowLongPtr(drawingView, GWLP_WNDPROC, (LONG_PTR)drawingViewWndProc); // 커스텀 윈도우 프로시저 설정

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
		L"BUTTON", L"큐브", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		640, 16, 140, 64, hWnd, (HMENU)5, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// 메시지 루프
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) { // get으로 메시지 잡아줌
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}