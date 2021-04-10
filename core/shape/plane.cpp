//
// Created by h'pinp on 2021/3/31.
//

#include "plane.h"

Plane::Plane(Material *material, Vector3f normal, Point3f p)
        : Shape(material), normal(normal), pinp(p)
{
}

bool Plane::Intersect(const Ray &r, float tMin, float tMax, hit_recorder &rec) const
{
    rec.mat_ptr = material;
    float t = Dot(pinp - r.o, normal) / Dot(r.d, normal);
    if (t > tMin && t < tMax)
    {
        rec.t = t;
        rec.p = r.point_at_parameter(t);
        rec.normal = Unit(normal);
        return true;
    }
    return false;
}

bool Plane::ObjectBound(Bounds3f &box) const
{
    return false;
}
