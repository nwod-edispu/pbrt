#ifndef RAY_H
#define RAY_H

#include"medium.h"
#include"vec.h"
#include "point.h"
#include"../utils/const.h"

class Ray
{
public:
    Ray() : tMax(Infinity), time(0), medium(nullptr)
    {}

    Ray(const Point3f o, const Vector3f d, float tMax = Infinity,
        float time = 0.f, const Medium *medium = nullptr)
            : o(o), d(d), tMax(tMax), time(time), medium(medium)
    {}

    Point3f point_at_parameter(float t) const
    { return o + d * t; }

    Point3f o;
    Vector3f d;
    mutable float tMax;
    float time;
    const Medium *medium;
};

#endif
