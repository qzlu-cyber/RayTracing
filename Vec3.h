//
// Created by 94164 on 2023/10/6.
//

#ifndef RAYTRACING_VEC3_H
#define RAYTRACING_VEC3_H

#include <iostream>
#include <cmath>

#include "Utils.h"

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

    static Vec3 Random() {
        return {RandomDouble(), RandomDouble(), RandomDouble()};
    }

    static Vec3 Random(double min, double max) {
        return {RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max)};
    }

    bool NearZero() {
        // Return true if the vector is close to zero in all dimensions.
        const auto s = 1e-8;
        return (std::fabs(m_V[0]) < s) && (std::fabs(m_V[1]) < s) && (std::fabs(m_V[2]) < s);
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

inline Vec3 Reflect(const Vec3 &v, const Vec3 &n) {
    return v - 2 * Dot(v, n) * n;
}

inline Vec3 Refract(const Vec3 &uv, const Vec3 &n, double etaiOverEtat) {
    // Snell's Law
    double cosTheta = Dot(-uv, n);
    Vec3 rOutParallel = etaiOverEtat * (uv + cosTheta * n);
    Vec3 rOutPerp = -std::sqrt(std::fabs(1.0 - rOutParallel.LengthSquared())) * n;
    return rOutParallel + rOutPerp;
}

inline Vec3 RandomInUnitSphere() {
    // 生成一个单位球内的随机向量
    while (true) {
        Vec3 p = Vec3::Random(-1, 1);
        if (p.LengthSquared() < 1) return p;
    }
}

inline Vec3 RandomUnitVector() {
    // 生成一个单位向量
    return Normalize(RandomInUnitSphere());
}

inline Vec3 RandomInHemisphere(const Vec3 &normal) {
    Vec3 inUnitSphere = RandomUnitVector();
    if (Dot(inUnitSphere, normal) > 0.0) // 生成的随机反射向量在正半球中
        return inUnitSphere;
    else
        return -inUnitSphere;
}

inline Vec3 RandomInUnitDisk() {
    // 生成一个单位圆盘内的随机向量
    while (true) {
        Vec3 p = {RandomDouble(-1, 1), RandomDouble(-1, 1), 0};
        if (p.LengthSquared() < 1) return p;
    }
}

#endif //RAYTRACING_VEC3_H
