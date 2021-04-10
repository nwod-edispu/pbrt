//
// Created by h'pinp on 2021/3/31.
//

#ifndef RAY_CYLINDER_H
#define RAY_CYLINDER_H

#include"disk.h"

class Cylinder : public Shape
{
public:
    Cylinder(Material *material,Point3f center,
               float radius, float yMin, float yMax);
    virtual bool Intersect(const Ray &r, float tMin, float tMax, hit_recorder &rec)const ;

    virtual bool ObjectBound(Bounds3f &box) const;
    float yMin,yMax;
    Point3f center;
    float radius;
    Disk* disk;
};


#endif //RAY_CYLINDER_H
