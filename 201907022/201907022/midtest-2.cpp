#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Margin과 Padding 값 설정
int margin = 8;
int padding = 8;

RECT box;
HWND buttons[5]; // 5개의 버튼을 저장할 배열
HWND drawingView; // 드로잉 뷰 핸들

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HBRUSH hBrush_background = CreateSolidBrush(RGB(255, 240, 200));
    HBRUSH hBrush_white= CreateSolidBrush(RGB(255, 255, 255));

    // 윈도우 클래스 등록
    WNDCLASS wc = {};
    ZeroMemory(&wc, sizeof(wc));
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"MyWindowClass";
    wc.hbrBackground = hBrush_background;

    RegisterClass(&wc);

    /*
    WNDCLASS drawingViewClass = {}; 
	WCHAR szDrawingViewClass[] = L"DrawingViewClass";

	drawingViewClass.style = CS_HREDRAW | CS_VREDRAW;
	drawingViewClass.lpfnWndProc = WndProc;
	drawingViewClass.hInstance = hInstance;
	drawingViewClass.hCursor = LoadCursor(NULL, IDC_CROSS); // 커서 설정
	drawingViewClass.lpszClassName = szDrawingViewClass;
	drawingViewClass.hbrBackground = CreateSolidBrush(RGB(255, 255, 255)); // 두 번째 클래스의 배경색 설정

	RegisterClass(&drawingViewClass);


    */
    // 윈도우 생성
    HWND hWnd = CreateWindow(
        L"MyWindowClass", L"곰돌이",
        WS_OVERLAPPEDWINDOW, // 기존 코드에서 스타일 변경
        CW_USEDEFAULT, 0, 800, 480, nullptr, nullptr, hInstance, nullptr
    );

    if (!hWnd) {
        return -1;
    }
    if (!drawingView) {
        return -1;
    }


    // 드로잉 뷰 생성
    drawingView = CreateWindow(
        L"STATIC", L"", // 드로잉 뷰의 제목을 설정
        WS_CHILD | WS_VISIBLE | SS_SUNKEN, // 스타일을 설정
        16, 96, 784 - 2 * margin, 464 - 2 * margin, // 크기 설정
       nullptr , nullptr, hInstance, nullptr
    );

    // 윈도우를 표시
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // 메시지 루프
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT Wndmsg, WPARAM wParam, LPARAM lParam) {
    switch (Wndmsg) {
    case WM_GETMINMAXINFO: // 창 크기 정보
    {
        MINMAXINFO* minMaxInfo = (MINMAXINFO*)lParam;
        minMaxInfo->ptMinTrackSize.x = 800; // 최소 너비와 최대를 같게 하여 고정
        minMaxInfo->ptMinTrackSize.y = 480; // 최소 높이와 최대를 같게 하여 고정
        minMaxInfo->ptMaxTrackSize.x = 800; // 최대 너비
        minMaxInfo->ptMaxTrackSize.y = 480; // 최대 높이
        return 0;
    }
    return 0;
    case WM_CLOSE:
        // 윈도우 닫기 버튼 클릭 시 프로세스 종료
        PostQuitMessage(0);
        break;
    case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        HWND hwndStatic = (HWND)lParam;
       
       if(hwndStatic == drawingView) {
            // 드로잉 뷰 배경색 설정
            return (LRESULT)CreateSolidBrush(RGB(255, 255, 255));
        }
        break;
    }
    default:
        return DefWindowProc(hWnd, Wndmsg, wParam, lParam);
    }
    return 0;
}