//
// Created by 94164 on 2023/10/6.
//

#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H

#include <iostream>

#include "Vec3.h"

class Ray {
public:
    Ray() = default;

    Ray(const Point3 &origin, const Vec3 &direction) : m_Origin(origin), m_Direction(direction) {}

    Point3 Origin() const { return m_Origin; }

    Vec3 Direction() const { return m_Direction; }

    Point3 At(double t) const {
        return m_Origin + t * m_Direction;
    }

private:
    Point3 m_Origin; // 原点
    Vec3 m_Direction; // 方向
};

#endif //RAYTRACING_RAY_H
