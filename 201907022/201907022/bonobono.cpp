#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Sample Window Class";  // wchar_t와 L 접두사 사용

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  // 추가: 윈도우의 배경색

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Sample Drawing",  // L 접두사 사용
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 450, 450,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        // 바탕 원 그리기
        HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
        SelectObject(hdc, hBlueBrush);
        Ellipse(hdc, 50, 50, 400, 400);
        DeleteObject(hBlueBrush);

        // 눈 그리기
        HBRUSH hEyeBrush = CreateSolidBrush(RGB(0, 0, 0));
        SelectObject(hdc, hEyeBrush);
        Ellipse(hdc, 150, 150, 200, 200);  // 왼쪽 눈
        Ellipse(hdc, 250, 150, 300, 200);  // 오른쪽 눈
        DeleteObject(hEyeBrush);

        // 코 그리기
        HBRUSH hNoseBrush = CreateSolidBrush(RGB(0, 0, 0));
        SelectObject(hdc, hNoseBrush);
        Ellipse(hdc, 210, 250, 240, 280);
        DeleteObject(hNoseBrush);

        // 입 그리기
        HBRUSH hMouthBrush = CreateSolidBrush(RGB(255, 0, 255));
        SelectObject(hdc, hMouthBrush);
        Ellipse(hdc, 175, 300, 275, 320);
        DeleteObject(hMouthBrush);

        EndPaint(hwnd, &ps);
    } return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
