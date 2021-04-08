#ifndef RAY_TRIANGLE_H
#define RAY_TRIANGLE_H

#include"shape.h"
#include"triangle_mesh.h"

class Triangle : public Shape
{
public:
    Triangle(Material *material, TriangleMesh* mesh, int triNumber);

    bool intersect(const Ray &r, float tMin, float tMax, hit_recorder &rec) const override;
    Bounds3f ObjectBound() const override;
    int v;
//    Point3f p0, p1, p2;
//    Vector3f normal;
//    Vector3f v01, v12, v20;
    TriangleMesh* mesh_ptr;
};


#endif //RAY_TRIANGLE_H
