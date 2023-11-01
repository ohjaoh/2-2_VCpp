#include <windows.h>
#include <math.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HRGN hRegion;
bool isDragging = false;
POINT dragStartPoint;
RECT circleRect = { 50, 50, 200, 200 };

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
        L"Drag Circle",
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
        hRegion = CreateEllipticRgn(circleRect.left, circleRect.top, circleRect.right, circleRect.bottom);
        return 0;

    case WM_DESTROY:
        DeleteObject(hRegion);
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Set background color to white and clear the background
        HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
        FillRect(hdc, &ps.rcPaint, whiteBrush);
        DeleteObject(whiteBrush);

        // Draw the circle
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
            int dy = HIWORD(lParam) - dragStartPoint.y;

            HRGN newRegion = CreateRectRgn(0, 0, 0, 0);
            CombineRgn(newRegion, hRegion, NULL, RGN_COPY);
            OffsetRgn(newRegion, dx, dy);
            DeleteObject(hRegion);
            hRegion = newRegion;

            dragStartPoint.x += dx;
            dragStartPoint.y += dy;

            InvalidateRect(hwnd, NULL, TRUE);
        }
        return 0;

    case WM_LBUTTONUP:
        if (isDragging) {
            isDragging = false;
            ReleaseCapture();
        }
        return 0;

    case WM_RBUTTONDOWN:
    {
        POINT pt = { LOWORD(lParam), HIWORD(lParam) };
        if (PtInRegion(hRegion, pt.x, pt.y)) {
            int width = circleRect.right - circleRect.left;
            int height = circleRect.bottom - circleRect.top;
            int centerX = (circleRect.left + circleRect.right) / 2;
            int centerY = (circleRect.top + circleRect.bottom) / 2;

            int dx = pt.x - centerX;
            double factor = 1.0 + dx * 0.01;
            int newWidth = (int)(width * sqrt(factor));
            int newHeight = (int)(height * sqrt(factor));

            circleRect.left = centerX - newWidth / 2;
            circleRect.top = centerY - newHeight / 2;
            circleRect.right = centerX + newWidth / 2;
            circleRect.bottom = centerY + newHeight / 2;

            DeleteObject(hRegion);
            hRegion = CreateEllipticRgn(circleRect.left, circleRect.top, circleRect.right, circleRect.bottom);

            InvalidateRect(hwnd, NULL, TRUE);
        }
    }
    return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
