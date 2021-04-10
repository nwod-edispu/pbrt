#ifndef RAY_TRACER_H
#define RAY_TRACER_H

#include"component/camera.h"
#include"shape/sphere.h"
#include"shape/triangle.h"
#include"shape/obj_parser.h"
#include"shape/bvh_node.h"
#include"shape/shape_list.h"

Vector3f color(const Ray &r, Shape *world, int depth)
{
    hit_recorder rec;
    if (world->Intersect(r, 0.001, Infinity, rec))
    {
        Ray scatter;
        Vector3f attenuation;
        if (depth < 20 && rec.mat_ptr->scatter(r, rec, attenuation, scatter))
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
    Point3f lookfrom = Point3f(5, 3, 1);
    Point3f lookat = Point3f(0, 0.1, 0);
    float disk_to_focus = (lookfrom - lookat).Length();
    float aperture = 0.0;
    Camera cam(lookfrom, lookat, Vector3f(0, 1, 0), 20,
               nx / ny, aperture, 0.7 * disk_to_focus);
    return cam;
}


void trace(char *outputFile, char *objFile, bool isSimpleObj,
           const int nx, const int ny, const int ns)
{
    std::ofstream out(outputFile);
    out << "P3\n" << nx << " " << ny << "\n255\n";

    int n = 70000;
    auto **list = new Shape *[n + 1];

    int cnt = 0;
    initSceneWithObj(objFile, list, cnt, isSimpleObj);
    auto head = new BvhNode(list, cnt);

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
                col += color(r, head, 0);
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

#endif //RAY_TRACER_H
