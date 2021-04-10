#ifndef RAY_BOUNDS_H
#define RAY_BOUNDS_H

#include"ray.h"
#include"geometry.h"

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
        pMin = Point3<T>(maxNum, maxNum, maxNum);
        pMax = Point3<T>(minNum, minNum, minNum);
    }


    Bounds3(Point3<T> &p1, Point3<T> &p2)
            : pMin(std::min(p1.x, p2.x), std::min(p1.y, p2.y),
                   std::min(p1.z, p2.z)),
              pMax(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
                   std::max(p1.z, p2.z))
    {
    }

    bool hit(const Ray &r, float tMin, float tMax) const
    {
        for (int a = 0; a < 3; a++)
        {
            float invD = 1.0f / r.d[a];
            float t0 = (pMin[a] - r.o[a]) * invD;
            float t1 = (pMax[a] - r.o[a]) * invD;
            if (invD < 0.0f)
            {
                std::swap(t0, t1);
            }
            tMin = t0 > tMin ? t0 : tMin;
            tMax = t1 < tMax ? t1 : tMax;
            if (tMin >= tMax)return false;
        }
        return true;
    }

    Point3<T> pMin, pMax;
};

typedef Bounds2<float> Bounds2f;
typedef Bounds2<int> Bounds2i;
typedef Bounds3<float> Bounds3f;
typedef Bounds3<int> Bounds3i;

template<typename T>
Bounds3<T> SurroundingBox(Bounds3<T> &box0, Bounds3<T> &box1)
{
    Point3<T> small = Min(box0.pMin, box1.pMin);
    Point3<T> big = Max(box0.pMax, box1.pMax);
//    std::cout<<Bounds3<T>(small, big);
    return Bounds3<T>(small, big);
}

template<typename T>
std::ostream &operator<<(std::ostream &out, Bounds3<T> &b)
{
    out << "Bounds3(" << b.pMin << ", \n\t" << b.pMax << ")\n";
    return out;
}
#endif //RAY_BOUNDS_H
