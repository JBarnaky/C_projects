#include <windows.h>
#include <cstdlib> // For rand()
#include <ctime>   // For time

// Constants for window dimensions
const int WIDTH = 1920;
const int HEIGHT = 1080;
const int FRAME_RATE = 60;
const int FRAME_TIME = 1000 / FRAME_RATE; // Frame time in milliseconds

// Function declarations
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void GenerateWhiteNoise(HDC hdc);

// Entry point of the application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nShowCmd) {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Register the window class
    const char CLASS_NAME[] = "WhiteNoiseWindowClass";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0, CLASS_NAME, "White Noise Generator",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
        nullptr, nullptr, hInstance, nullptr
    );

    if (hwnd == nullptr) {
        return 0;
    }

    ShowWindow(hwnd, nShowCmd);

    // Set a timer to trigger every FRAME_TIME milliseconds
    SetTimer(hwnd, 1, FRAME_TIME, nullptr);

    // Main message loop
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Kill the timer before exiting
    KillTimer(hwnd, 1);

    return 0;
}

// Window procedure to handle messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        GenerateWhiteNoise(hdc); // Generate and display white noise
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_TIMER: {
        // Invalidate the window to trigger a repaint
        InvalidateRect(hwnd, nullptr, TRUE);
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Function to generate and display white noise
void GenerateWhiteNoise(HDC hdc) {
    // Create a bitmap to hold the noise
    HBITMAP hBitmap = CreateCompatibleBitmap(hdc, WIDTH, HEIGHT);
    HDC memDC = CreateCompatibleDC(hdc);
    SelectObject(memDC, hBitmap);

    // Create a buffer for the pixel data
    BITMAPINFO bmpInfo;
    ZeroMemory(&bmpInfo, sizeof(BITMAPINFO));
    bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfo.bmiHeader.biWidth = WIDTH;
    bmpInfo.bmiHeader.biHeight = -HEIGHT; // Negative to indicate a top-down bitmap
    bmpInfo.bmiHeader.biPlanes = 1;
    bmpInfo.bmiHeader.biBitCount = 32; // 32 bits for ARGB
    bmpInfo.bmiHeader.biCompression = BI_RGB;

    // Allocate memory for the pixel data
    BYTE* pixels = new BYTE[WIDTH * HEIGHT * 4]; // 4 bytes per pixel (ARGB)

    // Fill the pixel buffer with random grayscale values
    for (int i = 0; i < WIDTH * HEIGHT; ++i) {
        BYTE grayValue = static_cast<BYTE>(rand() % 256);
        pixels[i * 4 + 0] = grayValue; // Blue
        pixels[i * 4 + 1] = grayValue; // Green
        pixels[i * 4 + 2] = grayValue;
        pixels[i * 4 + 3] = 255; // Alpha (fully opaque)
    }

    // Set the pixel data to the bitmap
    SetDIBits(memDC, hBitmap, 0, HEIGHT, pixels, &bmpInfo, DIB_RGB_COLORS);

    // BitBlt to copy the bitmap to the window
    BitBlt(hdc, 0, 0, WIDTH, HEIGHT, memDC, 0, 0, SRCCOPY);

    // Clean up
    DeleteObject(hBitmap);
    DeleteDC(memDC);
    delete[] pixels; // Free the allocated pixel buffer
}
