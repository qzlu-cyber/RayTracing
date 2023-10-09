//
// Created by 94164 on 2023/10/6.
//
#include "Sphere.h"

/// \brief 判断光线是否与球体相交
/// \param ray 光线
/// \param tMin 表示最小的光线参数 t 值，它用于过滤掉在光线起点之前的交点
/// \param tMax 表示最大的光线参数 t 值，它用于过滤掉在光线起点之后的交点
/// \param record 记录交点信息
/// \return 光线是否与球体相交
bool Sphere::Hit(const Ray &ray, Interval t, HitRecord &record) const {
    Point3 center = (m_IsMoving) ? Center(ray.Time()) : m_Center1; // 计算球心在某一时刻的位置
    Vec3 oc = ray.Origin() - center; // 球心到光线原点的向量
    double a = ray.Direction().LengthSquared(); // 光线方向的长度的平方
    double half_b = Dot(oc, ray.Direction());
    double c = oc.LengthSquared() - m_Radius * m_Radius;
    double discriminant = half_b * half_b - a * c;

    if (discriminant < 0) return false; // 无交点

    double root = (-half_b - std::sqrt(discriminant)) / a; // 较小的根，即较近的交点
    if (!t.Surrounds(root)) { // 交点不在范围内
        root = (-half_b + std::sqrt(discriminant)) / a; // 较大的根，即较远的交点
        if (!t.Surrounds(root)) { // 交点不在范围内
            return false;
        }
    }

    record.t = root; // 交点的 t 值
    record.point = ray.At(record.t); // 交点
    record.material = m_Material; // 材质
    Vec3 outwardNormal = (record.point - center) / m_Radius; // 交点的法向量
    record.SetFaceNormal(ray, outwardNormal);

    return true;
}

Point3 Sphere::Center(double time) const {
    return m_Center1 + time * m_CenterVector; // 计算球心在某一时刻的位置
}

AABB Sphere::GetAABB() const {
    Point3 center = (m_IsMoving) ? Center(0) : m_Center1; // 计算球心在某一时刻的位置
    return AABB(center - m_Radius, center + m_Radius); // 计算包围盒
}

