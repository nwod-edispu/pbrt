#ifndef RAY_BOUNDS_H
#define RAY_BOUNDS_H

#include<algorithm>
#include"point.h"


template<typename T>
class Bounds2
{
public:

};

template<typename T>
class Bounds3
{
public:
    Bounds3()
    {
        T minNum = std::numeric_limits<T>::lowest();
        T maxNum = std::numeric_limits<T>::max();
        pMin = Point3<T>(minNum, minNum, minNum);
        pMax = Point3<T>(maxNum, maxNum, maxNum);
    }

    Bounds3(Point3<T> &p) : pMin(p), pMax(p)
    {}

    Bounds3(Point3<T> &p1, Point3<T> &p2)
            : pMin(std::min(p1.x, p2.x), std::min(p1.y, p2.y),
                   std::min(p1.z, p2.z)),
              pMax(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
                   std::max(p1.z, p2.z))
    {}


    Point3<T> pMin, pMax;

};

typedef Bounds2<float> Bounds2f;
typedef Bounds2<int> Bounds2i;
typedef Bounds3<float> Bounds3f;
typedef Bounds3<int> Bounds3i;
#endif //RAY_BOUNDS_H
