//
// Created by 94164 on 2023/10/6.
//
#include "HittableList.h"

static AABB Union(const AABB &box1, const AABB &box2) {
    Point3 small(fmin(box1.Min().x(), box2.Min().x()),
                 fmin(box1.Min().y(), box2.Min().y()),
                 fmin(box1.Min().z(), box2.Min().z()));
    Point3 big(fmax(box1.Max().x(), box2.Max().x()),
               fmax(box1.Max().y(), box2.Max().y()),
               fmax(box1.Max().z(), box2.Max().z()));

    return AABB(small, big);
}

/// \brief 判断光线是否与物体列表中的物体相交
bool HittableList::Hit(const Ray &ray, Interval t, HitRecord &record) const {
    HitRecord tempRecord; // 临时记录交点信息
    bool hitAnything = false; // 是否有物体被光线击中
    double closestSoFar = t.Max(); // 最近的交点

    for (const auto &object : m_Objects) { // 遍历所有物体
        if (object->Hit(ray, Interval(t.Min(), closestSoFar), tempRecord)) { // 如果光线击中物体
            hitAnything = true;
            closestSoFar = tempRecord.t; // 更新最近的交点
            record = tempRecord; // 更新交点信息
        }
    }

    return hitAnything;
}

AABB HittableList::GetAABB() const {
    if (m_Objects.empty()) return AABB(); // 如果物体列表为空，返回空包围盒

    AABB box; // 包围盒
    bool firstBox = true; // 是否是第一个包围盒

    for (const auto &object : m_Objects) { // 遍历所有物体
        AABB objectBox = object->GetAABB(); // 获取物体的包围盒
        if (firstBox) { // 如果是第一个包围盒
            box = objectBox; // 直接赋值
        } else { // 如果不是第一个包围盒
            box = Union(box, objectBox); // 计算包围盒
        }
        firstBox = false;
    }

    return box;
}

