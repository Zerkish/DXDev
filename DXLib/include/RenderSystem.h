#ifndef DXLIB_RENDERER_H
#define DXLIB_RENDERER_H

#include "Defs.h"
#include "Window.h"
#include "SimpleMath.h"

#include <d3d11.h>


namespace dx {

class RenderSystem {
public:
    RenderSystem();
    ~RenderSystem();

    Error::E Initialize(const Window &window);

    void Clear(const Vector4f &color);
    void Present();

private:
    NO_COPY_ASSIGN(RenderSystem);

    void FreeResources();
    Error::E CreateDeviceAndContext();
    Error::E CreateSwapChain(const Window &window);
    Error::E CreateDepthStencilBuffer();
    bool _initOk;

    DXGI_SWAP_CHAIN_DESC _swapDesc;
    D3D_FEATURE_LEVEL _featureLevel;
    UINT _msaaQualityLevel;

    ID3D11Device *_device;
    ID3D11DeviceContext *_context;
    IDXGISwapChain *_swapChain;

    ID3D11RenderTargetView *_renderTargetView;
    ID3D11DepthStencilView *_depthStencilView;
};

} // namespace dx
#endif // !DXLIB_RENDERER_H