#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Sample Window Class";  // wchar_t�� L ���λ� ���

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  // �߰�: �������� ����

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Sample Drawing",  // L ���λ� ���
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
        // ���� �� �׸���
        HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
        SelectObject(hdc, hBlueBrush);
        Ellipse(hdc, 50, 50, 400, 400);
        DeleteObject(hBlueBrush);

        // �� �׸���
        HBRUSH hEyeBrush = CreateSolidBrush(RGB(0, 0, 0));
        SelectObject(hdc, hEyeBrush);
        Ellipse(hdc, 150, 150, 200, 200);  // ���� ��
        Ellipse(hdc, 250, 150, 300, 200);  // ������ ��
        DeleteObject(hEyeBrush);

        // �� �׸���
        HBRUSH hNoseBrush = CreateSolidBrush(RGB(0, 0, 0));
        SelectObject(hdc, hNoseBrush);
        Ellipse(hdc, 210, 250, 240, 280);
        DeleteObject(hNoseBrush);

        // �� �׸���
        HBRUSH hMouthBrush = CreateSolidBrush(RGB(255, 0, 255));
        SelectObject(hdc, hMouthBrush);
        Ellipse(hdc, 175, 300, 275, 320);
        DeleteObject(hMouthBrush);

        EndPaint(hwnd, &ps);
    } return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
