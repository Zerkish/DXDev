#ifndef APPLICATION_H
#define APPLICATION_H

#include <DXLib.h>

class Application : public dx::DXApp {
public:
    Application();
    ~Application();

protected:
    void OnInitialize(dx::RenderSystem &r) override;
    void OnUpdate(const dx::Timer &timer) override;
    void OnRender(dx::RenderSystem &r, const dx::Timer &timer) override;

    void OnClose() override;
private:

};

#endif // !APPLICATION_H