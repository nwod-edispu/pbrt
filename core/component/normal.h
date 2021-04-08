#ifndef NORMAL_H
#define NORMAL_H
#include"vec.h"

template <typename T> class Normal3
{
public:
	explicit Normal3<T>(const Vector3<T>& v) : x(v.x), y(v.y), z(v.z)
	{
		Assert(v.hasNaNs());
	}
	T x, y, z;
};

typedef Normal3<float> Normal3f;
#endif
