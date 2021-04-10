//
// Created by h'pinp on 2021-03-26.
//

#include "sphere.h"

bool Sphere::Intersect(const Ray &r, float tMin, float tMax, hit_recorder &rec) const
{
    rec.mat_ptr = material;
    Vector3f oc = r.o - center;
    float a = Dot(r.d, r.d);
    float b = Dot(oc, r.d);
    float c = Dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0)
    {
        float t = ((-b - sqrt(discriminant)) / a);
        if (t < tMax && t > tMin)
        {
            rec.t = t;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        t = ((-b + sqrt(discriminant)) / a);
        if (t < tMax && t > tMin)
        {
            rec.t = t;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;
}

Sphere::Sphere(Material *material, Point3f cen, float r)
        : Shape(material), center(cen), radius(r)
{

}

bool Sphere::ObjectBound(Bounds3f &box) const
{
    Point3f p1 = center - Vector3f(radius, radius, radius);
    Point3f p2 = center + Vector3f(radius, radius, radius);
    box = Bounds3f(p1, p2);
    return true;
}
