#include"core/component/camera.h"
#include"core/shape/sphere.h"
#include"core/shape/plane.h"
#include"core/shape/cylinder.h"
#include"core/shape/triangle.h"
#include"core/shape/obj_parser.h"
#include"core/shape/shape_list.h"
#include"core/component/material.h"


Vector3f color(const Ray &r, ShapeList *world, int depth)
{
    hit_recorder rec;
    if (world->hit(r, 0.001, Infinity, rec))
    {
        Ray scatter;
        Vector3f attenuation;
        if (depth < 5 && rec.mat_ptr->scatter(r, rec, attenuation, scatter))
        {
            return attenuation * color(scatter, world, depth + 1);
        } else
        {
            return {0, 0, 0};
        }
    } else
    {
        Vector3f unit_direction = Unit(r.d);
        float t = 0.5 * (unit_direction.y + 1.0);
        return ((float) 1.0 - t) * Vector3f(1.0, 1.0, 1.0) +
               t * Vector3f(0.5, 0.7, 1.0);
    }
}


Camera getCamera(float nx, float ny)
{
    Point3f lookfrom = Point3f(5, 2.5, 3);
    Point3f lookat = Point3f(0, 0.6, 0);
    float disk_to_focus = (lookfrom - lookat).Length();
    float aperture = 0.0;
    Camera cam(lookfrom, lookat, Vector3f(0, 1, 0), 20,
               nx / ny, aperture, 0.7 * disk_to_focus);
    return cam;
}

int main()
{
    std::ofstream out("a.ppm");
    const int nx = 200;
    const int ny = 100;
    const int ns = 30;
    out << "P3\n" << nx << " " << ny << "\n255\n";

    int n = 500;
    Shape **list = new Shape *[n + 1];
    int cnt = 1;
    RandomScene(list, cnt);

    auto *world = new ShapeList(list, cnt);
    Camera cam = getCamera(nx, ny);
    for (int j = ny - 1; j >= 0; j--)
    {
        std::cout << "j:" << j << std::endl;
        for (int i = 0; i < nx; i++)
        {
            Vector3f col(0.f, 0.f, 0.f);
            for (int s = 0; s < ns; s++)
            {
                float u = float(i + RandFloat()) / float(nx);
                float v = float(j + RandFloat()) / float(ny);
                Ray r = cam.get_ray(u, v);
                col += color(r, world, 0);
            }
            col /= float(ns);
            //gamma correct
            col = Vector3f(std::sqrt(col[0]), std::sqrt(col[1]), std::sqrt(col[2]));
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            out << ir << " " << ig << " " << ib << "\n";
        }
    }
}