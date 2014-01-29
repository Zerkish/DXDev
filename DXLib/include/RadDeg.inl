#ifndef DXLIB_RADDEG_H
#define DXLIB_RADDEG_H

namespace dx {

struct Degrees;

struct Radians {
private:
    float _value;
public:
    friend bool operator== (const Radians &, const Radians &);
    friend bool operator== (const Radians &, float f);
    friend bool operator== (float f, const Radians &);
    friend Degrees ToDegrees(const Radians &);

    Radians() : _value(0) { }
    explicit Radians(float f) : _value(f) { }

    inline const Radians& operator+= (const Radians &r) {
        _value += r._value;
        return (*this);
    }

    inline const Radians& operator-= (const Radians &r) {
        _value -= r._value;
        return (*this);
    }

    inline const Radians& operator*= (const Radians &r) {
        _value *= r._value;
        return (*this);
    }

    inline const Radians& operator/= (const Radians &r) {
        _value /= r._value;
        return (*this);
    }

    inline const Radians operator+ (const Radians &r) const {
        return Radians(_value + r._value);
    }

    inline const Radians operator- (const Radians &r) const {
        return Radians(_value - r._value);
    }

    inline const Radians operator* (const Radians &r) const {
        return Radians(_value * r._value);
    }

    inline const Radians operator/ (const Radians &r) const {
        return Radians(_value / r._value);
    }

    inline bool operator!= (const Radians &r) const {
        return !(*this == r);
    }

    inline bool operator> (const Radians &r) const {
        return _value > r._value;
    }

    inline bool operator< (const Radians &r) const {
        return _value < r._value;
    }

    inline bool operator>= (const Radians &r) const {
        return _value >= r._value;
    }

    inline bool operator<= (const Radians &r) const {
        return _value <= r._value;
    }
    
    inline const Radians operator- () const {
        return Radians(-_value);
    }

    inline const Radians operator+ () const {
        return *this;
    }

    inline operator float() const {
        return _value;
    }
};

struct Degrees {
private:
    float _value;
public:
    friend bool operator== (const Degrees &, const Degrees &);
    friend bool operator== (const Degrees &, float f);
    friend bool operator== (float f, const Degrees &);
    friend Radians ToRadians(const Degrees &);

    Degrees() : _value(0) { }
    explicit Degrees(float f) : _value(f) { }

    inline const Degrees& operator+= (const Degrees &r) {
        _value += r._value;
        return (*this);
    }

    inline const Degrees& operator-= (const Degrees &r) {
        _value -= r._value;
        return (*this);
    }

    inline const Degrees& operator*= (const Degrees &r) {
        _value *= r._value;
        return (*this);
    }

    inline const Degrees& operator/= (const Degrees &r) {
        _value /= r._value;
        return (*this);
    }

    inline const Degrees operator+ (const Degrees &r) const {
        return Degrees(_value + r._value);
    }

    inline const Degrees operator- (const Degrees &r) const {
        return Degrees(_value - r._value);
    }

    inline const Degrees operator* (const Degrees &r) const {
        return Degrees(_value * r._value);
    }

    inline const Degrees operator/ (const Degrees &r) const {
        return Degrees(_value / r._value);
    }

    inline bool operator!= (const Degrees &r) const {
        return !(*this == r);
    }

    inline bool operator> (const Degrees &r) const {
        return _value > r._value;
    }

    inline bool operator< (const Degrees &r) const {
        return _value < r._value;
    }

    inline bool operator>= (const Degrees &r) const {
        return _value >= r._value;
    }

    inline bool operator<= (const Degrees &r) const {
        return _value <= r._value;
    }
    
    inline const Degrees operator- () const {
        return Degrees(-_value);
    }

    inline const Degrees operator+ () const {
        return *this;
    }

    inline operator float() const {
        return _value;
    }
};

} // namespace dx
#endif // !DXLIB_RADDEG_H