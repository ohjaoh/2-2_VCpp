#include <windows.h>
#include <math.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HRGN hRegion;
bool isDragging = false;
bool isResizing = false;
POINT dragStartPoint;
POINT pt;
RECT circleRect = { 50, 50, 200, 200 };

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Drag and Resize Circle",
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

    case WM_DESTROY: {
        DeleteObject(hRegion);
        PostQuitMessage(0);
    }return 0;

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

    case WM_LBUTTONDOWN: {
        pt = { LOWORD(lParam), HIWORD(lParam) };
        if (PtInRegion(hRegion, pt.x, pt.y)) {
            isDragging = true;
            dragStartPoint = pt;
            SetCapture(hwnd);
        }
    }
        return 0;

    case WM_RBUTTONDOWN: {
        pt = { LOWORD(lParam), HIWORD(lParam) };
        if (PtInRegion(hRegion, pt.x, pt.y)) {
            isResizing = true;
            dragStartPoint = pt;
            SetCapture(hwnd);
        }
    }
        return 0;

    case WM_MOUSEMOVE:
        if (isDragging || isResizing) {
            int dx = LOWORD(lParam) - dragStartPoint.x;
            int dy = HIWORD(lParam) - dragStartPoint.y;

            if (isDragging) {
                OffsetRect(&circleRect, dx, dy);
            }
            else if (isResizing) {
                int width = circleRect.right - circleRect.left;
                int height = circleRect.bottom - circleRect.top;
                int newWidth = width + dx;
                int newHeight = height + dy;
                if (newWidth > 10 && newHeight > 10) {
                    circleRect.right = circleRect.left + newWidth;
                    circleRect.bottom = circleRect.top + newHeight;
                }
            }

            DeleteObject(hRegion);
            hRegion = CreateEllipticRgn(circleRect.left, circleRect.top, circleRect.right, circleRect.bottom);
            InvalidateRect(hwnd, NULL, TRUE);

            dragStartPoint.x += dx;
            dragStartPoint.y += dy;
        }
        return 0;

    case WM_LBUTTONUP:
        if (isDragging) {
            isDragging = false;
            ReleaseCapture();
        }
        return 0;

    case WM_RBUTTONUP:
        if (isResizing) {
            isResizing = false;
            ReleaseCapture();
        }
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
