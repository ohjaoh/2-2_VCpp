#include <windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Margin�� Padding �� ����
int margin = 8;
int padding = 8;

RECT box;
HWND buttons[5]; // 5���� ��ư�� ������ �迭
HWND drawingView; // ����� �� �ڵ�

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    HBRUSH hBrush_background = CreateSolidBrush(RGB(255, 240, 200));
    HBRUSH hBrush_white= CreateSolidBrush(RGB(255, 255, 255));

    // ������ Ŭ���� ���
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
	drawingViewClass.hCursor = LoadCursor(NULL, IDC_CROSS); // Ŀ�� ����
	drawingViewClass.lpszClassName = szDrawingViewClass;
	drawingViewClass.hbrBackground = CreateSolidBrush(RGB(255, 255, 255)); // �� ��° Ŭ������ ���� ����

	RegisterClass(&drawingViewClass);


    */
    // ������ ����
    HWND hWnd = CreateWindow(
        L"MyWindowClass", L"������",
        WS_OVERLAPPEDWINDOW, // ���� �ڵ忡�� ��Ÿ�� ����
        CW_USEDEFAULT, 0, 800, 480, nullptr, nullptr, hInstance, nullptr
    );

    if (!hWnd) {
        return -1;
    }
    if (!drawingView) {
        return -1;
    }


    // ����� �� ����
    drawingView = CreateWindow(
        L"STATIC", L"", // ����� ���� ������ ����
        WS_CHILD | WS_VISIBLE | SS_SUNKEN, // ��Ÿ���� ����
        16, 96, 784 - 2 * margin, 464 - 2 * margin, // ũ�� ����
       nullptr , nullptr, hInstance, nullptr
    );

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT Wndmsg, WPARAM wParam, LPARAM lParam) {
    switch (Wndmsg) {
    case WM_GETMINMAXINFO: // â ũ�� ����
    {
        MINMAXINFO* minMaxInfo = (MINMAXINFO*)lParam;
        minMaxInfo->ptMinTrackSize.x = 800; // �ּ� �ʺ�� �ִ븦 ���� �Ͽ� ����
        minMaxInfo->ptMinTrackSize.y = 480; // �ּ� ���̿� �ִ븦 ���� �Ͽ� ����
        minMaxInfo->ptMaxTrackSize.x = 800; // �ִ� �ʺ�
        minMaxInfo->ptMaxTrackSize.y = 480; // �ִ� ����
        return 0;
    }
    return 0;
    case WM_CLOSE:
        // ������ �ݱ� ��ư Ŭ�� �� ���μ��� ����
        PostQuitMessage(0);
        break;
    case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        HWND hwndStatic = (HWND)lParam;
       
       if(hwndStatic == drawingView) {
            // ����� �� ���� ����
            return (LRESULT)CreateSolidBrush(RGB(255, 255, 255));
        }
        break;
    }
    default:
        return DefWindowProc(hWnd, Wndmsg, wParam, lParam);
    }
    return 0;
}