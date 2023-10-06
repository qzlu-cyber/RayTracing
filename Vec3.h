//
// Created by 94164 on 2023/10/6.
//

#ifndef RAYTRACING_VEC3_H
#define RAYTRACING_VEC3_H

#include <iostream>
#include <cmath>

class Vec3 {
public:
    Vec3() : m_V{0, 0, 0} {}

    Vec3(double e0, double e1, double e2) : m_V{e0, e1, e2} {}

    double x() const { return m_V[0]; }

    double y() const { return m_V[1]; }

    double z() const { return m_V[2]; }

    Vec3 &operator+=(const Vec3 &v) {
        m_V[0] += v.m_V[0];
        m_V[1] += v.m_V[1];
        m_V[2] += v.m_V[2];

        return *this;
    }

    Vec3 &operator*=(const double t) {
        m_V[0] *= t;
        m_V[1] *= t;
        m_V[2] *= t;

        return *this;
    }

    Vec3 &operator/=(const double t) {
        return *this *= 1 / t;
    }

    Vec3 operator-() const { return {-m_V[0], -m_V[1], -m_V[2]}; }

    double operator[](int i) const { return m_V[i]; }

    double &operator[](int i) { return m_V[i]; }

    double LengthSquared() const {
        return m_V[0] * m_V[0] + m_V[1] * m_V[1] + m_V[2] * m_V[2];
    }

    double Length() const {
        return std::sqrt(LengthSquared());
    }

private:
    double m_V[3];
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using Point3 = Vec3;
using Color = Vec3;

// Vector Utility Functions
inline std::ostream &operator<<(std::ostream &out, const Vec3 &v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return {u.x() + v.x(), u.y() + v.y(), u.z() + v.z()};
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return {u.x() - v.x(), u.y() - v.y(), u.z() - v.z()};
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return {u.x() * v.x(), u.y() * v.y(), u.z() * v.z()};
}

inline Vec3 operator*(double t, const Vec3 &v) {
    return {t * v.x(), t * v.y(), t * v.z()};
}

inline Vec3 operator*(const Vec3 &v, double t) {
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t) {
    return (1 / t) * v;
}

inline double Dot(const Vec3 &u, const Vec3 &v) {
    return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

inline Vec3 Cross(const Vec3 &u, const Vec3 &v) {
    return {u.y() * v.z() - u.z() * v.y(),
            u.z() * v.x() - u.x() * v.z(),
            u.x() * v.y() - u.y() * v.x()};
}

inline Vec3 Normalize(Vec3 v) {
    return v / v.Length();
}

#endif //RAYTRACING_VEC3_H
