//
// Created by 94164 on 2023/10/6.
//

#ifndef RAYTRACING_HITTABLELIST_H
#define RAYTRACING_HITTABLELIST_H

#include <memory>
#include <vector>

#include "Hittable.h"

class HittableList : public Hittable {
public:
    HittableList() = default;

    explicit HittableList(const std::shared_ptr<Hittable>& object) { Add(object); }

    void Clear() { m_Objects.clear(); }

    void Add(const std::shared_ptr<Hittable>& object) { m_Objects.push_back(object); }

    bool Hit(const Ray &ray, Interval t, HitRecord &record) const override;

private:
    std::vector<std::shared_ptr<Hittable>> m_Objects; // 存储所有物体
};

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

#endif //RAYTRACING_HITTABLELIST_H
