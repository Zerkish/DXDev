#include <RenderSystem.h>
#include "Util.h"

#include <cassert>

static const UINT kDefaultWidth = 640;
static const UINT kDefaultHeight = 480;
static const DXGI_FORMAT kDefaultFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

IDXGIFactory* FactoryFromDevice(ID3D11Device *device);

// Default swapchain desc that has sane values for all parameters.
// New modes are created by copying this and changing specific settings.
static const DXGI_SWAP_CHAIN_DESC kDefaultSwapDesc = {
    /* DXGI_MODE_DESC */ {
        kDefaultWidth,
        kDefaultHeight,
        /* Refresh */ {
            60, // Numerator
            1   // Denominator
        },
        kDefaultFormat,
        DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
        DXGI_MODE_SCALING_UNSPECIFIED
    },
    /* DXGI_SAMPLE_DESC */ {
        1, // SampleCount
        0, // QualityLevel
    },
    DXGI_USAGE_RENDER_TARGET_OUTPUT,
    1, // Number of Buffers
    NULL, // Window Handle
    TRUE, // Window-mode
    DXGI_SWAP_EFFECT_DISCARD,
    0 // Flags
};

// Featurelevels we're interested in.
static const D3D_FEATURE_LEVEL kFeatureLevels[] = {
    D3D_FEATURE_LEVEL_11_0,
    D3D_FEATURE_LEVEL_10_1,
    D3D_FEATURE_LEVEL_10_0,
    D3D_FEATURE_LEVEL_9_3,
};

namespace dx {

RenderSystem::RenderSystem() {
    _initOk = false;
    _device = nullptr;
    _context = nullptr;
    _swapChain = nullptr;
    _renderTargetView = nullptr;
    _depthStencilView = nullptr;
}

RenderSystem::~RenderSystem() {
    if (_initOk) {
        if (_context) {
            _context->ClearState();
        }
        FreeResources();
    }
}

Error::E RenderSystem::Initialize(const Window &window) {
    Error::E err = Error::OK;
    err = CreateDeviceAndContext();

    if (err != Error::OK) {
        FreeResources();
        return err;
    }

    err = CreateSwapChain(window);

    if (err != Error::OK) {
        FreeResources();
        return err;        
    }

    ID3D11Texture2D *backBuffer;
    DEBUG_HR(_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
    DEBUG_HR(_device->CreateRenderTargetView(backBuffer, NULL, &_renderTargetView));
    ReleaseCom(backBuffer);

    err = CreateDepthStencilBuffer();

    if (err != Error::OK) {
        FreeResources();
        return err;
    }

    _context->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);

    D3D11_VIEWPORT vp;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.Width = (float)window.GetWidth();
    vp.Height = (float)window.GetHeight();
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;

    _context->RSSetViewports(1, &vp);

    _initOk = true;
    return Error::OK;
}

void RenderSystem::Clear(const Vector4f &color) {
    _context->ClearRenderTargetView(_renderTargetView, reinterpret_cast<const float*>(&color));
    _context->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 0.0f, 0);
}

void RenderSystem::Present() {
    DEBUG_HR(_swapChain->Present(0, 0));
}

void RenderSystem::FreeResources() {
    ReleaseCom(_depthStencilView);
    ReleaseCom(_swapChain);
    ReleaseCom(_renderTargetView);
    ReleaseCom(_device);
    ReleaseCom(_context);    
}

Error::E RenderSystem::CreateDeviceAndContext() {
    assert(!_device);
    UINT flags = D3D11_CREATE_DEVICE_SINGLETHREADED;
    
#if defined(DEBUG) | defined(_DEBUG)
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif 

    DEBUG_HR(D3D11CreateDevice(
        NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        flags,
        kFeatureLevels,
        ARRAY_SIZE(kFeatureLevels),
        D3D11_SDK_VERSION,
        &_device,
        &_featureLevel,
        &_context
    ));

    if (_featureLevel != D3D_FEATURE_LEVEL_11_0) {
        return Error::RENDER_FEATURE_LEVEL_TOO_LOW;
    }

    UINT formatSupport;
    DEBUG_HR(_device->CheckFormatSupport(kDefaultFormat, &formatSupport));

    if (!(formatSupport & D3D11_FORMAT_SUPPORT_BUFFER)) {
        return Error::RENDER_FORMAT_NOT_SUPPORTED;
    }

    DEBUG_HR(_device->CheckMultisampleQualityLevels(kDefaultFormat, 4, &_msaaQualityLevel));
    assert(_msaaQualityLevel > 0);

    return Error::OK;
}

Error::E RenderSystem::CreateSwapChain(const Window &window) {
    assert(_device);
     _swapDesc = kDefaultSwapDesc;

    _swapDesc.SampleDesc.Count = 4;
    _swapDesc.SampleDesc.Quality = _msaaQualityLevel - 1;
    _swapDesc.OutputWindow = window.GetHandle();
    _swapDesc.BufferDesc.Width = window.GetWidth();
    _swapDesc.BufferDesc.Height = window.GetHeight();

    IDXGIFactory *factory = FactoryFromDevice(_device);

    DEBUG_HR(factory->CreateSwapChain(_device, &_swapDesc, &_swapChain));
    ReleaseCom(factory);
    return Error::OK;
}

Error::E RenderSystem::CreateDepthStencilBuffer() {
    D3D11_TEXTURE2D_DESC bd;
    bd.Width = _swapDesc.BufferDesc.Width;
    bd.Height = _swapDesc.BufferDesc.Height;
    bd.MipLevels = 1;
    bd.ArraySize = 1;
    bd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    bd.SampleDesc = _swapDesc.SampleDesc;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags  = 0;

    ID3D11Texture2D *buffer;
    DEBUG_HR(_device->CreateTexture2D(&bd, NULL, &buffer));
    DEBUG_HR(_device->CreateDepthStencilView(buffer, 0, &_depthStencilView));
    ReleaseCom(buffer);

    return Error::OK;
}

} // namespace dx

static IDXGIFactory* FactoryFromDevice(ID3D11Device *device) {
    assert(device);

    IDXGIDevice *dxgiDevice = nullptr;
    DEBUG_HR(device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice)));

    IDXGIAdapter *dxgiAdapter = nullptr;
    DEBUG_HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&dxgiAdapter)));

    IDXGIFactory *dxgiFactory = nullptr;
    DEBUG_HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&dxgiFactory)));

    ReleaseCom(dxgiAdapter);
    ReleaseCom(dxgiDevice);
    return dxgiFactory;
}