#include <iostream>
#include <Windows.h>

#include "Application.h"
#include <DirectXMath.h>
#include <DXMath.h>

void SIMDTest() {
    _declspec(align(16)) float numbers[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    _declspec(align(16)) float numbers2[4] = { 1.0f, -1.0f, 1.0f, -1.0f };


    // Load arrays to SSE registers
    __m128 v1 = _mm_load_ps(numbers);
    __m128 v2 = _mm_load_ps(numbers2);

    // Add registers v1, v2, and store into v2.
    v2 = _mm_add_ps(v1, v2);

    // Store the result into numbers array.
    _mm_store_ps(numbers, v2);

    std::cout << numbers[0] << std::endl
              << numbers[1] << std::endl
              << numbers[2] << std::endl
              << numbers[3] << std::endl;
}

int main() {
    Application app;
    if (app.Initialize() != dx::Error::OK) {
        std::cout << "Initialization failure!" << std::endl;
    }
    app.Run();
    
#if defined(_DEBUG) | defined(DEBUG)
    system("PAUSE");
#endif
    return 0;
}
