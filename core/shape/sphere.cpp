//
// Created by h'pinp on 2021-03-26.
//

#include "sphere.h"

bool Sphere::intersect(const Ray &r, float tMin, float tMax, hit_recorder &rec) const
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

Sphere::Sphere(Material *material,Point3f cen, float r)
        : Shape(material), center(cen), radius(r)
{

}

Bounds3f Sphere::ObjectBound() const
{
    return Bounds3f();
}
