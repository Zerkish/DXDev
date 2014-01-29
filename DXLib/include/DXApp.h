#ifndef DXLIB_DXAPP_H
#define DXLIB_DXAPP_H

#include "Window.h"
#include "Timer.h"
#include "RenderSystem.h"

namespace dx {

class DXApp : public Window {
public:
    DXApp(UINT width, UINT height, const std::string &title);
    virtual ~DXApp();

    Error::E Initialize();
    
    // Blocks until application closes.
    void Run();

protected:
    virtual void OnInitialize(RenderSystem &r) = 0;
    virtual void OnUpdate(const Timer &timer) = 0;
    virtual void OnRender(RenderSystem &r, const Timer &timer) = 0;

    inline int GetCurrentFPS() const { return (int)_fps; }
    inline float GetCurrentTPF() const { return 1.0f / _fps; }

    void Quit();
private:
    void CalculateFPS();

    // Measures total runtime.
    Timer _appTimer;
    bool _isRunning;
    RenderSystem _renderer;

    int _frames;
    int _lastFrames;
    double _frameTime;
    float _fps;
};

} // namespace dx
#endif // !DXLIB_DXAPP_H