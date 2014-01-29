#ifndef DXLIB_WINDOW_H
#define DXLIB_WINDOW_H

#include "Defs.h"
#include "Err.h"

#include <Windows.h>

#include <string>

namespace dx {

class Window {
public:
    Window(UINT width, UINT height, const std::string &title,
        HINSTANCE hInstance = NULL);
    virtual ~Window();

    // Creates the actual window, gives the user a chance to
    // handle any errors upon creation.
    Error::E Initialize();

    bool IsVisible() const;
    void SetVisible(bool value);

    // Returns dimensions of CLIENT area.
    UINT GetWidth() const;
    UINT GetHeight() const;

    // Returns Dimensions of WINDOW area.
    UINT GetRealWidth() const;
    UINT GetRealHeight() const;

    // Set the size of the client area.
    void SetSize(UINT nWidth, UINT nHeight);

    std::string GetTitle() const;
    void SetTitle(const std::string &str);

    // Polls all windows messages and handles them.
    void HandleMessages();

    // Set to true when the user attempts to close the window.
    bool IsCloseRequested() const;

    // Returns the handle to the native window.
    HWND GetHandle() const;

protected:
    // Events that get sent down to derived classes.
    virtual void OnClose() { };
    virtual void OnGainFocus() { }
    virtual void OnLostFocus() { }
    virtual void OnMinimize() { }
    virtual void OnMaximize() { }

private:
    NO_COPY_ASSIGN(Window);

    // Used to delegate to member version.
    static LRESULT CALLBACK StaticWinProc(HWND, UINT, WPARAM, LPARAM);
    static Error::E RegisterDXClass(HINSTANCE);
    static WNDCLASS _wndClass;
    static bool _isClassReg;
    static const char *_kClassName;
    static const DWORD _kWindowStyles;

    LRESULT WindowProc(HWND, UINT, WPARAM, LPARAM);
    Error::E InitWindow();

    // Window members
    HWND _hwnd;
    HINSTANCE _hInst;
    std::string _title;
    UINT _width;
    UINT _height;
    bool _shouldClose; // TODO : Some way to reset this flag.
};

} // namespace dx
#endif // !DXLIB_DXWINDOW_H