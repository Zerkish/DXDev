#include "SimpleMath.h"


/////////////////////////////
// VECTOR 2 /////////////////
/////////////////////////////

inline Vector2f Vector2f::Reflect(const Vector2f &axis) {
        return (*this) - axis * (axis.Dot(*this) * 2);
}

inline Vector2f Vector2f::operator+=(const Vector2f &v) {
    *this = *this + v;
    return *this;
}

inline Vector2f Vector2f::operator-=(const Vector2f &v) {
    *this = *this - v;
    return *this;
}

inline Vector2f Vector2f::operator*=(const float f) {
    *this = *this * f;
    return *this;
}

inline Vector2f Vector2f::operator/=(const float f) {
    *this = *this / f;
    return *this;
}

// Scalar multiplication.
inline const Vector2f operator*(const Vector2f &lhs, float c) {
    return Vector2f(lhs.x * c, lhs.y * c);
}

// Scalar division.
inline const Vector2f operator/(const Vector2f &lhs, float c) {
    return lhs * (1.0f / c);
}

// Vector addition.
inline const Vector2f operator+(const Vector2f &lhs, const Vector2f &rhs) {
    return Vector2f(lhs.x + rhs.x, lhs.y + rhs.y);
}

// Vector substraction.
inline const Vector2f operator-(const Vector2f &lhs, const Vector2f &rhs) {
    return Vector2f(lhs.x - rhs.x, lhs.y - rhs.y);
}

// Scalar vector addition.
inline const Vector2f operator+(const Vector2f &lhs, float c) {
    return Vector2f(lhs.x + c, lhs.y + c);
}

// Scalar vector subtraction.
inline const Vector2f operator-(const Vector2f &lhs, float c) {
    return lhs + (-c);
}


/////////////////////////////
// VECTOR 3 /////////////////
/////////////////////////////


inline Vector3f Vector3f::operator+=(const Vector3f &v) {
    *this = *this + v;
    return *this;
}

inline Vector3f Vector3f::operator-=(const Vector3f &v) {
    *this = *this - v;
    return *this;
}

inline Vector3f Vector3f::operator*=(const float f) {
    *this = *this * f;
    return *this;
}

inline Vector3f Vector3f::operator/=(const float f) {
    *this = *this / f;
    return *this;
}

// Scalar multiplication.
inline const Vector3f operator*(const Vector3f &lhs, float c) {
    return Vector3f(lhs.x * c, lhs.y * c, lhs.z * c);
}

// Scalar division.
inline const Vector3f operator/(const Vector3f &lhs, float c) {
    return lhs * (1.0f / c);
}

// Vector addition.
inline const Vector3f operator+(const Vector3f &lhs, const Vector3f &rhs) {
    return Vector3f(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

// Vector substraction.
inline const Vector3f operator-(const Vector3f &lhs, const Vector3f &rhs) {
    return Vector3f(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

// Scalar-Vector addition.
inline const Vector3f operator+(const Vector3f &lhs, float c) {
    return Vector3f(lhs.x + c, lhs.y + c, lhs.z + c);
}

// Scalar vector substraction.
inline const Vector3f operator-(const Vector3f &lhs, float c) {
    return lhs + (-c);
}

/////////////////////////////
// VECTOR 4 /////////////////
/////////////////////////////

inline Vector4f Vector4f::operator+=(const Vector4f &v) {
    *this = *this + v;
    return *this;
}

inline Vector4f Vector4f::operator-=(const Vector4f &v) {
    *this = *this - v;
    return *this;
}

inline Vector4f Vector4f::operator*=(const float f) {
    *this = *this * f;
    return *this;
}

inline Vector4f Vector4f::operator/=(const float f) {
    *this = *this / f;
    return *this;
}

// Scalar multiplication.
inline const Vector4f operator*(const Vector4f &lhs, float c) {
    return Vector4f(lhs.x * c, lhs.y * c, lhs.z * c, lhs.w * c);
}
inline const Vector4f operator*(float c, const Vector4f &rhs) {
    return rhs * c;
}

// Scalar division.
inline const Vector4f operator/(const Vector4f &lhs, float c) {
    return lhs * (1.0f / c);
}

// Vector-scalar addition.
inline const Vector4f operator+(const Vector4f &lhs, float c) {
    return Vector4f(lhs.x + c, lhs.y + c, lhs.z + c, lhs.w + c);
}

// Vector-scalar substraction.
inline const Vector4f operator-(const Vector4f &lhs, float c) {
    return lhs + (-c);
}

// Vector addition.
inline const Vector4f operator+(const Vector4f &lhs, const Vector4f &rhs) {
    return Vector4f(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

// Vector substraction.
inline const Vector4f operator-(const Vector4f &lhs, const Vector4f &rhs) {
    return Vector4f(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

/////////////////////////////
// MAT4X4 ///////////////////
/////////////////////////////

inline Mat4x4 Mat4x4::CreateTranslation(float x, float y, float z) {
    Mat4x4 m;
    m.m[3][0] = x;
    m.m[3][1] = y;
    m.m[3][2] = z;
    return m;
}

inline Mat4x4 Mat4x4::CreateTranslation(const Vector3f &v) {
    return CreateTranslation(v.x, v.y, v.z);
}

inline Mat4x4 Mat4x4::CreateTranslation(const Vector4f &v) {
    return CreateTranslation(v.x, v.y, v.z);
}

// Creates a matrix that can have different scales on x, y & z.
inline Mat4x4 Mat4x4::CreateScale(float sx, float sy, float sz) {
    Mat4x4 m;
    m.m[0][0] = sx;
    m.m[1][1] = sy;
    m.m[2][2] = sz;
    return m;
}

// Creates a uniform scale matrix.
inline Mat4x4 Mat4x4::CreateScale(float s) {
    Mat4x4 m;
    m.m[0][0] = m.m[1][1] = m.m[2][2] = s;
    return m;
}

inline Mat4x4 Mat4x4::CreateRotationAxis(const Vector3f &axis, float theta) {
    Mat4x4 m;
    float c = std::cos(theta);
    float s = std::sin(theta);
    m.m[0][0] = c + (1.0f - c) * axis.x * axis.x;
    m.m[0][1] = (1.0f - c) * axis.x * axis.y + s * axis.z;
    m.m[0][2] = (1.0f - c) * axis.x * axis.z - s * axis.y;
    m.m[0][3] = 0.0f;

    m.m[1][0] = (1 - c) * axis.x * axis.y - s * axis.z;
    m.m[1][1] = c + (1 - c) * axis.y * axis.y;
    m.m[1][2] = (1 - c) * axis.y * axis.z + s * axis.x;
    m.m[1][3] = 0.0f;

    m.m[2][0] = (1 - c) * axis.x * axis.z + s * axis.y;
    m.m[2][1] = (1 - c) * axis.y * axis.z - s * axis.x;
    m.m[2][2] = c + (1 - c) * axis.z * axis.z;
    m.m[2][3] = 0.0f;

    m.m[3][0] = m.m[3][1] = m.m[3][2] = 0.0f;
    m.m[3][3] = 1.0f;

    return m;
}

inline Vector3f Mat4x4::GetPosition() const {
	return Vector3f(m[3][0], m[3][1], m[3][2]);
}

inline Mat4x4 Mat4x4::CreateRotationX(float theta) {
    return CreateRotationAxis(Vector3f(1.0f, 0, 0), theta);
}

inline Mat4x4 Mat4x4::CreateRotationY(float theta) {
    return CreateRotationAxis(Vector3f(0, 1.0f, 0), theta);
}

inline Mat4x4 Mat4x4::CreateRotationZ(float theta) {
    return CreateRotationAxis(Vector3f(0, 0, 1.0f), theta);
}

inline Mat4x4 Mat4x4::CreateLookAt(const Vector3f &eyePos,
        const Vector3f &target , const Vector3f &up) {
    Vector3f zAxis = (eyePos - target).GetUnit();
    Vector3f xAxis = up.Cross(zAxis).GetUnit();
    Vector3f yAxis = zAxis.Cross(xAxis);

    Mat4x4 view;

    view.m[0][0] = xAxis.x;
    view.m[1][0] = xAxis.y;
    view.m[2][0] = xAxis.z;
    view.m[3][0] = -eyePos.Dot(xAxis);

    view.m[0][1] = yAxis.x;
    view.m[1][1] = yAxis.y;
    view.m[2][1] = yAxis.z;
    view.m[3][1] = -eyePos.Dot(yAxis);

    view.m[0][2] = zAxis.x;
    view.m[1][2] = zAxis.y;
    view.m[2][2] = zAxis.z;
    view.m[3][2] = -eyePos.Dot(zAxis);


    return view;
}

inline Mat4x4 Mat4x4::CreatePerspectiveFovRH(float fov,
        float aspect, float zNear, float zFar) {
    Mat4x4 p;
    p.m[0][0] = 1.0f / (aspect * std::tan(fov / 2.0f));
    p.m[1][1] = 1.0f / (std::tan(fov / 2.0f));
    p.m[2][2] = zFar / (zFar - zNear);
    p.m[2][3] = -1.0f; // Handedness.
    p.m[3][2] = -(zNear * zFar) / (zFar - zNear);
    p.m[3][3] = 0.0f;

    float f = 1.0f / std::tan(fov / 2.0f);


    p.m[0][0] = f / aspect;
    p.m[1][1] = f;

    p.m[2][2] = (zFar + zNear) / (zNear - zFar);
    p.m[3][2] = (2 * zFar * zNear) / (zNear - zFar);

    p.m[2][3] = -1.0f;
    p.m[3][3] = 0.0f;
    return p;
}

inline Mat4x4 Mat4x4::Transpose() const {
    Mat4x4 m;

    for (int i = 0; i < 4; ++i)
        for (int k = 0; k < 4; ++k)
            m.m[k][i] = this->m[i][k];

    return m;
}


inline float Mat4x4::Determinant() const {
    return m[0][0] * m[1][1] * m[2][2] * m[3][3] +
            m[0][0] * m[1][2] * m[2][3] * m[3][1] +
            m[0][0] * m[1][3] * m[2][1] * m[3][2] +
            m[0][1] * m[1][0] * m[2][3] * m[3][2] +
            m[0][1] * m[1][2] * m[2][0] * m[3][3] +
            m[0][1] * m[1][3] * m[2][2] * m[3][0] +
            m[0][2] * m[1][0] * m[2][1] * m[3][3] +
            m[0][2] * m[1][1] * m[2][3] * m[3][0] +
            m[0][2] * m[1][3] * m[2][0] * m[3][1] +
            m[0][3] * m[1][0] * m[2][2] * m[3][1] +
            m[0][3] * m[1][1] * m[2][0] * m[3][2] +
            m[0][3] * m[1][2] * m[2][1] * m[3][0] -
            m[0][0] * m[1][1] * m[2][3] * m[3][2] -
            m[0][0] * m[1][2] * m[2][1] * m[3][3] -
            m[0][0] * m[1][3] * m[2][2] * m[3][1] -
            m[0][1] * m[1][0] * m[2][2] * m[3][3] -
            m[0][1] * m[1][2] * m[2][3] * m[3][0] -
            m[0][1] * m[1][3] * m[2][0] * m[3][2] -
            m[0][2] * m[1][0] * m[2][3] * m[3][1] -
            m[0][2] * m[1][1] * m[2][0] * m[3][3] -
            m[0][3] * m[1][0] * m[2][1] * m[3][2] -
            m[0][3] * m[1][1] * m[2][2] * m[3][0] -
            m[0][3] * m[1][2] * m[2][0] * m[3][1];
}

// Returns the inverse matrix.
inline Mat4x4 Mat4x4::Inverse() const {
    Mat4x4 minors;

    minors.m[0][0] = m[1][1] * ( m[3][3] * m[2][2] - m[2][3] * m[3][2] ) -
                        m[1][2] * ( m[2][1] * m[3][3] - m[2][3] * m[3][1] ) +
                        m[1][3] * ( m[2][1] * m[3][2] - m[2][2] * m[3][1] ) ;

    minors.m[0][1] = m[1][0] * ( m[3][3] * m[2][2] - m[2][3] * m[3][2] ) -
                        m[1][2] * ( m[2][0] * m[3][3] - m[2][3] * m[3][0] ) +
                        m[1][3] * ( m[2][0] * m[3][2] - m[2][2] * m[3][0] ) ;

    minors.m[0][2] = m[1][0] * ( m[3][3] * m[2][1] - m[2][3] * m[3][1] ) -
                        m[1][1] * ( m[2][0] * m[3][3] - m[2][3] * m[3][0] ) +
                        m[1][3] * ( m[2][0] * m[3][1] - m[2][1] * m[3][0] ) ;

    minors.m[0][3] = m[1][0] * ( m[3][2] * m[2][1] - m[2][2] * m[3][1] ) -
                        m[1][1] * ( m[2][0] * m[3][2] - m[2][2] * m[3][0] ) +
                        m[1][2] * ( m[2][0] * m[3][1] - m[2][1] * m[3][0] ) ;

    minors.m[1][0] = m[0][1] * ( m[3][3] * m[2][2] - m[2][3] * m[3][2] ) -
                        m[0][2] * ( m[2][1] * m[3][3] - m[2][3] * m[3][1] ) +
                        m[0][3] * ( m[2][1] * m[3][2] - m[2][2] * m[3][1] ) ;

    minors.m[1][1] = m[0][0] * ( m[3][3] * m[2][2] - m[2][3] * m[3][2] ) -
                        m[0][2] * ( m[2][0] * m[3][3] - m[2][3] * m[3][0] ) +
                        m[0][3] * ( m[2][0] * m[3][2] - m[2][2] * m[3][0] ) ;

    minors.m[1][2] = m[0][0] * ( m[3][3] * m[2][1] - m[2][3] * m[3][1] ) -
                        m[0][1] * ( m[2][0] * m[3][3] - m[2][3] * m[3][0] ) +
                        m[0][3] * ( m[2][0] * m[3][1] - m[2][1] * m[3][0] ) ;

    minors.m[1][3] = m[0][0] * ( m[3][2] * m[2][1] - m[2][2] * m[3][1] ) -
                        m[0][1] * ( m[2][0] * m[3][2] - m[2][2] * m[3][0] ) +
                        m[0][2] * ( m[2][0] * m[3][1] - m[2][1] * m[3][0] ) ;

    minors.m[2][0] = m[0][1] * ( m[3][3] * m[1][2] - m[1][3] * m[3][2] ) -
                        m[0][2] * ( m[1][1] * m[3][3] - m[1][3] * m[3][1] ) +
                        m[0][3] * ( m[1][1] * m[3][2] - m[1][2] * m[3][1] ) ;

    minors.m[2][1] = m[0][0] * ( m[3][3] * m[1][2] - m[1][3] * m[3][2] ) -
                        m[0][2] * ( m[1][0] * m[3][3] - m[1][3] * m[3][0] ) +
                        m[0][3] * ( m[1][0] * m[3][2] - m[1][2] * m[3][0] ) ;

    minors.m[2][2] = m[0][0] * ( m[3][3] * m[1][1] - m[1][3] * m[3][1] ) -
                        m[0][1] * ( m[1][0] * m[3][3] - m[1][3] * m[3][0] ) +
                        m[0][3] * ( m[1][0] * m[3][1] - m[1][1] * m[3][0] ) ;

    minors.m[2][3] = m[0][0] * ( m[3][2] * m[1][1] - m[1][2] * m[3][1] ) -
                        m[0][1] * ( m[1][0] * m[3][2] - m[1][2] * m[3][0] ) +
                        m[0][2] * ( m[1][0] * m[3][1] - m[1][1] * m[3][0] ) ;

    minors.m[3][0] = m[0][1] * ( m[2][3] * m[1][2] - m[1][3] * m[2][2] ) -
                        m[0][2] * ( m[1][1] * m[2][3] - m[1][3] * m[2][1] ) +
                        m[0][3] * ( m[1][1] * m[2][2] - m[1][2] * m[2][1] ) ;

    minors.m[3][1] = m[0][0] * ( m[2][3] * m[1][2] - m[1][3] * m[2][2] ) -
                        m[0][2] * ( m[1][0] * m[2][3] - m[1][3] * m[2][0] ) +
                        m[0][3] * ( m[1][0] * m[2][2] - m[1][2] * m[2][0] ) ;

    minors.m[3][2] = m[0][0] * ( m[2][3] * m[1][1] - m[1][3] * m[2][1] ) -
                        m[0][1] * ( m[1][0] * m[2][3] - m[1][3] * m[2][0] ) +
                        m[0][3] * ( m[1][0] * m[2][1] - m[1][1] * m[2][0] ) ;

    minors.m[3][3] = m[0][0] * ( m[2][2] * m[1][1] - m[1][2] * m[2][1] ) -
                        m[0][1] * ( m[1][0] * m[2][2] - m[1][2] * m[2][0] ) +
                        m[0][2] * ( m[1][0] * m[2][1] - m[1][1] * m[2][0] ) ;

    // Create cofactor matrix.
    minors.m[0][1] *= -1.0f;
    minors.m[0][3] *= -1.0f;

    minors.m[1][0] *= -1.0f;
    minors.m[1][2] *= -1.0f;

    minors.m[2][1] *= -1.0f;
    minors.m[2][3] *= -1.0f;

    minors.m[3][0] *= -1.0f;
    minors.m[3][2] *= -1.0f;

    minors = minors.Transpose();

    // Return the inverse matrix.
    return minors * (1.0f / Determinant());
}

    // Transforms a 4D Vector by this matrix.
inline Vector4f Mat4x4::Transform(const Vector4f &vec) const {
    Vector4f v;
    v.x = vec.x * m[0][0] + vec.y * m[1][0] + vec.z * m[2][0] + vec.w * m[3][0];
    v.y = vec.x * m[0][1] + vec.y * m[1][1] + vec.z * m[2][1] + vec.w * m[3][1];
    v.z = vec.x * m[0][2] + vec.y * m[1][2] + vec.z * m[2][2] + vec.w * m[3][2];
    v.w = vec.x * m[0][3] + vec.y * m[1][3] + vec.z * m[2][3] + vec.w * m[3][3];
    return v;

}

// Pointer version of Transform in case the old vector isn't needed.
inline void Mat4x4::Transform(Vector4f *pVec) const {
    *pVec = Transform(*pVec);
}

// Transforms a 3D vector by this matrix.
inline Vector3f Mat4x4::Transform(const Vector3f &vec) const {
    Vector3f v;
    v.x = vec.x * m[0][0] + vec.y * m[1][0] + vec.z * m[2][0] + 1.0f * m[3][0];
    v.y = vec.x * m[0][1] + vec.y * m[1][1] + vec.z * m[2][1] + 1.0f * m[3][1];
    v.z = vec.x * m[0][2] + vec.y * m[1][2] + vec.z * m[2][2] + 1.0f * m[3][2];
    return v;
}

inline void Mat4x4::Transform(Vector3f *pVec) const {
    *pVec = Transform(*pVec);
}

// Matrix multiplication.
inline const Mat4x4 operator*(const Mat4x4 &lhs, const Mat4x4 &rhs) {
    Mat4x4 m;

    m.m[0][0] = lhs.m[0][0] * rhs.m[0][0] + lhs.m[0][1] * rhs.m[1][0] + lhs.m[0][2] * rhs.m[2][0] + lhs.m[0][3] * rhs.m[3][0];
    m.m[0][1] = lhs.m[0][0] * rhs.m[0][1] + lhs.m[0][1] * rhs.m[1][1] + lhs.m[0][2] * rhs.m[2][1] + lhs.m[0][3] * rhs.m[3][1];
    m.m[0][2] = lhs.m[0][0] * rhs.m[0][2] + lhs.m[0][1] * rhs.m[1][2] + lhs.m[0][2] * rhs.m[2][2] + lhs.m[0][3] * rhs.m[3][2];
    m.m[0][3] = lhs.m[0][0] * rhs.m[0][3] + lhs.m[0][1] * rhs.m[1][3] + lhs.m[0][2] * rhs.m[2][3] + lhs.m[0][3] * rhs.m[3][3];

    m.m[1][0] = lhs.m[1][0] * rhs.m[0][0] + lhs.m[1][1] * rhs.m[1][0] + lhs.m[1][2] * rhs.m[2][0] + lhs.m[1][3] * rhs.m[3][0];
    m.m[1][1] = lhs.m[1][0] * rhs.m[0][1] + lhs.m[1][1] * rhs.m[1][1] + lhs.m[1][2] * rhs.m[2][1] + lhs.m[1][3] * rhs.m[3][1];
    m.m[1][2] = lhs.m[1][0] * rhs.m[0][2] + lhs.m[1][1] * rhs.m[1][2] + lhs.m[1][2] * rhs.m[2][2] + lhs.m[1][3] * rhs.m[3][2];
    m.m[1][3] = lhs.m[1][0] * rhs.m[0][3] + lhs.m[1][1] * rhs.m[1][3] + lhs.m[1][2] * rhs.m[2][3] + lhs.m[1][3] * rhs.m[3][3];

    m.m[2][0] = lhs.m[2][0] * rhs.m[0][0] + lhs.m[2][1] * rhs.m[1][0] + lhs.m[2][2] * rhs.m[2][0] + lhs.m[2][3] * rhs.m[3][0];
    m.m[2][1] = lhs.m[2][0] * rhs.m[0][1] + lhs.m[2][1] * rhs.m[1][1] + lhs.m[2][2] * rhs.m[2][1] + lhs.m[2][3] * rhs.m[3][1];
    m.m[2][2] = lhs.m[2][0] * rhs.m[0][2] + lhs.m[2][1] * rhs.m[1][2] + lhs.m[2][2] * rhs.m[2][2] + lhs.m[2][3] * rhs.m[3][2];
    m.m[2][3] = lhs.m[2][0] * rhs.m[0][3] + lhs.m[2][1] * rhs.m[1][3] + lhs.m[2][2] * rhs.m[2][3] + lhs.m[2][3] * rhs.m[3][3];

    m.m[3][0] = lhs.m[3][0] * rhs.m[0][0] + lhs.m[3][1] * rhs.m[1][0] + lhs.m[3][2] * rhs.m[2][0] + lhs.m[3][3] * rhs.m[3][0];
    m.m[3][1] = lhs.m[3][0] * rhs.m[0][1] + lhs.m[3][1] * rhs.m[1][1] + lhs.m[3][2] * rhs.m[2][1] + lhs.m[3][3] * rhs.m[3][1];
    m.m[3][2] = lhs.m[3][0] * rhs.m[0][2] + lhs.m[3][1] * rhs.m[1][2] + lhs.m[3][2] * rhs.m[2][2] + lhs.m[3][3] * rhs.m[3][2];
    m.m[3][3] = lhs.m[3][0] * rhs.m[0][3] + lhs.m[3][1] * rhs.m[1][3] + lhs.m[3][2] * rhs.m[2][3] + lhs.m[3][3] * rhs.m[3][3];

    return m;
}

// Matrix scalar multiplication.
inline const Mat4x4 operator*(const Mat4x4 &lhs, float c) {
    Mat4x4 m = lhs;
    for (int i = 0; i < 4; ++i)
        for (int k = 0; k < 4; ++k)
            m.m[i][k] *= c;
    return m;
}

inline const Mat4x4 operator*(float c, const Mat4x4 &rhs) {
    return rhs * c;
}

// matrix scalar division.
inline const Mat4x4 operator/(const Mat4x4 &lhs, float c) {
    return lhs * (1.0f / c);
}
