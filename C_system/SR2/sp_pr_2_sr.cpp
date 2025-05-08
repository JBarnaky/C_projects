#include <windows.h>
#include <windowsx.h>
#include <string>
#include <vector>

using namespace std;

// Структура для хранения информации о цвете и тексте
struct ColorEntry {
    COLORREF color;
    string text;
};

class WinApp {
public:
    WinApp(HINSTANCE hInst) : hInstance(hInst), hWnd(nullptr), hButtonAdd(nullptr), hButtonExit(nullptr), hStat(nullptr), hListBox(nullptr) {}

    int Run() {
        WNDCLASSEX wc = {};
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.lpszClassName = TEXT("sp_pr2_sr_class");
        wc.lpfnWndProc = WndProc;
        wc.style = CS_VREDRAW | CS_HREDRAW;
        wc.hInstance = hInstance;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 7);
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;

        if (!RegisterClassEx(&wc)) {
            MessageBox(NULL, TEXT("Ошибка регистрации класса!"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
            return FALSE;
        }

        hWnd = CreateWindowEx(0, wc.lpszClassName, TEXT("Пример приложения. Выбор цвета <Фамилия, Имя>"), WS_OVERLAPPEDWINDOW, 0, 0, 700, 700, NULL, NULL, hInstance, this);

        if (!hWnd) {
            MessageBox(NULL, TEXT("Окно не создано!"), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
            return FALSE;
        }

        ShowWindow(hWnd, SW_SHOW);
        UpdateWindow(hWnd);

        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return (int)msg.wParam;
    }

    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        WinApp* pThis = nullptr;
        if (msg == WM_NCCREATE) {
            CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
            pThis = reinterpret_cast<WinApp*>(cs->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
        }
        else {
            pThis = reinterpret_cast<WinApp*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        }

        if (pThis) {
            return pThis->HandleMessage(hwnd, msg, wParam, lParam);
        }
        else {
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }

private:
    HINSTANCE hInstance;
    HWND hWnd;
    HWND hButtonAdd;
    HWND hButtonExit;
    HWND hStat;
    HWND hListBox;
    vector<ColorEntry> colorEntries = {
        {RGB(255,0,0), "Красный"},
        {RGB(255,125,0), "Оранжевый"},
        {RGB(255,255,0), "Желтый"},
        {RGB(0,255,0), "Зеленый"},
        {RGB(0,255,255), "Голубой"},
        {RGB(0,0,255), "Синий"},
        {RGB(125,0,255), "Фиолетовый"}
    };

    LRESULT HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        switch (msg) {
        case WM_CREATE:
            InitializeControls(hwnd);
            return 0;

        case WM_COMMAND:
            HandleCommand(wParam);
            return 0;

        case WM_PAINT:
            HandlePaint();
            return 0;

        case WM_DESTROY:
            PostQuitMessage(IDCANCEL);
            return 0;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }

    void InitializeControls(HWND parent) {
        hStat = CreateWindowEx(0, TEXT("static"), TEXT("Выбор цвета"), WS_CHILD | WS_CAPTION | WS_VISIBLE | WS_SIZEBOX,
            300, 50, 150, 80, parent, (HMENU)0, hInstance, NULL);

        hListBox = CreateWindowEx(0, TEXT("listbox"), TEXT("Список цветов"), WS_CHILD | WS_CAPTION | WS_VISIBLE | WS_SIZEBOX |
            WS_HSCROLL | WS_VSCROLL, 20, 50, 160, 250, parent, (HMENU)103, hInstance, NULL);

        for (const auto& entry : colorEntries) {
            SendMessage(hListBox, LB_ADDSTRING, 0, reinterpret_cast<LPARAM>(entry.text.c_str()));
        }
        SendMessage(hListBox, LB_SETCURSEL, 0, 0L);

        hButtonAdd = CreateWindowEx(0, TEXT("button"), TEXT("Добавить"), WS_CHILD | WS_BORDER | WS_VISIBLE, 120, 350, 90, 30, parent,
            (HMENU)101, hInstance, NULL);

        hButtonExit = CreateWindowEx(0, TEXT("button"), TEXT("Выход"), WS_CHILD | WS_BORDER | WS_VISIBLE, 250, 350, 90, 30, parent,
            (HMENU)IDCANCEL, hInstance, NULL);
    }

    void HandleCommand(WPARAM wParam) {
        int wmld = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);

        if (wmld == IDCANCEL) {
            DestroyWindow(hWnd);
            return;
        }

        if (wmld == 101) {
            HandleAddButton();
        }
    }

    void HandleAddButton() {
        TCHAR str[500] = {};
        int itemIndex = (int)SendMessage(hListBox, LB_GETCURSEL, 0, 0L);
        SendMessage(hListBox, LB_GETTEXT, itemIndex, reinterpret_cast<LPARAM>(str));

        SetWindowText(hStat, str);
        SetFocus(hStat);

        HDC hdc = GetDC(hStat);
        SetTextColor(hdc, colorEntries[itemIndex].color);
        TextOut(hdc, 0, 0, str, lstrlen(str));
        ReleaseDC(hStat, hdc);
    }

    void HandlePaint() {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        TextOut(hdc, 50, 10, TEXT("Выберите цвет:"), 14);
        EndPaint(hWnd, &ps);
    }
};

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WinApp app(hInstance);
    return app.Run();
}
