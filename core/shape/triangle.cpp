//
// Created by h'p on 2021/4/8.
//

#include "triangle.h"


Triangle::Triangle(Material *material, TriangleMesh *mesh, int triNumber)
        : Shape(material), mesh_ptr(mesh)
{
    v = 3 * triNumber;

}

bool Triangle::Intersect(const Ray &r, float tMin, float tMax, hit_recorder &rec) const
{
    const Point3f &p0 = mesh_ptr->vertices[mesh_ptr->vertexIndices[v]];
    const Point3f &p1 = mesh_ptr->vertices[mesh_ptr->vertexIndices[v + 1]];
    const Point3f &p2 = mesh_ptr->vertices[mesh_ptr->vertexIndices[v + 2]];
    Vector3f v01 = p1 - p0;
    Vector3f v12 = p2 - p1;
    Vector3f v20 = p0 - p2;
    Vector3f normal = (mesh_ptr->normals[mesh_ptr->normalIndices[v]] +
                       mesh_ptr->normals[mesh_ptr->normalIndices[v + 1]] +
                       mesh_ptr->normals[mesh_ptr->normalIndices[v + 2]]) / 3.0;
    rec.mat_ptr = material;
    float t = Dot(p0 - r.o, normal) / Dot(r.d, normal);
    if (t > tMin && t < tMax)
    {
        rec.t = t;
        rec.p = r.point_at_parameter(t);
        rec.normal = normal;
        Vector3f v0 = rec.p - p0, v1 = rec.p - p1, v2 = rec.p - p2;
        Vector3f cv0 = Cross(v0, v01), cv1 = Cross(v1, v12), cv2 = Cross(v2, v20);
        return SameSide(cv0, cv1) && SameSide(cv1, cv2);
    }
    return false;
}

bool Triangle::ObjectBound(Bounds3f &box) const
{
    const Point3f &p0 = mesh_ptr->vertices[mesh_ptr->vertexIndices[v]];
    const Point3f &p1 = mesh_ptr->vertices[mesh_ptr->vertexIndices[v + 1]];
    const Point3f &p2 = mesh_ptr->vertices[mesh_ptr->vertexIndices[v + 2]];
    const Vector3f bias = Vector3f(0.000001, 0.000001, 0.000001);
    auto small = Min(p0, Min(p1, p2)) - bias;
    auto big = Max(p0, Max(p1, p2)) + bias;
    box = Bounds3f(small, big);
    return true;
}
