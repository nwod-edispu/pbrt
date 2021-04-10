#include "cylinder.h"

Cylinder::Cylinder(Material *material, Point3f center, float radius, float yMin, float yMax)
        : Shape(material), center(center), radius(radius), yMin(yMin), yMax(yMax)
{
    disk = new Disk(material, Vector3f(0, 1, 0), Point3f(center.x, yMax, center.z), radius);
}

bool Cylinder::Intersect(const Ray &r, float tMin, float tMax, hit_recorder &rec) const
{
    hit_recorder tmp_rec;
    tmp_rec.t = tMax;
    bool hit_disk = disk->Intersect(r, tMin, tMax, tmp_rec);
    rec.mat_ptr = material;
    float a = r.d.x * r.d.x + r.d.z * r.d.z;
    float b = r.d.x * (r.o.x - center.x) + r.d.z * (r.o.z - center.z);
    float c = std::pow(r.o.x - center.x, 2) + std::pow(r.o.z - center.z, 2)
              - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0)
    {
        float t = ((-b - sqrt(discriminant)) / a);
        if (t < tMax && t > tMin)
        {
            Point3f p = r.point_at_parameter(t);
            if (p.y < yMax && p.y > yMin)
            {
                if (hit_disk && tmp_rec.t < t)
                {
                    rec = tmp_rec;
                    return true;
                }
                rec.t = t;
                rec.p = p;
                rec.normal = (rec.p - Point3f(center.x, rec.p.y, center.z)) / radius;
                return true;
            }
        }
        t = ((-b + sqrt(discriminant)) / a);
        if (t < tMax && t > tMin)
        {
            Point3f p = r.point_at_parameter(t);
            if (p.y < yMax && p.y > yMin)
            {
                if (hit_disk && tmp_rec.t < t)
                {
                    rec = tmp_rec;
                    return true;
                }
                rec.t = t;
                rec.p = p;
                rec.normal = (rec.p - Point3f(center.x, rec.p.y, center.z)) / radius;
                return true;
            }
        }
    }
    if (hit_disk)
    {
        rec.t = tmp_rec.t;
        rec.normal = tmp_rec.normal;
        rec.p = tmp_rec.p;
        return true;
    }
    return false;
}

bool Cylinder::ObjectBound(Bounds3f &box) const
{
    Point3f p1 = Point3f(center.x, yMin, center.z) - Vector3f(radius, 0, radius);
    Point3f p2 = Point3f(center.x, yMax, center.z) + Vector3f(radius, 0, radius);
    box=Bounds3f(p1, p2);
    return true;
}
