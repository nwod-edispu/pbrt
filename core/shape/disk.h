//
// Created by h'pinp on 2021/3/31.
//

#ifndef RAY_DISK_H
#define RAY_DISK_H
#include"plane.h"

class Disk:public Shape
{
public:
    Disk(Material *material,Vector3f normal,Point3f center,float radius);
    virtual bool intersect(const Ray &r, float tMin, float tMax, hit_recorder &rec)const ;

    virtual Bounds3f ObjectBound() const;
    Vector3f normal;
    Point3f center;
    float radius;
};


#endif //RAY_DISK_H
