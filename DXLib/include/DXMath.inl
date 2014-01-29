#ifndef DXLIB_DXMATH_INL
#define DXLIB_DXMATH_INL


#include <DXMath.h>
#include <DirectXMath.h>

namespace dx {

inline const Vector2 Vector2::Normalize(const Vector2 &v) {
    float len = v.Length();
    return Vector2(v.x / len, v.y / len);
}

inline float Vector2::Dot(const Vector2 &v1, const Vector2 &v2) {
    _declspec(align(16)) float n1[] = { v1.x, v1.y };
    _declspec(align(16)) float n2[] = { v2.x, v2.y };

}


} // namespace dx
#endif // !DXLIB_DXMATH_INL