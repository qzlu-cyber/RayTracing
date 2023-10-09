//
// Created by 94164 on 2023/10/6.
//

#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

#include "Hittable.h"
#include "AABB.h"

class Sphere : public Hittable {
public:
    Sphere() = default;

    Sphere(Point3 center, double radius, const std::shared_ptr<Material> &material) : m_Center1(center),
                                                                                      m_IsMoving(false),
                                                                                      m_Radius(radius),
                                                                                      m_Material(material) {}

    Sphere(Point3 center1, Point3 center2, double radius, const std::shared_ptr<Material> &material) : m_Center1(center1),
                                                                                                       m_Center2(center2),
                                                                                                       m_Radius(radius),
                                                                                                       m_Material(material),
                                                                                                       m_IsMoving(true),
                                                                                                       m_CenterVector(center2 - center1) {}

    bool Hit(const Ray &ray, Interval t, HitRecord &record) const override;

    AABB GetAABB() const override;

private:
    Point3 Center(double time) const; // 计算球心在某一时刻的位置

private:
    Point3 m_Center1; // 球心 1 运动轨迹的起点
    Point3 m_Center2; // 球心 2 运动轨迹的终点
    Vec3 m_CenterVector; // 球心 1 到 球心 2 的向量
    bool m_IsMoving; // 球体是否在运动
    double m_Radius; // 半径
    std::shared_ptr<Material> m_Material; // 材质
};

#endif //RAYTRACING_SPHERE_H
