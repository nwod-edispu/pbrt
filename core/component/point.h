#ifndef POINT_H
#define POINT_H

#include"vec.h"

template<typename T>
class Point3
{
public:
    T x, y, z;

    Point3()
    {
        x = y = z = 0;
    }

    Point3(T x, T y, T z) : x(x), y(y), z(z)
    {
        assert(!HasNaNs());
    }

    bool HasNaNs() const
    {
        return std::isnan(x) || std::isnan(y) || std::isnan(z);
    }

    template<typename U>
    explicit Point3(const Point3<U> &p)
            :x((T) p.x), y((T) p.y), z((T) p.z)
    {
        assert(!HasNaNs());
    }

    Point3<T> operator+(const Vector3<T> &v) const
    {
        return Point3<T>(x + v.x, y + v.y, z + v.z);
    }

    Point3<T> &operator+=(const Vector3<T> &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Point3<T> operator-(const Vector3<T> &v) const
    {
        return Point3<T>(x - v.x, y - v.y, z - v.z);
    }

    Vector3<T> operator-(const Point3<T> &p) const
    {
        return Vector3<T>(x - p.x, y - p.y, z - p.z);
    }

    Point3<T> &operator-=(const Vector3<T> &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
};

template<typename T>
class Point2
{
public:
    T x, y;

    Point2()
    {
        x = y = 0;
    }

    Point2(T x, T y) : x(x), y(y)
    {
        assert(!HasNaNs());
    }

    bool HasNaNs() const
    {
        return std::isnan(x) || std::isnan(y);
    }

    explicit Point2(const Point3 <T> &p) : x(p.x), y(p.y)
    {
        assert(!HasNaNs());
    }
};

typedef Point2<float> Point2f;
typedef Point2<int> Point2i;
typedef Point3<float> Point3f;
typedef Point3<int> Point3i;
#endif
