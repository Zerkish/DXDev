#ifndef DXLIB_SIMPLEMATH_H
#define DXLIB_SIMPLEMATH_H

#include <cmath>

namespace math {

extern const float Pi;
extern const float PiOver2;
extern const float PiOver4;
extern const float TwoPi;

inline float WrapAngle(float f)
{
    if (f > Pi * 2)
        f = -Pi * 2;
    if (f < -Pi * 2)
        f = Pi * 2;
    return f;
}

inline float Lerp(float x, float y, float a)
{
    return x + (y - x) * a;
}

inline float Clamp(float x, float min, float max)
{
    x = x < min ? min : x;
    x = x > max ? max : x;
    return x;
}

inline float ToRadians(float degrees)
{
    return degrees * (Pi / 180.0f);
}

inline float ToDegrees(float radians)
{
    return radians * (180.0f / Pi);
}

} // namespace math

struct Vector2f
{
    static const Vector2f kUnitX;
    static const Vector2f kUnitY;
    static const Vector2f kZero;
    static const Vector2f kOne;

    float x, y;

    Vector2f(float nx, float ny) { x = nx; y = ny; }
    Vector2f(int nx, int ny) { x = (float)nx; y = (float)ny; }
    Vector2f() { x = y = 0.0f; }

    // Scalar product of this vector and rhs.
    inline float Dot(const Vector2f &rhs) const { return x * rhs.x + y * rhs.y; }

    // Returns length of the vector.
    inline float Length() const { return std::sqrt(x * x + y * y); }

    // Normalizes this vector.
    inline void Normalize() { float l = Length(); x = x / l; y = y / l; }

    // Returns a normalized Unitvector version of this vector.
    inline Vector2f GetUnit() const { Vector2f v = *this; v.Normalize(); return v; }

    Vector2f Reflect(const Vector2f &axis);

    Vector2f operator+=(const Vector2f &v);
    Vector2f operator-=(const Vector2f &v);
    Vector2f operator*=(const float f);
    Vector2f operator/=(const float f);
};

// Scalar multiplication.
const Vector2f operator*(const Vector2f &lhs, float c);
// Scalar division.
const Vector2f operator/(const Vector2f &lhs, float c);

// Vector addition.
const Vector2f operator+(const Vector2f &lhs, const Vector2f &rhs);

// Vector substraction.
const Vector2f operator-(const Vector2f &lhs, const Vector2f &rhs);

// Scalar vector addition.
const Vector2f operator+(const Vector2f &lhs, float c);

// Scalar vector subtraction.
const Vector2f operator-(const Vector2f &lhs, float c);


struct Vector3f
{
    static const Vector3f kUnitX;
    static const Vector3f kUnitY;
    static const Vector3f kUnitZ;
    static const Vector3f kZero;
    static const Vector3f kOne;

    float x, y, z;

    // Conversion constructor.
    Vector3f(const Vector2f &v) { x = v.x; y = v.y; z = 0.0f; }

    Vector3f(float nx, float ny, float nz) { x = nx; y = ny; z = nz; }
    Vector3f() { x = y = z = 0.0f; }

    // Scalar product.
    inline float Dot(const Vector3f &rhs) const { return x * rhs.x + y * rhs.y + z * rhs.z; }

    // Length of the vector.
    inline float Length() const {return std::sqrt(x * x + y * y + z * z); }

    // Normalizes this vector.
    inline void Normalize() { float l = Length(); x /= l; y /= l; z /= l; }

    // Returns a normalized version of this vector.
    inline Vector3f GetUnit() const { Vector3f v = *this; v.Normalize(); return v; }

    // Performs cross product between this vector and another vector.
    inline const Vector3f Cross(const Vector3f &rhs) const
    {
        return Vector3f(y * rhs.z - z * rhs.y,
                        z * rhs.x - x * rhs.z,
                        x * rhs.y - y * rhs.x);
    }

    Vector3f operator+=(const Vector3f &v);
    Vector3f operator-=(const Vector3f &v);
    Vector3f operator*=(const float f);
    Vector3f operator/=(const float f);
};

// Scalar multiplication.
const Vector3f operator*(const Vector3f &lhs, float c);

// Scalar division.
const Vector3f operator/(const Vector3f &lhs, float c);

// Vector addition.
const Vector3f operator+(const Vector3f &lhs, const Vector3f &rhs);

// Vector substraction.
const Vector3f operator-(const Vector3f &lhs, const Vector3f &rhs);

// Scalar-Vector addition.
const Vector3f operator+(const Vector3f &lhs, float c);

// Scalar vector substraction.
const Vector3f operator-(const Vector3f &lhs, float c);

struct Vector4f
{
    static const Vector4f kUnitX;
    static const Vector4f kUnitY;
    static const Vector4f kUnitZ;
    static const Vector4f kUnitW;
    static const Vector4f kZero;
    static const Vector4f kOne;

    float x, y, z, w;

    // Conversion constructor.
    Vector4f(const Vector3f &v) { x = v.x; y = v.y; z = v.z; w = 1.0f; }

    Vector4f() { x = y = z = w = 0.0f; }
    Vector4f(float nx, float ny, float nz, float nw)
        { x = nx; y = ny; z = nz; w = nw; }

    // Scalar product.
    inline float Dot(const Vector4f &rhs) const
    {
        return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
    }

    // Gets length of this vector.
    inline float Length() const
    {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    // Normalizes this vector.
    inline void Normalize()
    {
        float l = Length();
        x /= l;
        y /= l;
        z /= l;
        w /= l;
    }

    inline Vector3f Cross(const Vector4f &vec)
    {
        return Vector3f(y * vec.z - z * vec.y,
                        z * vec.x - x * vec.z,
                        x * vec.y - y * vec.x);
    }

    // Gets a normalized version of this vector.
    inline Vector4f GetUnit() const { Vector4f v = *this; v.Normalize(); return v; }

    Vector4f operator+=(const Vector4f &v);
    Vector4f operator-=(const Vector4f &v);
    Vector4f operator*=(const float f);
    Vector4f operator/=(const float f);
};

// Scalar multiplication.
inline const Vector4f operator*(const Vector4f &lhs, float c);
inline const Vector4f operator*(float c, const Vector4f &rhs);

// Scalar division.
inline const Vector4f operator/(const Vector4f &lhs, float c);

// Vector-scalar addition.
inline const Vector4f operator+(const Vector4f &lhs, float c);

// Vector-scalar substraction.
inline const Vector4f operator-(const Vector4f &lhs, float c);

// Vector addition.
inline const Vector4f operator+(const Vector4f &lhs, const Vector4f &rhs);

// Vector substraction.
inline const Vector4f operator-(const Vector4f &lhs, const Vector4f &rhs);

// Matrix class.
struct Mat4x4 {
    static const Mat4x4 kIdentity;
    float m[4][4];

    // Defaults to an identity matrix.
    Mat4x4() {
        m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
        m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
    }

	Vector3f GetPosition() const;

    // Returns a translation matrix.
    static Mat4x4 CreateTranslation(float x, float y, float z);
    static Mat4x4 CreateTranslation(const Vector3f &v);
    static Mat4x4 CreateTranslation(const Vector4f &v);

    // Creates a matrix that can have different scales on x, y & z.
    static Mat4x4 CreateScale(float sx, float sy, float sz);

    // Creates a uniform scale matrix.
    static Mat4x4 CreateScale(float s);

    static Mat4x4 CreateRotationAxis(const Vector3f &axis, float theta);

    static Mat4x4 CreateRotationX(float theta);

    static Mat4x4 CreateRotationY(float theta);

    static Mat4x4 CreateRotationZ(float theta);

    // Creates a view matrix from camera position, target and up vectors.
    static Mat4x4 CreateLookAt(const Vector3f &eyePos,
        const Vector3f &target , const Vector3f &up);

    // Creates the perspective projection matrix from
    static Mat4x4 CreatePerspectiveFovRH(float fov, float aspect,
        float zNear, float zFar);

    Mat4x4 Transpose() const;

    float Determinant() const;

    // Returns the inverse matrix.
    Mat4x4 Inverse() const;


    // Transforms a 4D Vector by this matrix.
    Vector4f Transform(const Vector4f &vec) const;

    // Pointer version, in case the old vector isn't needed.
    void Transform(Vector4f *pVec) const;

    // Transforms a 3D vector by this matrix.
    Vector3f Transform(const Vector3f &vec) const;

    void Transform(Vector3f *pVec) const;
};

// Matrix multiplication.
const Mat4x4 operator*(const Mat4x4 &lhs, const Mat4x4 &rhs);

// Matrix scalar multiplication.
const Mat4x4 operator*(const Mat4x4 &lhs, float c);

const Mat4x4 operator*(float c, const Mat4x4 &rhs);

// matrix scalar division.
const Mat4x4 operator/(const Mat4x4 &lhs, float c);

struct RectangleI {
	int x, y, w, h;
	RectangleI(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) { }
	RectangleI() { x = y = w = h = 0; }
};

struct RectangleF {
	float x, y, w, h;
	RectangleF(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) { }
    RectangleF(const Vector2f &min, const Vector2f &max)
        : x(min.x), y(min.y), w(max.x - min.x), h(max.y - min.y) { }
	RectangleF() { x = y = w = h = 0.0f; }

    bool Intersects(const RectangleF &r) const {
        if (x > (r.x + r.w)) return false;
        if (y > (r.y + r.h)) return false;
        if (r.x > (x + w)) return false;
        if (r.y > (y + h)) return false;
        return true;
    }
};

#include "SimpleMath.inl"

#endif // !DXLIB_SIMPLEMATH_H