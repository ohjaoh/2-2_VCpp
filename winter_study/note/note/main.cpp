#include <windows.h>

wchar_t  textBuffer[1024] = { 0 }; // 예시 버퍼
int textLength = 0; // 현재 텍스트의 길이

HBRUSH hBrush_background = CreateSolidBrush(RGB(204, 255, 153)); // 배경브러쉬
HBRUSH hBrush_background1 = CreateSolidBrush(RGB(255, 255, 255));// 흰 배경 브러쉬

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CHAR:
		if (textLength < sizeof(textBuffer) - 1) { // 버퍼 오버플로우 방지
			textBuffer[textLength] = (char)wParam; // 문자 추가
			textLength++;
			textBuffer[textLength] = '\0'; // 널 문자로 문자열 종료
			InvalidateRect(hWnd, NULL, TRUE); // 화면 갱신 요청
		}
		// 자녀 윈도우에 텍스트 변경을 알리고 갱신 요청
		//SendMessage(WritingView, WM_USER_TEXT_UPDATE, (WPARAM)textBuffer, (LPARAM)textLength);

		break;

	case WM_GETMINMAXINFO: {
		RECT rect = { 0, 0, 700, 900 }; // 원하는 클라이언트 영역의 크기
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

// 프로그램 진입점
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

	// Window viewport 영역 조정
	RECT rect = { 0, 0, 700, 900 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// 윈도우 생성
	HWND hWnd = CreateWindow(
		wcex.lpszClassName,
		TEXT("메모장"),
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
	wcWriting.lpfnWndProc = WritingViewWndProc; // 자식뷰의 메시지 처리 함수
	wcWriting.cbClsExtra = 0;
	wcWriting.cbWndExtra = 0;
	wcWriting.hInstance = hInstance;
	wcWriting.hIcon = NULL;
	wcWriting.hCursor = LoadCursor(NULL, IDC_IBEAM); // 마우스 포인터를 빔모양으로 설정
	wcWriting.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));
	wcWriting.lpszMenuName = NULL;
	wcWriting.lpszClassName = L"WritingViewClass";
	wcWriting.hIconSm = NULL;

	RegisterClassEx(&wcWriting);


	HWND WritingView = CreateWindow(
		L"WritingViewClass", L"", // 클래스 이름과 창 제목
		WS_CHILD | WS_VISIBLE,
		10, 80, 680, 810, // 위치와 크기 수정
		hWnd, NULL, // 부모 창과 메뉴 핸들
		hInstance, NULL
	);

	SetWindowLongPtr(WritingView, GWLP_USERDATA, (LONG_PTR)hWnd); // 부모 윈도우 핸들 저장
	SetWindowLongPtr(WritingView, GWLP_WNDPROC, (LONG_PTR)WritingViewWndProc); // 커스텀 윈도우 프로시저 설정

	if (!WritingView) {
		return -1;
	}

	if (!hWnd) {
		return FALSE;
	}

	hButton1 = CreateWindow(
		L"BUTTON", L"글작성", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 10, 100, 60, hWnd, (HMENU)1, hInstance, NULL);

	hButton2 = CreateWindow(
		L"BUTTON", L"저장", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		120, 10, 100, 60, hWnd, (HMENU)2, hInstance, NULL);


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