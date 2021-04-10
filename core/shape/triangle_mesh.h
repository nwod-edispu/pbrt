#ifndef RAY_TRIANGLE_MESH_H
#define RAY_TRIANGLE_MESH_H

#include<vector>
#include"shape.h"


class TriangleMesh
{
public:
    TriangleMesh(Material *material);

    std::vector<Point3f> vertices;
    std::vector<Vector3f> normals;
    std::vector<int> vertexIndices;
    std::vector<int> normalIndices;
    Material* material;
};


#endif //RAY_TRIANGLE_MESH_H
