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
    bool Intersect(const Ray &r, float tMin, float tMax, hit_recorder &rec)const override ;

    bool ObjectBound(Bounds3f &box) const override;
    Vector3f normal;
    Point3f center;
    float radius;
};


#endif //RAY_DISK_H
