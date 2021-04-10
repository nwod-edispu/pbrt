#ifndef RAY_BVH_NODE_H
#define RAY_BVH_NODE_H

#include"shape.h"

int BoxXCompare(const void *a, const void *b);

int BoxYCompare(const void *a, const void *b);

int BoxZCompare(const void *a, const void *b);

class BvhNode : public Shape
{
public:
    BvhNode(Shape **l, int n);

    bool Intersect(const Ray &r, float tMin, float tMax, hit_recorder &rec) const override;

    bool ObjectBound(Bounds3f &b) const override;

    Shape *left;
    Shape *right;
    Bounds3f box;
};


#endif //RAY_BVH_NODE_H
