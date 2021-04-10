#ifndef RAY_OBJ_PARSER_H
#define RAY_OBJ_PARSER_H

#include<fstream>
#include"../component/material.h"
#include"triangle.h"
#include"cylinder.h"

void parseV(TriangleMesh *mesh, char *buffer)
{
    float f1, f2, f3;
    if (sscanf_s(buffer, "v %f %f %f", &f1, &f2, &f3) == 3)
    {
        mesh->vertices.emplace_back(f1, f2, f3);
    } else
    {
        std::cout << "error parsing " << buffer << std::endl;
        exit(-1);
    }
}

void parseVN(TriangleMesh *mesh, char *buffer)
{
    float f1, f2, f3;
    if (sscanf_s(buffer, "vn %f %f %f", &f1, &f2, &f3) == 3)
    {
        mesh->normals.emplace_back(f1, f2, f3);
    } else
    {
        std::cout << "error parsing " << buffer << std::endl;
        exit(-1);
    }
}

void parseSimpleF(TriangleMesh *mesh, char *buffer,
                  Shape **list, int &cnt, const int triNum)
{
    for (int i = 0; i < 3; i++)
    {
        mesh->vertexIndices.push_back(0);
    }

    if (sscanf_s(buffer, "f %d %d %d",
                 &mesh->vertexIndices[3 * triNum],
                 &mesh->vertexIndices[3 * triNum + 1],
                 &mesh->vertexIndices[3 * triNum + 2]) == 3)
    {
        list[cnt++] = new Triangle(mesh->material, mesh, triNum, false);
    } else
    {
        std::cout << "error parsing " << buffer << std::endl;
        exit(-1);
    }
}

void parseF(TriangleMesh *mesh, char *buffer,
            Shape **list, int &cnt, const int triNum)
{
    for (int i = 0; i < 3; i++)
    {
        mesh->vertexIndices.push_back(0);
        mesh->normalIndices.push_back(0);
    }

    int tmp = 0;
    if (sscanf_s(buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                 &mesh->vertexIndices[3 * triNum], &tmp, &mesh->normalIndices[3 * triNum],
                 &mesh->vertexIndices[3 * triNum + 1], &tmp, &mesh->normalIndices[3 * triNum + 1],
                 &mesh->vertexIndices[3 * triNum + 2], &tmp, &mesh->normalIndices[3 * triNum + 2]) == 9)
    {
        list[cnt++] = new Triangle(mesh->material, mesh, triNum, true);
    } else
    {
        std::cout << "error parsing " << buffer << std::endl;
        exit(-1);
    }
}

void LoadObj(char *filename, Shape **list, int &cnt)
{
    std::ifstream in(filename);

    if (!in.good())
    {
        std::cout << "ERROR: loading obj:(" << filename << ") file is not good" << "\n";
        exit(0);
    }

    char buffer[256];
    auto mesh = new TriangleMesh(new Lambertian(Vector3f(0.9, 0.1, 0.1)));
    mesh->vertices.emplace_back(0, 0, 0);
    mesh->normals.emplace_back(0, 0, 0);

    int triNum = 0;
    while (in.getline(buffer, 255))
    {
        if (buffer[0] == 'v' && buffer[1] == ' ')
        {
            parseV(mesh, buffer);
        } else if (buffer[0] == 'v' && buffer[1] == 'n' && buffer[2] == ' ')
        {
            parseVN(mesh, buffer);
        } else if (buffer[0] == 'f' && buffer[1] == ' ')
        {
            parseF(mesh, buffer, list, cnt, triNum);
            triNum += 1;
        }
    }
}

void LoadSimpleObj(char *filename, Shape **list, int &cnt)
{
    std::ifstream in(filename);

    if (!in.good())
    {
        std::cout << "ERROR: loading obj:(" << filename << ") file is not good" << "\n";
        exit(0);
    }

    char buffer[256];
    auto mesh = new TriangleMesh(new Lambertian(Vector3f(0.9, 0.1, 0.1)));
    mesh->vertices.emplace_back(0, 0, 0);

    int triNum = 0;
    while (in.getline(buffer, 255))
    {
        if (buffer[0] == 'v' && buffer[1] == ' ')
        {
            parseV(mesh, buffer);
        } else if (buffer[0] == 'v' && buffer[1] == 'n' && buffer[2] == ' ')
        {
            parseVN(mesh, buffer);
        } else if (buffer[0] == 'f' && buffer[1] == ' ')
        {
            parseSimpleF(mesh, buffer, list, cnt, triNum);
            triNum += 1;
        }
    }
}

void initSceneWithObj(char *objFile, Shape **list, int &cnt, bool isSimpleObj)
{
    if(isSimpleObj)LoadSimpleObj(objFile, list, cnt);
    else LoadObj(objFile, list, cnt);
    std::cout << "There are " << cnt << " triangle faces in obj file.\n";
}

void RandomScene(Shape **list, int &cnt)
{
    list[cnt++] = new Sphere(new Lambertian(Vector3f(0.5, 0.5, 0.5)),
                             Point3f(0, -1000, 0), 1000);

//    list[0] = new Plane(new Lambertian(Vector3f(0.5, 0.5, 0.5)),
//                        Vector3f(0, 1, 0), Point3f(0, 0, 0));
        for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            float choose_mat = RandFloat();
            Point3f center(a + 0.9 * RandFloat(), 0.2, b + 0.9 * RandFloat());
            if ((center - Point3f(4, 0.2, 0)).Length() > 0.9)
            {
                if (choose_mat < 0.8)
                {
                    list[cnt++] = new Sphere(new Lambertian(Vector3f(RandFloat() * RandFloat(),
                                                                     RandFloat() * RandFloat(),
                                                                     RandFloat() * RandFloat())),
                                             center, 0.2);
                } else if (choose_mat < 0.95)
                {
                    list[cnt++] = new Sphere(new Metal(Vector3f(0.5 * (1 + RandFloat()),
                                                                0.5 * (1 + RandFloat()),
                                                                0.5 * (1 + RandFloat())),
                                                       0.5 * RandFloat()),
                                             center, 0.2);
                } else
                {
                    list[cnt++] = new Sphere(new Dielectric(1.5), center, 0.2);
                }
            }
        }
    }
    list[cnt++] = new Cylinder(new Metal(Vector3f(0.4, 0.8, 0.1), 0.0),
                               Point3f(2, 1, 2), 1, 0, 2);
    list[cnt++] = new Sphere(new Lambertian(Vector3f(0.9, 0.2, 0.1)),
                             Point3f(-4, 1, 0), 1);
    list[cnt++] = new Sphere(new Lambertian(Vector3f(0.9, 0.9, 0.1)),
                             Point3f(0, 1, 0), 1.0);
    list[cnt++] = new Sphere(new Lambertian(Vector3f(0.4, 0.2, 0.1)),
                             Point3f(0, 3, 0), 1.0);
}

#endif //RAY_OBJ_PARSER_H
