#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HRGN hRegion;
bool isDragging = false;
POINT dragStartPoint;
RECT ellipseRect = { 50, 50, 200, 200 };

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Drag to Resize Circle",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 300,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_CREATE:
        hRegion = CreateEllipticRgn(ellipseRect.left, ellipseRect.top, ellipseRect.right, ellipseRect.bottom);
        return 0;

    case WM_DESTROY:
        DeleteObject(hRegion);
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // 배경을 흰색으로 채웁니다.
        HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(hdc, &ps.rcPaint, whiteBrush);
        DeleteObject(whiteBrush);

        // 원을 그립니다.
        HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
        FillRgn(hdc, hRegion, redBrush);
        DeleteObject(redBrush);

        EndPaint(hwnd, &ps);
    }
    return 0;

    case WM_LBUTTONDOWN:
    {
        POINT pt = { LOWORD(lParam), HIWORD(lParam) };
        if (PtInRegion(hRegion, pt.x, pt.y)) {
            isDragging = true;
            dragStartPoint = pt;
            SetCapture(hwnd);
        }
    }
    return 0;

    case WM_MOUSEMOVE:
        if (isDragging) {
            int dx = LOWORD(lParam) - dragStartPoint.x;

            // 원을 확대/축소
            if (dx > 0) {
                ellipseRect.right += dx;
                ellipseRect.bottom += dx;
            }
            else if (dx < 0) {
                ellipseRect.right += dx;
                ellipseRect.bottom += dx;
            }

            // 새로운 지역을 생성
            DeleteObject(hRegion);
            hRegion = CreateEllipticRgn(ellipseRect.left, ellipseRect.top, ellipseRect.right, ellipseRect.bottom);

            dragStartPoint.x = LOWORD(lParam);

            InvalidateRect(hwnd, NULL, TRUE);
        }
        return 0;

    case WM_LBUTTONUP:
        if (isDragging) {
            isDragging = false;
            ReleaseCapture();
        }
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
