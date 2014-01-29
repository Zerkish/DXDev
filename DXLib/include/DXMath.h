#ifndef DXLIB_DXMATH_H
#define DXLIB_DXMATH_H


#include <DirectXMath.h>
#include <cmath>

// Inlined methods and classes related to 
#include <RadDeg.inl>

namespace dx {

extern const float Pi;
extern const float PiOver2;
extern const float PiOver3;
extern const float PiOver4;
extern const float PiOver180;
extern const float TwoPi;


// Checks if *value* is within *delta* of *mark*.
template<typename N>
inline bool InRange(const N &value, const N &mark, const N &delta) {
    return value > (mark - delta) &&
           value < (mark + delta);
}

// Compares floats within precision of FLT_EPSILON
inline bool FloatEquals(float f1, float f2) {
    return fabsf(f1 - f2) < FLT_EPSILON;
}

inline bool operator== (const Radians &r1, const Radians &r2) {
    return FloatEquals(r1._value, r2._value);
}

inline bool operator== (const Radians &r, float f) {
    return FloatEquals(r._value, f);
}

inline bool operator== (float f, const Radians &r) {
    return r == f;
}

inline Degrees ToDegrees(const Radians &r) {
    return Degrees(r._value / PiOver180);
}

inline Radians ToRadians(const Degrees &d) {
    return Radians(d._value * PiOver180);
}

struct Vector2 {
    static const Vector2 Zero;
    static const Vector2 One;
    static const Vector2 UnitX;
    static const Vector2 UnitY;
    
    float x, y;
    static const Vector2 Normalize(const Vector2 &);
    static float Dot(const Vector2 &, const Vector2 &v);


    Vector2(float x, float y) : x(x), y(y) { }
    Vector2() : x(0.0f), y(0.0f) { }

    // Normalizes this vector
    void Normalize();

    float Length() const;
    float LengthSquared() const;

    float Dot(const Vector2 &) const;
    
    const Vector2 operator+ (const Vector2 &) const;
    const Vector2 operator- (const Vector2 &) const;
    const Vector2 operator* (const float) const;
    const Vector2 operator/ (const float) const;

    const Vector2& operator+= (const Vector2 &);
    const Vector2& operator-= (const Vector2 &);
    const Vector2& operator*= (const float);
    const Vector2& operator/= (const float);
   
};


//#include "DXMath.inl"

} // namespace dx
#endif // !DXLIB_DXMATH_H