#include <windows.h>
#include <fstream>
#define ID_SAVE_BUTTON 1001  // 버튼 ID를 상수로 정의
#define ID_LOAD_BUTTON 1002  // 버튼 ID를 상수로 정의

wchar_t  textBuffer[2048] = { 0 }; // 텍스트 저장 버퍼
int textLength = 0; // 현재 텍스트의 길이
int y = 10;
char test = '\n';

HBRUSH hBrush_background = CreateSolidBrush(RGB(204, 255, 153)); // 배경브러쉬
HBRUSH hBrush_background1 = CreateSolidBrush(RGB(255, 255, 255));// 흰 배경 브러쉬

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CHAR:
		if (textLength < sizeof(textBuffer) - 1) { // 버퍼 오버플로우 방지
			if (wParam == VK_RETURN) {
				textBuffer[textLength] = '\n';
				textLength++;
			}
			else {
				textBuffer[textLength] = (char)wParam; // 문자 추가
				textLength++;
			}
			textBuffer[textLength] = '\0'; // 널 문자로 문자열 종료
			InvalidateRect(hWnd, NULL, TRUE); // 화면 갱신 요청
		}
		if (wParam == VK_TAB) {
			// 탭 문자를 공백 4개로 변환 (또는 원하는 수의 공백으로)
			for (int i = 0; i < 4; ++i) {
				if (textLength < sizeof(textBuffer) - 1) {
					textBuffer[textLength] = ' ';
					textLength++;
				}
			}
			textBuffer[textLength] = '\0'; // 널 문자로 문자열 종료
			InvalidateRect(hWnd, NULL, TRUE); // 화면 갱신 요청
		}
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
		switch (LOWORD(wParam)) {
		case ID_SAVE_BUTTON: {  // "저장하기" 버튼의 ID
			OPENFILENAME ofn;       // 공통 대화 상자 구조체
			wchar_t szFileName[MAX_PATH] = L"";

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFilter = L"텍스트 파일 (*.txt)\0*.txt\0모든 파일 (*.*)\0*.*\0";
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
			ofn.lpstrDefExt = L"txt";

			// "저장하기" 대화 상자를 표시
			if (GetSaveFileName(&ofn)) {
				std::wofstream file(szFileName);
				if (file.is_open()) {
					file << textBuffer;
					file.close();
				}
			}
		}
						   break;
		case ID_LOAD_BUTTON: {  // "불러오기" 버튼의 ID
			OPENFILENAME ofn;
			wchar_t szFileName[MAX_PATH] = L"";

			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFilter = L"텍스트 파일 (*.txt)\0*.txt\0모든 파일 (*.*)\0*.*\0";
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

			// 파일 열기 대화 상자 표시
			if (GetOpenFileName(&ofn)) {
				std::wifstream file(szFileName);
				if (file.is_open()) {
					textLength = 0; // 버퍼 초기화
					while (file.peek() != WEOF) {
						textBuffer[textLength++] = file.get();
						if (textLength >= sizeof(textBuffer) - 1) break; // 버퍼 오버플로우 방지
					}
					textBuffer[textLength] = '\0'; // 널 문자로 문자열 종료
					file.close();
					SetFocus(hWnd);// 포커스를 부모뷰로 하고 글을 입력하면 출력화면이 떠오름
					InvalidateRect(hWnd, NULL, TRUE); // 화면 갱신 요청
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
		// 텍스트 줄바꿈을 위한 변수들
		int lineHeight = 20; // 라인 높이
		int x = 10, y = 10; // 시작 위치
		wchar_t* lineStart = textBuffer; // 줄 시작 위치
		wchar_t* p = textBuffer; // 현재 처리 중인 문자 위치

		while (*p) {
			if (*p == L'\n') {
				// 현재 줄을 화면에 그림
				TextOut(hdc, x, y, lineStart, p - lineStart);
				// 다음 줄의 시작 위치와 y 좌표 업데이트
				lineStart = p + 1;
				y += lineHeight;
			}
			p++;
		}
		// 마지막 줄을 화면에 그림
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
		L"BUTTON", L"불러오기", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 10, 100, 60, hWnd, (HMENU)ID_LOAD_BUTTON, hInstance, NULL);

	hButton2 = CreateWindow(
		L"BUTTON", L"저장", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		120, 10, 100, 60, hWnd, (HMENU)ID_SAVE_BUTTON, hInstance, NULL);


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