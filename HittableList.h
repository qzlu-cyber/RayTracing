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

    bool IsEmpty() const { return m_Objects.empty(); }

    size_t Size() const { return m_Objects.size(); }

    bool Hit(const Ray &ray, Interval t, HitRecord &record) const override;

    AABB GetAABB() const override;

    std::shared_ptr<Hittable> operator[](size_t index) const { return m_Objects[index]; }

    std::vector<std::shared_ptr<Hittable>> GetObjects() const { return m_Objects; }

private:
    std::vector<std::shared_ptr<Hittable>> m_Objects; // 存储所有物体
};

#endif //RAYTRACING_HITTABLELIST_H
