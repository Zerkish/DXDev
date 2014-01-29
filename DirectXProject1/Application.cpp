#include "Application.h"

Application::Application() : dx::DXApp(800, 600, "DirectXProject1") {

}

Application::~Application() {

}

void Application::OnInitialize(dx::RenderSystem &r) {

}

void Application::OnUpdate(const dx::Timer &timer) {
    SetTitle(std::string("DirectXProject1  FPS:") + std::to_string(GetCurrentFPS()));
}

void Application::OnRender(dx::RenderSystem &r, const dx::Timer &timer) {

}

void Application::OnClose() {
    DXApp::Quit();
}