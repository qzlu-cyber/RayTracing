//
// Created by 94164 on 2023/10/8.
//
#include <ctime>
#include "BVH.h"

static AABB Union(const AABB &box1, const AABB &box2) {
    Point3 small(fmin(box1.Min().x(), box2.Min().x()),
                 fmin(box1.Min().y(), box2.Min().y()),
                 fmin(box1.Min().z(), box2.Min().z()));
    Point3 big(fmax(box1.Max().x(), box2.Max().x()),
               fmax(box1.Max().y(), box2.Max().y()),
               fmax(box1.Max().z(), box2.Max().z()));

    return AABB(small, big);
}

BVH::BVH(const std::shared_ptr<HittableList> &hittableList, int maxPrimitivesInNode, BVH::SplitMethod splitMethod)
    : m_MaxPrimitivesInNode(std::min(255, maxPrimitivesInNode)), m_SplitMethod(splitMethod), m_HittableList(hittableList) {
    time_t start, end; // 计时
    time(&start);

    if (m_HittableList->IsEmpty()) return;
    m_Root = BuildBVH(m_HittableList); // 递归构建 BVH 树

    time(&end);
    double timeCost = difftime(end, start);
    int hour = (int) (timeCost / 3600);
    int minute = (int) (timeCost - hour * 3600) / 60;
    int second = (int) (timeCost - hour * 3600 - minute * 60);
    std::cout << "BVH Tree Build Time: " << hour << "h " << minute << "m " << second << "s" << std::endl;
}

std::shared_ptr<BVHNode> BVH::BuildBVH(std::shared_ptr<HittableList> &hittableList) {
    std::shared_ptr<BVHNode> node = std::make_shared<BVHNode>();
    AABB aabb = hittableList->GetAABB(); // 计算物体列表的包围盒

    if (hittableList->Size() == 1) { // 如果物体列表中只有一个物体，那么该物体就是叶子节点
        node->aabb = aabb;
        node->object = (*hittableList)[0];
        return node;
    } else if (hittableList->Size() == 2) { // 如果物体列表中只有两个物体，那么该节点的左右子树分别是这两个物体
        std::shared_ptr<HittableList> leftList = std::make_shared<HittableList>();
        std::shared_ptr<HittableList> rightList = std::make_shared<HittableList>();
        leftList->Add((*hittableList)[0]);
        rightList->Add((*hittableList)[1]);
        node->aabb = aabb;
        node->left = BuildBVH(leftList);
        node->right = BuildBVH(rightList);
        return node;
    } else { // 如果大于两个物体就要进行 BVH 划分
        AABB centroidAABB; // 计算物体列表的中心包围盒

        for (int i = 0; i < hittableList->Size(); ++i) // 遍历物体列表，计算物体列表的中心包围盒
            centroidAABB = Union(centroidAABB, (*hittableList)[i]->GetAABB().Center());

        int splitAxis = centroidAABB.MaxDimension(); // 计算中心包围盒的最长轴
        auto objects = hittableList->GetObjects(); // 获取物体列表
        switch (splitAxis) { // 根据不同的情况，将物体根据中心坐标分别按照 x、y、z 轴排序
            case 0: // x 轴
                std::sort(objects.begin(), objects.end(), [](const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b) {
                    return a->GetAABB().Center().x() < b->GetAABB().Center().x();
                });
                break;
            case 1: // y 轴
                std::sort(objects.begin(), objects.end(), [](const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b) {
                    return a->GetAABB().Center().y() < b->GetAABB().Center().y();
                });
                break;
            case 2: // z 轴
                std::sort(objects.begin(), objects.end(), [](const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b) {
                    return a->GetAABB().Center().z() < b->GetAABB().Center().z();
                });
                break;
        }

        auto beginning = objects.begin(); // 物体列表的起始迭代器
        auto middling = objects.begin() + hittableList->Size() / 2; // 物体列表的中间迭代器
        auto ending = objects.end(); // 物体列表的末尾迭代器

        std::shared_ptr<HittableList> leftList = std::make_shared<HittableList>(); // 左子树物体列表
        std::shared_ptr<HittableList> rightList = std::make_shared<HittableList>(); // 右子树物体列表

        // 将物体列表中的物体分别添加到左右子树物体列表中
        for (auto it = beginning; it != middling; ++it)
            leftList->Add(*it);
        for (auto it = middling; it != ending; ++it)
            rightList->Add(*it);

        // 递归构建左右子树
        node->left = BuildBVH(leftList);
        node->right = BuildBVH(rightList);

        // 计算当前节点的包围盒
        node->aabb = Union(node->left->aabb, node->right->aabb);
    }

    return node;
}

bool BVH::Hit(const std::shared_ptr<BVHNode>& node, const Ray &ray, Interval t, HitRecord &record) const {
    if (!node->aabb.Hit(ray)) // 如果光线与包围盒不相交
        return false;
    if (!node->left && !node->right) // 如果是叶子节点
        return node->object->Hit(ray, t, record); // 判断光线与物体是否相交

    // 如果不是叶子节点，递归判断光线与左右子树是否相交
    HitRecord leftRecord, rightRecord;
    bool hitLeft = Hit(node->left, ray, t, leftRecord); // 判断光线与左子树是否相交
    bool hitRight = Hit(node->right, ray, t, rightRecord); // 判断光线与右子树是否相交
    // 比较两个交点的距离，返回距离较小的那个交点
    record = (hitLeft && hitRight) ? (leftRecord.t < rightRecord.t ? leftRecord : rightRecord) : (hitLeft ? leftRecord : (hitRight ? rightRecord : record));

    return hitLeft || hitRight;
}

