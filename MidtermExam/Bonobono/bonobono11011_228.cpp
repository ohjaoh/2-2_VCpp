#include <windows.h>

// 버튼에서 L버튼이 클릭이 되어야 그려지는 변수
bool LbuttonPressed = false;
bool isMoving = false;
bool cubepressed = false;
bool spacepressed = false;
bool Bonobono = false;
bool RegionPressed = false;
// 색상버튼
int color = 0;
int Shape = 0;

// 그리는데 필요한 녀석들
POINT startPoint = { 0 };
POINT endPoint = { 0 };
RECT rectangle1 = { 0,0,0,0 }; // 사각형 초기화
RECT Box = { 8, 8, 792, 472 }; // 테두리
HBRUSH hBrush_background = CreateSolidBrush(RGB(255, 240, 200));
HBRUSH hBrush_background1 = CreateSolidBrush(RGB(255, 255, 255));
HRGN hEllipseRegion;

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_GETMINMAXINFO: {
		RECT rect = { 0, 0, 800, 480 }; // 원하는 클라이언트 영역의 크기
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
			// 첫 번째 버튼 클릭
			Bonobono = false;
			Shape = 1;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == 2) {
			// 두 번째 버튼 클릭
			Bonobono = false;
			Shape = 2;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == 3) {
			// 세 번째 버튼 클릭
			Bonobono = true;
			Shape = 3;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if (LOWORD(wParam) == 4) {
			// 네 번째 버튼 클릭
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
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(drawingView, &ps);
		FillRect(hdc, &rect, hBrush_background1);



		if (Shape == 1) {
			FillRect(hdc, &rect, (HBRUSH)(hBrush_background));
			Rectangle(hdc, rectangle1.left, rectangle1.top, rectangle1.right, rectangle1.bottom);
		}
		if (Shape == 2) {
			FillRect(hdc, &rect, (HBRUSH)(hBrush_background)); 
			HRGN hEllipseRegion = CreateEllipticRgn(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
			FillRgn(hdc, hEllipseRegion, (HBRUSH)hBrush_background);
			DeleteObject(hEllipseRegion);

		}

		if (Bonobono && spacepressed == false) {// 보노보노 눈떠
			// 피부색
			HBRUSH skinBrush = CreateSolidBrush(RGB(127, 200, 255));
			SelectObject(hdc, skinBrush);
			// 그림의 원형 피부 부분을 그립니다.
			Ellipse(hdc, 205, 37, 535, 367);

			// 입 색
			HBRUSH mouthBrush = CreateSolidBrush(RGB(255, 150, 255));
			SelectObject(hdc, mouthBrush);
			Ellipse(hdc, 350, 195, 390, 320);

			// 흰 코 부분
			HBRUSH Whites = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, Whites);
			Ellipse(hdc, 320, 210, 370, 250);
			Ellipse(hdc, 370, 210, 420, 250);

			// 눈 부분 (눈 색을 특별히 명시하지 않았으므로 기본 검은색을 사용합니다.)
			HBRUSH Blacks = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, Blacks);
			Ellipse(hdc, 250, 170, 260, 190);
			Ellipse(hdc, 490, 170, 480, 190);

			// 검은 코 부분
			Ellipse(hdc, 350, 190, 390, 230);

			// 흰 눈동자
			SelectObject(hdc, Whites);
			Ellipse(hdc, 252, 175, 258, 180);
			Ellipse(hdc, 482, 175, 488, 180);

			//수염
			MoveToEx(hdc, 340, 225, NULL);
			LineTo(hdc, 310, 210);

			MoveToEx(hdc, 400, 225, NULL);
			LineTo(hdc, 430, 210);

			MoveToEx(hdc, 340, 235, NULL);
			LineTo(hdc, 310, 250);

			MoveToEx(hdc, 400, 235, NULL);
			LineTo(hdc, 430, 250);
			// 사용한 브러시 리소스를 해제합니다.
			DeleteObject(skinBrush);
			DeleteObject(mouthBrush);

			EndPaint(drawingView, &ps);
		}
		else if (Bonobono && spacepressed == true) {// 보노보노 눈감아
			// 피부색
			HBRUSH skinBrush = CreateSolidBrush(RGB(127, 200, 255));
			SelectObject(hdc, skinBrush);
			// 그림의 원형 피부 부분을 그립니다.
			Ellipse(hdc, 205, 37, 535, 367);


			// 입 색
			HBRUSH mouthBrush = CreateSolidBrush(RGB(255, 150, 255));
			SelectObject(hdc, mouthBrush);
			Ellipse(hdc, 350, 195, 390, 320);

			// 흰 코 부분
			HBRUSH Whites = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, Whites);
			Ellipse(hdc, 320, 210, 370, 250);
			Ellipse(hdc, 370, 210, 420, 250);

			// 눈 부분 
			//왼눈
			MoveToEx(hdc, 250, 170, NULL);
			LineTo(hdc, 220, 210);
			//오른눈
			MoveToEx(hdc, 490, 170, NULL);
			LineTo(hdc, 510, 210);

			// 검은 코 부분
			Ellipse(hdc, 350, 190, 390, 230);

			// 흰 눈동자
			SelectObject(hdc, Whites);
			Ellipse(hdc, 252, 175, 258, 180);
			Ellipse(hdc, 482, 175, 488, 180);

			//수염
			MoveToEx(hdc, 340, 225, NULL);
			LineTo(hdc, 310, 210);

			MoveToEx(hdc, 400, 225, NULL);
			LineTo(hdc, 430, 210);

			MoveToEx(hdc, 340, 235, NULL);
			LineTo(hdc, 310, 250);

			MoveToEx(hdc, 400, 235, NULL);
			LineTo(hdc, 430, 250);
			// 사용한 브러시 리소스를 해제합니다.
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
		if (PtInRect(&rectangle1, { LOWORD(lParam), HIWORD(lParam) })) // 만약 상자내부에서 클릭하면
		{
			isMoving = true;
			startPoint.x = LOWORD(lParam);
			startPoint.y = HIWORD(lParam);
		}
		POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		if (PtInRegion(hEllipseRegion, pt.x, pt.y)) {
			RegionPressed = true;
		}
		

	}
	return 0;

	case WM_MOUSEMOVE:
	{
		if (LbuttonPressed) {
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);
			if (Shape == 1)
			{
				// 사각형 크기 및 위치 설정
				rectangle1.left = min(startPoint.x, endPoint.x);
				rectangle1.top = min(startPoint.y, endPoint.y);
				rectangle1.right = max(startPoint.x, endPoint.x);
				rectangle1.bottom = max(startPoint.y, endPoint.y);
				// 사각형 크기 및 위치 설정
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


			// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
			InvalidateRect(drawingView, NULL, TRUE);
			startPoint.x = mouseX;
			startPoint.y = mouseY;

		}
		if (RegionPressed) {
			int mouseX = LOWORD(lParam);
			int mouseY = HIWORD(lParam);

			// 이전 위치에서 현재 마우스 위치까지 이동한 거리 계산
			int deltaX = mouseX - startPoint.x;
			int deltaY = mouseY - startPoint.y;

		}
	}
	return 0;
	case WM_RBUTTONUP:
	{
		if (isMoving)
		{
			isMoving = false;
		}
		if (RegionPressed) {
			RegionPressed = false;
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

	WNDCLASSEX wcexDrawing;
	wcexDrawing.cbSize = sizeof(WNDCLASSEX);
	wcexDrawing.style = CS_HREDRAW | CS_VREDRAW;
	wcexDrawing.lpfnWndProc = drawingViewWndProc; // 드로잉 뷰의 메시지 처리 함수
	wcexDrawing.cbClsExtra = 0;
	wcexDrawing.cbWndExtra = 0;
	wcexDrawing.hInstance = hInstance;
	wcexDrawing.hIcon = NULL;
	wcexDrawing.hCursor = LoadCursor(NULL, IDC_CROSS); // 마우스 포인터를 십자가로 설정
	wcexDrawing.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));
	wcexDrawing.lpszMenuName = NULL;
	wcexDrawing.lpszClassName = L"DrawingViewClass";
	wcexDrawing.hIconSm = NULL;

	RegisterClassEx(&wcexDrawing);

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