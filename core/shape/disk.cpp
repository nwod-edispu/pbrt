//
// Created by h'pinp on 2021/3/31.
//

#include "disk.h"


Disk::Disk(Material *material, Vector3f normal, Point3f p, float radius)
        : Shape(material), normal(normal), center(p), radius(radius)
{
}

bool Disk::intersect(const Ray &r, float tMin, float tMax, hit_recorder &rec) const
{
    rec.mat_ptr = material;
    float t = Dot(center - r.o, normal) / Dot(r.d, normal);
    if (t > tMin && t < tMax)
    {
        rec.t = t;
        rec.p = r.point_at_parameter(t);
        rec.normal = Unit(normal);
        if ((rec.p - center).Length() < radius)
        {
            return true;
        }
    }
    return false;
}

Bounds3f Disk::ObjectBound() const
{
    return Bounds3f();
}
