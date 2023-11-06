#include <windows.h>

// 버튼에서 L버튼이 클릭이 되어야 그려지는 변수
bool LbuttonPressed = false;
bool isMoving = false;
bool SpacePressed = false;
int Shape = 0;

// 그리는데 필요한 녀석들
POINT startPoint = { 0 };
POINT endPoint = { 0 };
RECT rectangle1 = { 0,0,0,0 }; // 사각형 초기화
RECT Eclip = { 0,0,0,0 }; // 원 초기화
RECT Box = { 8, 8, 792, 472 }; // 테두리

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
		}
		else if (LOWORD(wParam) == 5) {
			Shape = 5;
			SetFocus(hWnd);
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

		if (Shape == 3 && SpacePressed == false) {// 보노보노 눈떠
			// 피부색
			HBRUSH skinBrush = CreateSolidBrush(RGB(127, 200, 255));
			SelectObject(hdc, skinBrush);
			// 그림의 원형 피부 부분을 그립니다.
			Ellipse(hdc, 211, 37, 541, 367);

			// 입 색
			HBRUSH mouthBrush = CreateSolidBrush(RGB(255, 150, 255));
			SelectObject(hdc, mouthBrush);
			Ellipse(hdc, 356, 195, 396, 320);

			// 흰 코 부분
			HBRUSH Whites = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, Whites);
			Ellipse(hdc, 326, 210, 376, 250);
			Ellipse(hdc, 376, 210, 426, 250);

			// 눈 부분 (눈 색을 특별히 명시하지 않았으므로 기본 검은색을 사용합니다.)
			HBRUSH Blacks = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, Blacks);
			Ellipse(hdc, 256, 170, 266, 190);
			Ellipse(hdc, 496, 170, 486, 190);

			// 검은 코 부분
			Ellipse(hdc, 356, 190, 396, 230);

			// 흰 눈동자
			SelectObject(hdc, Whites);
			Ellipse(hdc, 258, 175, 266, 180);
			Ellipse(hdc, 488, 175, 496, 180);
			//수염
			MoveToEx(hdc, 346, 225, NULL);
			LineTo(hdc, 316, 210);

			MoveToEx(hdc, 406, 225, NULL);
			LineTo(hdc, 436, 210);

			MoveToEx(hdc, 346, 235, NULL);
			LineTo(hdc, 316, 250);

			MoveToEx(hdc, 406, 235, NULL);
			LineTo(hdc, 436, 250);
			// 사용한 브러시 리소스를 해제합니다.
			DeleteObject(skinBrush);
			DeleteObject(mouthBrush);
			DeleteObject(Whites);
			DeleteObject(Blacks);

			/*// 중앙선 나중에 지울것
			MoveToEx(hdc, 376, 0, NULL);
			LineTo(hdc, 376, 480);
			MoveToEx(hdc, 0, 184, NULL);
			LineTo(hdc, 800, 184);*/

			EndPaint(drawingView, &ps);
		}
		else if (Shape == 3 && SpacePressed == true) {// 보노보노 눈감아
			// 피부색
			HBRUSH skinBrush = CreateSolidBrush(RGB(127, 200, 255));
			SelectObject(hdc, skinBrush);
			// 그림의 원형 피부 부분을 그립니다.
			Ellipse(hdc, 211, 37, 541, 367);

			// 입 색
			HBRUSH mouthBrush = CreateSolidBrush(RGB(255, 150, 255));
			SelectObject(hdc, mouthBrush);
			Ellipse(hdc, 356, 195, 396, 320);

			// 흰 코 부분
			HBRUSH Whites = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, Whites);
			Ellipse(hdc, 326, 210, 376, 250);
			Ellipse(hdc, 376, 210, 426, 250);

			// 눈 부분
			//왼눈
			MoveToEx(hdc, 261, 175, NULL);
			LineTo(hdc, 246, 165);
			MoveToEx(hdc, 261, 175, NULL);
			LineTo(hdc, 246, 185);
			//오른눈
			MoveToEx(hdc, 491, 175, NULL);
			LineTo(hdc, 506, 165);
			MoveToEx(hdc, 491, 175, NULL);
			LineTo(hdc, 506, 185);

			// 검은 코 부분
			HBRUSH Blacks = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, Blacks);
			Ellipse(hdc, 356, 190, 396, 230);

			//수염
			MoveToEx(hdc, 346, 225, NULL);
			LineTo(hdc, 316, 210);
			
			MoveToEx(hdc, 406, 225, NULL);
			LineTo(hdc, 436, 210);

			MoveToEx(hdc, 346, 235, NULL);
			LineTo(hdc, 316, 250);

			MoveToEx(hdc, 406, 235, NULL);
			LineTo(hdc, 436, 250);
			// 사용한 브러시 리소스를 해제합니다.
			DeleteObject(skinBrush);
			DeleteObject(mouthBrush);
			DeleteObject(Whites);
			DeleteObject(Blacks);
			
			/*// 중앙선 나중에 지울것
			MoveToEx(hdc, 376, 0, NULL);
			LineTo(hdc, 376, 480);
			MoveToEx(hdc, 0, 184, NULL);
			LineTo(hdc, 800, 184);*/

			EndPaint(drawingView, &ps);
		}

		if (Shape == 4) {
			// 피부색
			HBRUSH RskinBrush = CreateSolidBrush(RGB(255, 200, 15));
			SelectObject(hdc, RskinBrush);
			// 귀부분
			// 왼귀
			Ellipse(hdc, 191, 15, 306, 135);
			// 오른귀
			Ellipse(hdc, 446, 15, 561, 135);
			// 얼굴
			Ellipse(hdc, 211, 37, 541, 367);

			// 눈
			HBRUSH Blacks = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, Blacks);
			Ellipse(hdc, 290, 150, 310, 170);
			Ellipse(hdc, 462, 150, 442, 170);

			// 눈썹3가닥
			MoveToEx(hdc, 270, 130, NULL);
			LineTo(hdc, 335, 130);
			MoveToEx(hdc, 270, 132, NULL);
			LineTo(hdc, 335, 132);
			MoveToEx(hdc, 270, 134, NULL);
			LineTo(hdc, 335, 134);


			MoveToEx(hdc, 417, 130, NULL);
			LineTo(hdc, 482, 130);
			MoveToEx(hdc, 417, 132, NULL);
			LineTo(hdc, 482, 132);
			MoveToEx(hdc, 417, 134, NULL);
			LineTo(hdc, 482, 134);


			// 코
			HBRUSH Whites = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, Whites);
			Ellipse(hdc, 376, 198, 416, 238);
			Ellipse(hdc, 336, 198, 376, 238);

			
			/*// 중앙선 나중에 지울것
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
		if (PtInRect(&rectangle1, { LOWORD(lParam), HIWORD(lParam) })) // 만약 상자내부에서 클릭하면
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
				// 사각형 크기 및 위치 설정
				rectangle1.left = min(startPoint.x, endPoint.x);
				rectangle1.top = min(startPoint.y, endPoint.y);
				rectangle1.right = max(startPoint.x, endPoint.x);
				rectangle1.bottom = max(startPoint.y, endPoint.y);
				// 원의 크기 및 위치 설정
				Eclip.left = min(startPoint.x, endPoint.x);
				Eclip.top = min(startPoint.y, endPoint.y);
				Eclip.right = max(startPoint.x, endPoint.x);
				Eclip.bottom = max(startPoint.y, endPoint.y);
				// WM_PAINT 메시지를 유발하여 화면에 그립니다.
				InvalidateRect(drawingView, NULL, TRUE);
			}
		}
		if (isMoving)
		{
			int mouseX = LOWORD(lParam);
			int mouseY = HIWORD(lParam);

			// 이전 위치에서 현재 마우스 위치까지 이동한 거리 계산
			int deltaX = mouseX - startPoint.x;
			int deltaY = mouseY - startPoint.y;

			// 사각형 이동
			rectangle1.left += deltaX;
			rectangle1.top += deltaY;
			rectangle1.right += deltaX;
			rectangle1.bottom += deltaY;

			double scaleFactor = 1;
			if (deltaX > 0) {
				scaleFactor = 1.0 + static_cast<double>(deltaX) / 100.0;  // 오른쪽으로 이동할 때마다 크기를 증가시킵니다.
			}
			else if (deltaX < 0) {
				scaleFactor = 1.0 / (1.0 - static_cast<double>(deltaX) / 100.0);  // 왼쪽으로 이동할 때마다 크기를 감소시킵니다.
			}
			else {
				scaleFactor = 1.0;  // 가로 이동이 없을 경우 크기는 변하지 않습니다.
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
			// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
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
		16, 98, 768, 368, // 위치와 크기
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

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}