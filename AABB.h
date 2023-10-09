//
// Created by 94164 on 2023/10/8.
//

#ifndef RAYTRACING_AABB_H
#define RAYTRACING_AABB_H

#include "Utils.h"
#include "Vec3.h"
#include "Ray.h"

class AABB {
public:
    AABB() {
        m_Min = Point3(Infinity, Infinity, Infinity);
        m_Max = Point3(-Infinity, -Infinity, -Infinity);
    }
    
    AABB(const Point3 &p) : m_Min(p), m_Max(p) {}

    AABB(const Point3 &p1, const Point3 &p2) {
        m_Min = Point3(std::fmin(p1.x(), p2.x()), std::fmin(p1.y(), p2.y()), std::fmin(p1.z(), p2.z()));
        m_Max = Point3(std::fmax(p1.x(), p2.x()), std::fmax(p1.y(), p2.y()), std::fmax(p1.z(), p2.z()));
    }

    Point3 Min() const { return m_Min; }

    Point3 Max() const { return m_Max; }

    // 计算包围盒对角线
    Vec3 Diagonal() const { return m_Max - m_Min; }
    // 返回包围盒最大维度
    int MaxDimension() const {
        Vec3 diagonal = Diagonal();
        if (diagonal.x() > diagonal.y() && diagonal.x() > diagonal.z()) return 0;
        else if (diagonal.y() > diagonal.z()) return 1;
        else return 2;
    }
    // 计算包围盒中心
    Point3 Center() const { return 0.5 * (m_Min + m_Max); }
    // 判断当前包围盒是否和另一个包围盒相交
    bool Overlap(const AABB &other) const {
        bool x = (m_Max.x() >= other.m_Min.x()) && (m_Min.x() <= other.m_Max.x());
        bool y = (m_Max.y() >= other.m_Min.y()) && (m_Min.y() <= other.m_Max.y());
        bool z = (m_Max.z() >= other.m_Min.z()) && (m_Min.z() <= other.m_Max.z());
        return x && y && z;
    }
    // 判断当前包围盒是否包含某一点
    bool Contain(const Point3 &p) const {
        return (p.x() >= m_Min.x() && p.x() <= m_Max.x()) &&
               (p.y() >= m_Min.y() && p.y() <= m_Max.y()) &&
               (p.z() >= m_Min.z() && p.z() <= m_Max.z());
    }
    // 判断光线是否与包围盒相交
    bool Hit(const Ray &ray) {
        Vec3 invDir = {1.0 / ray.Direction().x(), 1.0 / ray.Direction().y(), 1.0 / ray.Direction().z()};
        // tMinX 代表光线进入包围盒 X 面的时间，tMaxX 代表光线离开包围盒 X 面的时间，其他变量类似
        // tEnter 代表光线进入包围盒的时间，tExit 代表光线离开包围盒的时间
        double t1, t2, tMinX, tMaxX, tMinY, tMaxY, tMinZ, tMaxZ, tEnter, tExit;

        t1 = (m_Min.x() - ray.Origin().x()) * invDir.x();
        t2 = (m_Max.x() - ray.Origin().x()) * invDir.x();
        tMinX = std::fmin(t1, t2);
        tMaxX = std::fmax(t1, t2);

        t1 = (m_Min.y() - ray.Origin().y()) * invDir.y();
        t2 = (m_Max.y() - ray.Origin().y()) * invDir.y();
        tMinY = std::fmin(t1, t2);
        tMaxY = std::fmax(t1, t2);

        t1 = (m_Min.z() - ray.Origin().z()) * invDir.z();
        t2 = (m_Max.z() - ray.Origin().z()) * invDir.z();
        tMinZ = std::fmin(t1, t2);
        tMaxZ = std::fmax(t1, t2);

        tEnter = std::fmax(std::fmax(tMinX, tMinY), tMinZ); // 光线进入所有面才代表光线进入包围盒
        tExit = std::fmin(std::fmin(tMaxX, tMaxY), tMaxZ); // 光线离开任意面就代表光线离开包围盒

        if (tExit < 0.0) return false; // 包围盒在光线起点之后，说明光线没有与包围盒相交
        if (tEnter >= tExit) return false; // 光线进入包围盒的时间晚于光线离开包围盒的时间，说明光线没有与包围盒相交

        return true;
    }
public:
    Point3 m_Min; // 最小点
    Point3 m_Max; // 最大点
};

#endif //RAYTRACING_AABB_H
