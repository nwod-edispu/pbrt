#ifndef RAY_MATERIAL_H
#define RAY_MATERIAL_H

#include"ray.h"
#include"../shape/shape.h"
#include"../utils/utils.h"

Vector3f reflect(const Vector3f &v, const Vector3f &n)
{
    return v - 2 * Dot(v, n) * n;
}

bool refract(const Vector3f &v, const Vector3f &n, float ni_over_nt, Vector3f &refracted)
{
    Vector3f uv = Unit(v);
    float dotnr = Dot(uv, n);
    float discrimination = 1.0 - ni_over_nt * ni_over_nt * (1 - dotnr * dotnr);
    if (discrimination <= 0)
    {
        return false;
    } else
    {
        refracted = ni_over_nt * (uv - n * dotnr) - n * std::sqrt(discrimination);
        return true;
    }
}

float schlick(float cosine, float ref_idx)
{
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow(1 - cosine, 5);
}

class Material
{
public:
    virtual bool scatter(const Ray &r_in, const hit_recorder &rec,
                         Vector3f &attenuation, Ray &scatter) const = 0;
};

class Lambertian : public Material
{
public:
    Lambertian(const Vector3f &a) : albedo(a)
    {}

    virtual bool scatter(const Ray &r_in, const hit_recorder &rec,
                         Vector3f &attenuation, Ray &scatter) const
    {
        Point3f target = rec.p + rec.normal + RandomInUnitSphere();
        scatter = Ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }

    Vector3f albedo;
};

class Metal : public Material
{
public:
    Metal(const Vector3f &a, float f) : albedo(a)
    { if (f < 0)fuzz = f; else fuzz = 1; }

    virtual bool scatter(const Ray &r_in, const hit_recorder &rec,
                         Vector3f &attenuation, Ray &scatter) const
    {
        Vector3f reflected = reflect(Unit(r_in.d), rec.normal);
//        scatter = Ray(rec.pinp, reflected + fuzz * RandomInUnitSphere());//blur
        scatter = Ray(rec.p, reflected);//blur
        attenuation = albedo;
        //TODO: why?
        return (Dot(scatter.d, rec.normal) > 0);
    }

    Vector3f albedo;
    float fuzz;
};

class Dielectric : public Material
{
public:
    Dielectric(float ri) : ref_idx(ri)
    {}

    virtual bool scatter(const Ray &r_in, const hit_recorder &rec,
                         Vector3f &attenuation, Ray &scatter) const
    {
        Vector3f outward_normal;
        Vector3f reflected = reflect(r_in.d, rec.normal);
        float ni_over_nt;
        attenuation = Vector3f(1.0, 1.0, 1.0);
        Vector3f refracted;
        float reflect_prob;
        float cosine;
        if (Dot(r_in.d, rec.normal) > 0)//refract from inner
        {
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            cosine = ref_idx * Dot(r_in.d, rec.normal) / r_in.d.Length();
        } else
        {
            outward_normal = rec.normal;
            ni_over_nt = 1.0 / ref_idx;
            cosine = -Dot(r_in.d, rec.normal) / r_in.d.Length();
        }
        if (refract(r_in.d, outward_normal, ni_over_nt, refracted))
        {
            reflect_prob = schlick(cosine, ref_idx);
        } else
        {
            reflect_prob = 1.0;
        }
        if (RandFloat() < reflect_prob)
        {
            scatter = Ray(rec.p, reflected);
        } else
        {
            scatter = Ray(rec.p, refracted);
        }
        return true;
    }

    float ref_idx;
};

#endif //RAY_MATERIAL_H
