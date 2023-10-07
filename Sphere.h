//
// Created by 94164 on 2023/10/6.
//

#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

#include "Hittable.h"

class Sphere : public Hittable {
public:
    Sphere() = default;

    Sphere(Point3 center, double radius, const std::shared_ptr<Material> &material) : m_Center(center),
                                                                                      m_Radius(radius),
                                                                                      m_Material(material) {}

    bool Hit(const Ray &ray, Interval t, HitRecord &record) const override;

private:
    Point3 m_Center; // 球心
    double m_Radius; // 半径
    std::shared_ptr<Material> m_Material; // 材质
};

#endif //RAYTRACING_SPHERE_H
