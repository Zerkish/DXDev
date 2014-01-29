#include <DXApp.h>

namespace dx {

DXApp::DXApp(UINT width, UINT height, const std::string &title) 
 : Window(width, height, title) {

}

DXApp::~DXApp() {

}

Error::E DXApp::Initialize() {
    Error::E err = Window::Initialize();
    if (err != Error::OK) return err;

    err = _renderer.Initialize(*this);

    if (err != Error::OK) return err;

    return Error::OK;
}

void DXApp::Run() {
    Window::SetVisible(true);
    
    _isRunning = true;

    _appTimer.Start();

    _frameTime = 0;
    _frames = _lastFrames = 0;

    while (_isRunning) {
        _appTimer.Tick();
        CalculateFPS();
        
        // Handle Windows messages.
        HandleMessages();

        OnUpdate(_appTimer);
        _renderer.Clear(Vector4f::kZero);
        OnRender(_renderer, _appTimer);
        _renderer.Present();
    }
}

void DXApp::Quit() {
    _isRunning = false;
}

void DXApp::CalculateFPS() {
    ++_frames;
    _frameTime += _appTimer.GetDeltaSeconds();

    if (_frameTime >= 1.0) {
        _lastFrames = _frames;
        _frames = 0;
        _frameTime = 0.0;
    }

    _fps = static_cast<float>(_frames +_lastFrames * (1.0 - _frameTime));

}

} // namespace dx