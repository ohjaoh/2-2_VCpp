#include <windows.h>

// 전역 변수
HINSTANCE hInst;
HWND hWnd;
RECT rectangle = { 0, 0, 0, 0 }; // 초기 사각형 위치 및 크기
bool isDrawing = false;
bool isMoving = false;
POINT startPoint = { 0, 0 };
POINT endPoint = { 0, 0 };
POINT moveOffset = { 0, 0 };

// 윈도우 프로시저 콜백 함수
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
        SelectObject(hdc, hBrush);
        // 사각형 그리기
        Rectangle(hdc, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);

        EndPaint(hwnd, &ps);
        DeleteObject(hBrush);

        ReleaseDC(hwnd, hdc);
    }
    return 0;

    case WM_LBUTTONDOWN:
        if (PtInRect(&rectangle, { LOWORD(lParam), HIWORD(lParam) }))
        {
            isMoving = true;
            startPoint.x = LOWORD(lParam);
            startPoint.y = HIWORD(lParam);
        }
        else
        {
            isDrawing = true;
            startPoint.x = LOWORD(lParam);
            startPoint.y = HIWORD(lParam);
            endPoint = startPoint;
        }
        return 0;

    case WM_MOUSEMOVE:
        if (isDrawing)
        {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);

            // 사각형 크기 및 위치 설정
            rectangle.left = min(startPoint.x, endPoint.x);
            rectangle.top = min(startPoint.y, endPoint.y);
            rectangle.right = max(startPoint.x, endPoint.x);
            rectangle.bottom = max(startPoint.y, endPoint.y);

            // 윈도우 다시 그리기
            InvalidateRect(hwnd, NULL, TRUE);
        }
        else if (isMoving)
        {
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);

            // 이전 위치에서 현재 마우스 위치까지 이동한 거리 계산
            int deltaX = mouseX - startPoint.x;
            int deltaY = mouseY - startPoint.y;

            // 사각형 이동
            rectangle.left += deltaX;
            rectangle.top += deltaY;
            rectangle.right += deltaX;
            rectangle.bottom += deltaY;

            // 윈도우 다시 그리기
            InvalidateRect(hwnd, NULL, TRUE);

            startPoint.x = mouseX;
            startPoint.y = mouseY;
        }
        return 0;

    case WM_LBUTTONUP:
        if (isDrawing)
        {
            isDrawing = false;
        }
        else if (isMoving)
        {
            isMoving = false;
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wcex;
    memset(&wcex, 0, sizeof(wcex));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.lpszClassName = L"WindowClass";
    RegisterClassEx(&wcex);

    hWnd = CreateWindow(L"WindowClass", L"WinAPI Rectangle Draw & Move", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
