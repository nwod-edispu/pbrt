#ifndef GEOMETRY_H
#define GEOMETRY_H

#include"vec.h"
#include"point.h"
#include"normal.h"
#include"bounds.h"


template<typename T>
inline Vector3<T> operator*(T s, const Vector3<T> &v)
{
    return v * s;
}

template<typename T>
Vector3<T> Abs(const Vector3<T> &v)
{
    return Vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}

template<typename T>
inline T Dot(const Vector3<T> &v1, const Vector3<T> &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template<typename T>
inline T AbsDot(const Vector3<T> &v1, const Vector3<T> &v2)
{
    return std::abs(Dot(v1, v2));
}

template<typename T>
inline Vector3<T> Cross(const Vector3<T> &v1, const Vector3<T> &v2)
{
    double x1 = v1.x, y1 = v1.y, z1 = v1.z;
    double x2 = v2.x, y2 = v2.y, z2 = v2.z;
    return Vector3<T>(
            y1 * z2 - z1 * y2,
            z1 * x2 - z2 * x1,
            x1 * y2 - y1 * x2
    );
}

template<typename T>
T MinComponent(const Vector3<T> &v)
{
    return std::min(v.x, std::min(v.y, v.z));
}

template<typename T>
T MaxComponent(const Vector3<T> &v)
{
    return std::max(v.x, std::max(v.y, v.z));
}

template<typename T>
T MaxDimension(const Vector3<T> &v)
{
    return (v.x > v.y) ? ((v.x > v.z) ? 0 : 2) :
           (v.y > v.z) ? 1 : 2;
}

template<typename T>
Vector3<T> Min(Vector3<T> &p1, Vector3<T> &p2)
{
    return Vector3<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y),
                      std::min(p1.z, p2.z));
}

template<typename T>
Vector3<T> Max(Vector3<T> &p1, Vector3<T> &p2)
{
    return Vector3<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
                      std::max(p1.z, p2.z));
}

template<typename T>
Vector3<T> Permute(const Vector3<T> &v, int x, int y, int z)
{
    return Vector3<T>(v[x], v[y], v[z]);
}

template<typename T>
Vector3<T> Unit(const Vector3<T> &v)
{
    return v / v.Length();
}

//
//template <typename T> inline
//Vector3<T>::Vector3(const Normal3<T>& normal):x(normal.x), y(normal.y), z(normal.z)
//{
//
//}
/**********************
Point
**********************/
template<typename T>
inline float
Distance(const Point3<T> &p1, const Point3<T> &p2)
{
    return (p1 - p2).Length();
}

template<typename T>
inline float
SquaredDistance(const Point3<T> &p1, const Point3<T> &p2)
{
    return (p1 - p2).SquaredLength();
}

template<typename T>
Point3<T> Lerp(float t, const Point3<T> &p1, const Point3<T> &p2)
{
    return (1 - t) * p1 + t * p2;
}

template<typename T>
Point3<T> Min(const Point3<T> &p1, const Point3<T> &p2)
{
    return Point3<T>(std::min(p1.x, p2.x),
                     std::min(p1.y, p2.y), std::min(p1.z, p2.z));
}

template<typename T>
Point3<T> Max(const Point3<T> &p1, const Point3<T> &p2)
{
    return Point3<T>(std::max(p1.x, p2.x),
                     std::max(p1.y, p2.y), std::max(p1.z, p2.z));
}

template<typename T>
Point3<T> Floor(const Point3<T> &p1, const Point3<T> &p2)
{
    return Point3<T>(std::floor(p1.x, p2.x),
                     std::floor(p1.y, p2.y), std::floor(p1.z, p2.z));
}

template<typename T>
Point3<T> Ceil(const Point3<T> &p1, const Point3<T> &p2)
{
    return Point3<T>(std::ceil(p1.x, p2.x),
                     std::ceil(p1.y, p2.y), std::ceil(p1.z, p2.z));
}

template<typename T>
Point3<T> Abs(const Point3<T> &p1, const Point3<T> &p2)
{
    return Point3<T>(std::abs(p1.x, p2.x),
                     std::abs(p1.y, p2.y), std::abs(p1.z, p2.z));
}

template<typename T>
Point3<T> Permute(const Point3<T> &p, int x, int y, int z)
{
    return Point3<T>(p[x], p[y], p[z]);
}

/**********************
Normal
**********************/
template<typename T>
Normal3<T> Abs(const Normal3<T> &n)
{
    return Vector3<T>(std::abs(n.x), std::abs(n.y), std::abs(n.z));
}

template<typename T>
inline T Dot(const Normal3<T> &n, const Vector3<T> &v)
{
    return n.x * v.x + n.y * v.y + n.z * v.z;
}

template<typename T>
inline T AbsDot(const Normal3<T> &n, const Vector3<T> &v)
{
    return std::abs(Dot(n, v));
}

template<typename T>
inline Normal3<T> Faceforward(const Normal3<T> &n, const Vector3<T> &v)
{
    return Dot(n, v) < 0 ? -n : n;
}

template<typename T>
inline bool SameSide(const Vector3<T> &v1, const Vector3<T> &v2)
{
    return Dot(v1, v2) >= 0;
}
//
//template<typename T>
//inline bool Bounds3<T>::IntersectP(const Ray &ray, float *hitt0,
//                                   float *hitt1) const
//{
//    float t0 = 0, t1 = ray.tMax;
//    for (int i = 0; i < 3; i++)
//    {
//        float di = (float) 1 / ray.d[i];
//        float tnear = (this->pMin[i] - ray.o[i]) * di;
//        float tfar = (this->pMax[i] - ray.o[i]) * di;
//        if (tnear > tfar)std::swap(tnear, tfar);
//        t0 = tnear > t0 ? tnear : t0;
//        t1 = tfar < t1 ? tfar : t1;
//        if (t0 > t1)return false;
//    }
//    if (hitt0)*hitt0 = t0;
//    if (hitt1)*hitt1 = t1;
//    return true;
//}

#endif
