#ifndef RAY_SHAPE_H
#define RAY_SHAPE_H

#include"../component/transform.h"
#include"../component/bounds.h"
#include"../utils/utils.h"

class Material;

struct hit_recorder
{
    float t;
    Point3f p;
    Vector3f normal;
    Material *mat_ptr;
};


class Shape
{
public:
    Shape(Material* material);

    virtual bool Intersect(const Ray &r, float tMin, float tMax, hit_recorder &rec) const = 0;

    Material* material;

    virtual bool ObjectBound(Bounds3f &box) const = 0;



};

#endif //RAY_SHAPE_H
