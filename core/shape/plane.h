#ifndef RAY_PLANE_H
#define RAY_PLANE_H
#include"shape.h"

class Plane: public Shape
{
public:
    Plane(Material* material, Vector3f normal, Point3f p);

    virtual bool intersect(const Ray &r, float tMin, float tMax, hit_recorder &rec)const ;

    virtual Bounds3f ObjectBound() const;
    Vector3f normal;
    Point3f pinp;
};


#endif //RAY_PLANE_H
