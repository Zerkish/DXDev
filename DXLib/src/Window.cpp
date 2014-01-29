#include "Window.h"

#include <cassert>

#define ASSERT_HWND assert(_hwnd && "Window not created")

// Forward declarations
void CalculateClientSize(DWORD styles, UINT &width, UINT &height);

namespace dx {

// Class Variables.
const char *Window::_kClassName = "DX_WINDOW_CLASS";
WNDCLASS Window::_wndClass = { };
bool Window::_isClassReg = false;
const DWORD Window::_kWindowStyles = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;

// Constructor, hInstance has a default argument of 0.
Window::Window(UINT width, UINT height, const std::string &title,
               HINSTANCE hInstance) {
    _hInst = (hInstance == NULL) ? GetModuleHandle(NULL) : hInstance;

    _title = title;
    _hwnd = 0;
    _width = width;
    _height = height;
    _shouldClose = false;
}

// Destructor
Window::~Window() {
    if (_hwnd != 0)
        DestroyWindow(_hwnd);
}

// Responsible for creating the actual window, since we don't use exceptions
// we need to be able to return error codes.
Error::E Window::Initialize() {
    // Make sure initialize is only called once.
    assert(_hwnd == NULL);
    //if (_hwnd != NULL) return Error::WINDOW_ALREADY_CREATED;

    if (!_isClassReg) {
        Error::E err = RegisterDXClass(_hInst);
        if (err != Error::OK) return err;
    }

    return InitWindow();
}

bool Window::IsVisible() const {
    ASSERT_HWND;

    // Avoid performance warning about bool conversion.
    return IsWindowVisible(_hwnd) == TRUE;
}

void Window::SetVisible(bool value) {
    ASSERT_HWND;
    ShowWindow(_hwnd, static_cast<int>(value));
}

UINT Window::GetWidth() const {
    return _width;
}

UINT Window::GetHeight() const {
    return _height;
}

// Returns size of the actual window, including borders.
UINT Window::GetRealWidth() const {
    UINT w = _width, h = _height;
    CalculateClientSize(_kWindowStyles, w, h);
    return w;
}

// Returns size of the actual window, including borders.
UINT Window::GetRealHeight() const {
    UINT w = _width, h = _height;
    CalculateClientSize(_kWindowStyles, w, h);
    return h;
}

// Sets the size of the client area.
void Window::SetSize(UINT nWidth, UINT nHeight) {
    _width = nWidth;
    _height = nHeight;

    CalculateClientSize(_kWindowStyles, _width, _height);
    SetWindowPos(_hwnd, NULL, 0, 0, _width, _height, SWP_NOMOVE);
}

std::string Window::GetTitle() const {
    return _title;
}

void Window::SetTitle(const std::string &str) {
    ASSERT_HWND;
    SetWindowText(_hwnd, str.c_str());
}

// Standard message pump.
void Window::HandleMessages() {
    MSG msg = { 0 };
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

bool Window::IsCloseRequested() const {
    return _shouldClose;
}

HWND Window::GetHandle() const {
    ASSERT_HWND;
    return _hwnd;
}

// Static, registers the class used by all dx::Window instances.
Error::E Window::RegisterDXClass(HINSTANCE hInst) {
    assert(!_isClassReg && "Class already registered.");
    
    memset(&_wndClass, 0, sizeof(WNDCLASS));
    _wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    _wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    _wndClass.hInstance = hInst;
    _wndClass.lpfnWndProc = &StaticWinProc;
    _wndClass.lpszClassName = _kClassName;
    
    if (!RegisterClass(&_wndClass)) return Error::WINDOW_CLASS_REG_FAIL;

    _isClassReg = true;
    return Error::OK;
}

// Static Window Procedure, used to delegate calls to member method.
LRESULT Window::StaticWinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_CREATE) {
        Window *window = reinterpret_cast<Window*>(((LPCREATESTRUCT)lParam)->lpCreateParams);
        assert(window && "No window pointer in LPARAM");
        SetWindowLong(hwnd, GWL_USERDATA, (LONG)window);
    }

    Window *window = reinterpret_cast<Window*>(GetWindowLong(hwnd, GWL_USERDATA));

    if (window) {
        return window->WindowProc(hwnd, msg, wParam, lParam);
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

Error::E Window::InitWindow() {
    // Adjust window size to fit a client rectangle of [width, height] dimensions.
    UINT w = _width, h = _height;
    CalculateClientSize(_kWindowStyles, w, h);

    _hwnd = CreateWindowEx(
        NULL,
        _kClassName,
        _title.c_str(),
        _kWindowStyles,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        w,
        h,
        NULL,
        NULL,
        _hInst,
        this
    );

    return (_hwnd == NULL) ? Error::WINDOW_CREATE_FAIL : Error::OK;

}

LRESULT Window::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg) {
    case WM_DESTROY:
        OnClose();
        _shouldClose = true;
        break;
    case WM_ACTIVATE:
        if (wParam == WA_INACTIVE) OnGainFocus();
        else OnLostFocus();
        break;
    case WM_SIZE:
        if (wParam & SIZE_MAXIMIZED)
            OnMaximize();
        else if (wParam & SIZE_MINIMIZED)
            OnMinimize();

        break;
    }


    return DefWindowProc(hwnd, msg, wParam, lParam);
}

} // namespace dx

// Adjusts width and height to give the proper sizes using certain window styles.
static void CalculateClientSize(DWORD styles, UINT &width, UINT &height) {
    RECT r = { 0, 0, width, height };
    AdjustWindowRect(&r, styles, false);
    width = r.right - r.left;
    height = r.bottom - r.top;
}