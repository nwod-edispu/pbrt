#ifndef RAY_CAMERA_H
#define RAY_CAMERA_H
#include"geometry.h"
#include"ray.h"

class Camera
{
public:
    Camera(Point3f lookfrom, Point3f lookat, Vector3f vup, float vfov, float aspect,
           float aperture, float focus_dist)
    {
        lens_radius = aperture / 2;
        float theta = vfov * PI / 180;
        float half_height = std::tan(theta / 2);
        float half_width = aspect * half_height;
        origin = lookfrom;
        w = Unit(lookfrom - lookat);
        u = Unit(Cross(vup, w));
        v = Cross(w, u);
        lower_left_corner = origin - half_width * focus_dist * u -
                            half_height * focus_dist * v - focus_dist * w;
        horizontal = 2 * half_width * focus_dist * u;
        vertical = 2 * half_height * focus_dist * v;
    }

    Ray get_ray(float s, float t)
    {
        Vector3f rd = lens_radius * RandomInUnitDisk();
        Vector3f offset = u * rd.x + v * rd.y;
        //random point on lens
        return Ray(origin + offset, lower_left_corner + horizontal * s
                                    + vertical * t - origin - offset);
    }

    Point3f lower_left_corner;
    Vector3f horizontal;
    Vector3f vertical;
    Point3f origin;
    Vector3f u, v, w;
    float lens_radius;
};

#endif //RAY_CAMERA_H
