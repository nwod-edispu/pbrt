#include"utils.h"


std::default_random_engine rseed(time(nullptr));
std::uniform_real_distribution<float> randf(0.0, 1.0);

float RandFloat()
{
    return randf(rseed);
}

Vector3f RandomInUnitSphere()
{
    Vector3f v;
    do
    {
        v = Point3f(randf(rseed) * 2.0, randf(rseed) * 2.0,
                    randf(rseed) * 2.0) - Point3f(1.f, 1.f, 1.f);
    } while (v.Length() >= 1.0);
    return v;
}


Vector3f RandomInUnitDisk()
{
    Vector3f p;
    do
    {
        p = Vector3f(RandFloat(), RandFloat(), 0) * 2.0 - Vector3f(1, 1, 0);
    } while (Dot(p, p) >= 1.0);
    return p;
}

float Fmin(float a, float b)
{
    return a < b ? a : b;
}

float Fmax(float a, float b)
{
    return a > b ? a : b;
}