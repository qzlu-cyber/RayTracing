//
// Created by 94164 on 2023/10/8.
//

#ifndef RAYTRACING_BVH_H
#define RAYTRACING_BVH_H

#include <vector>

#include "AABB.h"
#include "HittableList.h"

struct BVHNode {
    BVHNode() {
        aabb = AABB();
        left = nullptr;
        right = nullptr;
        object = nullptr;
    }

    int splitAxis; // 该节点的分割轴
    int firstPrimitiveOffset; // 该节点的第一个物体在物体列表中的偏移量
    int numPrimitives; // 该节点包含的物体数量

    AABB aabb; // 包围盒
    std::shared_ptr<BVHNode> left; // 左子树
    std::shared_ptr<BVHNode> right; // 右子树
    std::shared_ptr<Hittable> object; // 当前节点包含的物体
};

class BVH {
public:
    enum class SplitMethod {
        NAIVE, // 朴素方法
        SAH // 表面积启发式方法
    };

    BVH() = default;

    BVH(const std::shared_ptr<HittableList> &hittableList, int maxPrimitivesInNode = 5, SplitMethod splitMethod = SplitMethod::NAIVE);

    bool Hit(const std::shared_ptr<BVHNode>& node, const Ray &ray, Interval t, HitRecord &record) const;

    std::shared_ptr<BVHNode> BuildBVH(std::shared_ptr<HittableList> &hittableList);

public:
    std::shared_ptr<BVHNode> m_Root; // BVH 树的根节点

private:
    const int m_MaxPrimitivesInNode; // 每个节点最多包含的物体数量
    const SplitMethod m_SplitMethod; // 分割方法
    std::shared_ptr<HittableList> m_HittableList; // 物体列表
};

#endif //RAYTRACING_BVH_H
