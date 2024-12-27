#include <windows.h>
#include <ctime>   // For std::time
#include <vector>  // For std::vector
#include <random>  // For std::mt19937 and std::uniform_int_distribution

// Constants for window dimensions
const int WIDTH = 1920;
const int HEIGHT = 1080;
const int FRAME_RATE = 60;
const int FRAME_TIME = 1000 / FRAME_RATE; // Frame time in milliseconds

// Function declarations
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void GenerateWhiteNoise(HDC hdc, HBITMAP hBitmap, BYTE* pixels);

// Entry point of the application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nShowCmd) {
    // Seed the random number generator with Mersenne Twister
    std::random_device rd; // Obtain a random number from hardware
    std::mt19937 mt(rd()); // Seed the generator
    std::uniform_int_distribution<int> dist(0, 255); // Distribution in range [0, 255]

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
    static HBITMAP hBitmap = nullptr;
    static std::vector<BYTE> pixels(WIDTH * HEIGHT * 4); // Buffer for pixel data
    static std::random_device rd; // Obtain a random number from hardware
    static std::mt19937 mt(rd()); // Seed the generator
    static std::uniform_int_distribution<int> dist(0, 255); // Distribution in range [0, 255]

    switch (uMsg) {
    case WM_CREATE:
        // Create a bitmap once
        hBitmap = CreateCompatibleBitmap(GetDC(hwnd), WIDTH, HEIGHT);
        return 0;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        GenerateWhiteNoise(hdc, hBitmap, pixels.data()); // Generate and display white noise
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_TIMER: {
        // Invalidate the window to trigger a repaint
        InvalidateRect(hwnd, nullptr, TRUE);
        return 0;
    }
    case WM_DESTROY:
        DeleteObject(hBitmap); // Clean up bitmap
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Function to generate and display white noise
void GenerateWhiteNoise(HDC hdc, HBITMAP hBitmap, BYTE* pixels) {
    // Fill the pixel buffer with random grayscale values
    for (int i = 0; i < WIDTH * HEIGHT; ++i) {
        BYTE grayValue = static_cast<BYTE>(rand() % 256); // Replace this with Mersenne Twister
        pixels[i * 4 + 0] = grayValue; // Blue
        pixels[i * 4 + 1] = grayValue; // Green
        pixels[i * 4 + 2] = grayValue; // Red
        pixels[i * 4 + 3] = 255; // Alpha (fully opaque
    }

    // Create a memory device context
    HDC memDC = CreateCompatibleDC(hdc);
    SelectObject(memDC, hBitmap);

    // Create a BITMAPINFO structure for the bitmap
    BITMAPINFO bmpInfo;
    ZeroMemory(&bmpInfo, sizeof(BITMAPINFO));
    bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfo.bmiHeader.biWidth = WIDTH;
    bmpInfo.bmiHeader.biHeight = -HEIGHT; // Negative to indicate a top-down bitmap
    bmpInfo.bmiHeader.biPlanes = 1;
    bmpInfo.bmiHeader.biBitCount = 32; // 32 bits for ARGB
    bmpInfo.bmiHeader.biCompression = BI_RGB;

    // Set the pixel data to the bitmap
    SetDIBits(memDC, hBitmap, 0, HEIGHT, pixels, &bmpInfo, DIB_RGB_COLORS);

    // BitBlt to copy the bitmap to the window
    BitBlt(hdc, 0, 0, WIDTH, HEIGHT, memDC, 0, 0, SRCCOPY);

    // Clean up
    DeleteDC(memDC); // Clean up the memory device context
}
