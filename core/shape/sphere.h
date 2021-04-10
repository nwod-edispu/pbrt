#ifndef RAY_SPHERE_H
#define RAY_SPHERE_H

#include"shape.h"


class Sphere : public Shape
{
public:
    Sphere(Material *material, Point3f cen, float r);

    virtual bool Intersect(const Ray &r, float tMin, float tMax, hit_recorder &rec) const;

    virtual bool ObjectBound(Bounds3f &box) const;

    Point3f center;
    float radius;
};


#endif //RAY_SPHERE_H