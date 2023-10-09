//
// Created by 94164 on 2023/10/8.
//

#ifndef RAYTRACING_SCENE_H
#define RAYTRACING_SCENE_H

#include "Camera.h"
#include "HittableList.h"
#include "BVH.h"

class Scene {
public:
    Scene(const std::shared_ptr<HittableList> &hittableList) : m_HittableList(hittableList) {}

    void BuildBVH() {
        std::cout << "Building BVH..." << std::endl;
        m_BVH = new BVH(m_HittableList, 5, BVH::SplitMethod::NAIVE);
    }

    bool Hit(const Ray &ray, Interval t, HitRecord &record) const {
        return m_BVH->Hit(m_BVH->m_Root, ray, t, record);
    }

private:
    BVH* m_BVH;
    std::shared_ptr<HittableList> m_HittableList;
};

#endif //RAYTRACING_SCENE_H
