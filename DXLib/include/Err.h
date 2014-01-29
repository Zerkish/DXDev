#ifndef DXLIB_DXLIBERR_H
#define DXLIB_DXLIBERR_H

namespace dx {
    namespace Error {
        enum E {
            OK = 0,

            // Attempt to register the DX_WINDOW_CLASS when RegisterClass had already been called.
            WINDOW_CLASS_ALREADY_REGISTERED = 1,

            // Failed to register WindowClass (Never seen this happen).
            WINDOW_CLASS_REG_FAIL,
            
            // CreateWindowEx failed.
            WINDOW_CREATE_FAIL,

            // Initialize() was called on an initialized dx::Window.
            WINDOW_ALREADY_CREATED,

            // Generic renderer initialization failure.
            RENDER_INIT_FAIL,

            // FeatureLevel too low
            RENDER_FEATURE_LEVEL_TOO_LOW,

            // Standard render format not supported
            RENDER_FORMAT_NOT_SUPPORTED,
        };
    } // namespace error
} // namespace dx

#endif // !DXLIB_DXLIBERR_H