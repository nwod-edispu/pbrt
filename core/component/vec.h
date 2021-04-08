#ifndef VEC_H
#define VEC_H
#include<cmath>
#include<cstdlib>
#include<cassert>


template <typename T>class Vector2
{
public:
	T x, y;

};

template <typename T>class Vector3
{
public:
	Vector3()
	{
		x = y = z = 0;
	}
	Vector3(T x, T y, T z)
		:x(x), y(y), z(z)
	{
		assert(!hasNaNs());
	}	
	bool hasNaNs() const
	{
		return std::isnan(x) || std::isnan(y) || std::isnan(z);
	}
	Vector3<T> operator+(const Vector3<T>& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	Vector3<T>& operator+=(const Vector3<T>& v)
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	}
    Vector3<T> operator-(const Vector3<T>& v) const
    {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }
    Vector3<T>& operator-=(const Vector3<T>& v)
    {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }
	Vector3<T> operator*(T s)const { return Vector3<T>(s*x, s*y, s*z); }
    Vector3<T> operator*(const Vector3<T>& v) const
    {
        return Vector3(x * v.x, y * v.y, z * v.z);
    }
	Vector3<T>& operator *= (T s)
	{
		x *= s; y *= s; z *= s;
		return *this;
	}
	Vector3<T> operator/(T f)const
	{
		assert(f != 0);
		float inv = (float)1 / f;
		return Vector3<T>(inv*x, inv*y, inv*z);
	}
	Vector3<T>& operator  /= (T f)
	{
		assert(f != 0);
		float inv = (float)1 / f;
		x *= inv; y *= inv; z *= inv;
		return *this;
	}
	Vector3<T> operator-()const
	{
		return Vector3(-x, -y, -z);
	}	
	T operator[] (int i)const
	{
		Assert(i >= 0 && i <= 2);
		if (i == 0)return x;
		if (i == 1)return y;
		return z;
	}
	T& operator[] (int i)
	{
		assert(i >= 0 && i <= 2);
		if (i == 0)return x;
		if (i == 1)return y;
		return z;
	}
	T LengthSquared() const { return x * x + y * y + z * z; }
	T Length() const { return std::sqrt(LengthSquared()); }
	T x, y, z;
};

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;


#endif