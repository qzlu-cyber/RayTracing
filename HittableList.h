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

#endif //RAYTRACING_HITTABLELIST_H
