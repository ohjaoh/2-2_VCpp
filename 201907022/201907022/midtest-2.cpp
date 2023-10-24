#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Margin과 Padding 값 설정
int margin = 8;
int padding = 8;

HWND box;
HWND buttons[5]; // 5개의 버튼을 저장할 배열
HWND drawingView; // 드로잉 뷰 핸들

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HBRUSH hBrush_background = CreateSolidBrush(RGB(255, 240, 200));

    // 윈도우 클래스 등록
    WNDCLASS wc = {};
    ZeroMemory(&wc, sizeof(wc));
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"MyWindowClass";

    RegisterClass(&wc);

    // 윈도우 생성
    HWND hWnd = CreateWindow(
        L"MyWindowClass", L"곰돌이",
        WS_OVERLAPPEDWINDOW, // 기존 코드에서 스타일 변경
        CW_USEDEFAULT, 0, 800, 480, nullptr, nullptr, hInstance, nullptr
    );

    if (!hWnd) {
        return -1;
    }

    SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush_background);

    // View Box 생성
    box = CreateWindow(
        L"STATIC", L"",
        WS_CHILD | WS_VISIBLE | SS_SUNKEN,
        margin, margin, 800 - 2 * margin, 480 - 2 * margin,
        hWnd, nullptr, hInstance, nullptr
    );

    if (!box) {
        return -1;
    }
    SetClassLongPtr(box, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush_background);

    // 박스 뷰의 크기 얻기
    RECT boxRect;
    GetClientRect(box, &boxRect);

    // 버튼 생성
    for (int i = 0; i < 5; i++) {
        margin = 16;
        buttons[i] = CreateWindow(
            L"BUTTON", L"Button",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // 버튼 스타일을 BS_PUSHBUTTON으로 변경
            boxRect.left + margin + i * (boxRect.right - 2 * margin) / 5, boxRect.top + margin,
            (boxRect.right - 2 * margin) / 5 - 2 * margin, 64, // 버튼 크기를 160x64로 조정
            box, nullptr, hInstance, nullptr
        );
        int margin = 8;
    }

    if (!buttons[0]) {
        return -1;
    }

    // 드로잉 뷰 생성
    drawingView = CreateWindow(
        L"STATIC", L"", // 드로잉 뷰의 제목을 설정
        WS_CHILD | WS_VISIBLE | SS_SUNKEN, // 스타일을 설정
        16, 96, boxRect.right - 2 * margin, boxRect.bottom - 2 * margin, // 크기 설정
        box, nullptr, hInstance, nullptr
    );

    if (!drawingView) {
        return -1;
    }

    // 드로잉 뷰 배경색 설정 (흰색)
    HBRUSH hBrush_drawing = CreateSolidBrush(RGB(255, 255, 255)); // 흰색 배경
    SetClassLongPtr(drawingView, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush_drawing);

    // 마우스 커서를 크로스(CROSS) 모양으로 변경
    HCURSOR hCursor = LoadCursor(nullptr, IDC_CROSS);
    SetClassLongPtr(drawingView, GCLP_HCURSOR, (LONG_PTR)hCursor);

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CLOSE:
        // 윈도우 닫기 버튼 클릭 시 프로세스 종료
        PostQuitMessage(0);
        break;
    case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        HWND hwndStatic = (HWND)lParam;

        if (hwndStatic == box) {
            // 박스뷰 배경색 설정
            SetBkColor(hdcStatic, RGB(255, 240, 200)); // RGB(255, 240, 200)로 배경색 설정
            return (LRESULT)CreateSolidBrush(RGB(255, 240, 200));
        }
        else if (hwndStatic == drawingView) {
            // 드로잉 뷰 배경색 설정
            SetBkColor(hdcStatic, RGB(255, 255, 255)); // 흰색 배경 설정
            return (LRESULT)CreateSolidBrush(RGB(255, 255, 255));
        }
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
