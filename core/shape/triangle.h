#ifndef RAY_TRIANGLE_H
#define RAY_TRIANGLE_H

#include"triangle_mesh.h"

class Triangle : public Shape
{
public:
    Triangle(Material *material, TriangleMesh* mesh, int triNumber);

    bool Intersect(const Ray &r, float tMin, float tMax, hit_recorder &rec) const override;
    bool ObjectBound(Bounds3f &box) const override;
    int v;
    TriangleMesh* mesh_ptr;
};


#endif //RAY_TRIANGLE_H
