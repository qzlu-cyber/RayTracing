//
// Created by 94164 on 2023/10/6.
//

#ifndef RAYTRACING_HITTABLE_H
#define RAYTRACING_HITTABLE_H

#include "Interval.h"
#include "Ray.h"

class HitRecord {
public:
    Vec3 point; // 交点
    Vec3 normal; // 法向量
    double t; // 交点的 t 值
    bool frontFace; // 光线是否从正面打到物体上

    void SetFaceNormal(const Ray &ray, const Vec3 &outwardNormal) {
        frontFace = Dot(ray.Direction(), outwardNormal) < 0.0; // 光线的方向是否与交点的法向量方向相同。如果是，说明光线从球体内部射入，否则光线从球体外部射入
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable {
public:
    virtual ~Hittable() = default;

    virtual bool Hit(const Ray &ray, Interval t, HitRecord &record) const = 0;
};

#endif //RAYTRACING_HITTABLE_H
