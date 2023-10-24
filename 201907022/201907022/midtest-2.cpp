#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Margin�� Padding �� ����
int margin = 8;
int padding = 8;

HWND box;
HWND buttons[5]; // 5���� ��ư�� ������ �迭
HWND drawingView; // ����� �� �ڵ�

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HBRUSH hBrush_background = CreateSolidBrush(RGB(255, 240, 200));

    // ������ Ŭ���� ���
    WNDCLASS wc = {};
    ZeroMemory(&wc, sizeof(wc));
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"MyWindowClass";

    RegisterClass(&wc);

    // ������ ����
    HWND hWnd = CreateWindow(
        L"MyWindowClass", L"������",
        WS_OVERLAPPEDWINDOW, // ���� �ڵ忡�� ��Ÿ�� ����
        CW_USEDEFAULT, 0, 800, 480, nullptr, nullptr, hInstance, nullptr
    );

    if (!hWnd) {
        return -1;
    }

    SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush_background);

    // View Box ����
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

    // �ڽ� ���� ũ�� ���
    RECT boxRect;
    GetClientRect(box, &boxRect);

    // ��ư ����
    for (int i = 0; i < 5; i++) {
        margin = 16;
        buttons[i] = CreateWindow(
            L"BUTTON", L"Button",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // ��ư ��Ÿ���� BS_PUSHBUTTON���� ����
            boxRect.left + margin + i * (boxRect.right - 2 * margin) / 5, boxRect.top + margin,
            (boxRect.right - 2 * margin) / 5 - 2 * margin, 64, // ��ư ũ�⸦ 160x64�� ����
            box, nullptr, hInstance, nullptr
        );
        int margin = 8;
    }

    if (!buttons[0]) {
        return -1;
    }

    // ����� �� ����
    drawingView = CreateWindow(
        L"STATIC", L"", // ����� ���� ������ ����
        WS_CHILD | WS_VISIBLE | SS_SUNKEN, // ��Ÿ���� ����
        16, 96, boxRect.right - 2 * margin, boxRect.bottom - 2 * margin, // ũ�� ����
        box, nullptr, hInstance, nullptr
    );

    if (!drawingView) {
        return -1;
    }

    // ����� �� ���� ���� (���)
    HBRUSH hBrush_drawing = CreateSolidBrush(RGB(255, 255, 255)); // ��� ���
    SetClassLongPtr(drawingView, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush_drawing);

    // ���콺 Ŀ���� ũ�ν�(CROSS) ������� ����
    HCURSOR hCursor = LoadCursor(nullptr, IDC_CROSS);
    SetClassLongPtr(drawingView, GCLP_HCURSOR, (LONG_PTR)hCursor);

    // �����츦 ǥ��
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // �޽��� ����
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
        // ������ �ݱ� ��ư Ŭ�� �� ���μ��� ����
        PostQuitMessage(0);
        break;
    case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        HWND hwndStatic = (HWND)lParam;

        if (hwndStatic == box) {
            // �ڽ��� ���� ����
            SetBkColor(hdcStatic, RGB(255, 240, 200)); // RGB(255, 240, 200)�� ���� ����
            return (LRESULT)CreateSolidBrush(RGB(255, 240, 200));
        }
        else if (hwndStatic == drawingView) {
            // ����� �� ���� ����
            SetBkColor(hdcStatic, RGB(255, 255, 255)); // ��� ��� ����
            return (LRESULT)CreateSolidBrush(RGB(255, 255, 255));
        }
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
