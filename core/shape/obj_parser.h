#ifndef RAY_OBJ_PARSER_H
#define RAY_OBJ_PARSER_H

#include<fstream>
#include"../component/material.h"
#include"triangle.h"

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
    mesh->vertices.emplace_back(0,0,0);
    float f1, f2, f3;
    int triNum = 0;
    while (in.getline(buffer, 255))
    {
        if (buffer[0] == 'v' && buffer[1] == ' ')
        {
            if (sscanf_s(buffer, "v %f %f %f", &f1, &f2, &f3) == 3)
            {
                mesh->vertices.emplace_back(f1, f2, f3);
            } else
            {
                std::cout << "error parsing " << buffer << std::endl;
                exit(-1);
            }
        } else if (buffer[0] == 'f' && buffer[1] == ' ')
        {
            for(int i=0;i<3;i++)
            {
                mesh->vertexIndices.push_back(0);
            }

            int tmp = 0;
            if (sscanf_s(buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d",
                         &mesh->vertexIndices[3 * triNum], &tmp, &tmp,
                         &mesh->vertexIndices[3 * triNum + 1], &tmp, &tmp,
                         &mesh->vertexIndices[3 * triNum + 2], &tmp, &tmp) == 9)
            {
                list[cnt++] = new Triangle(mesh->material, mesh, triNum);
            } else
            {
                std::cout << "error parsing " << buffer << std::endl;
                exit(-1);
            }
            triNum += 1;
        }
    }
//    for(int i=0;i<mesh->vertexIndices.size();i++)
//        std::cout<<mesh->vertexIndices[i]<<std::endl;
//    std::cout<<mesh->vertices.size()<<std::endl;
//    std::cout<<mesh->vertexIndices.size()<<std::endl;
}

void RandomScene(Shape **list, int &cnt)
{
    //    list[0] = new Sphere(nullptr, nullptr, false, new Lambertian(Vector3f(0.5, 0.5, 0.5)),
//                         Point3f(0, -1000, 0), 1000);
    list[0] = new Plane(new Lambertian(Vector3f(0.5, 0.5, 0.5)),
                        Vector3f(0, 1, 0), Point3f(0, 0, 0));
    //    for (int a = -11; a < 11; a++)
//    {
//        for (int b = -11; b < 11; b++)
//        {
//            float choose_mat = RandFloat();
//            Point3f center(a + 0.9 * RandFloat(), 0.2, b + 0.9 * RandFloat());
//            if ((center - Point3f(4, 0.2, 0)).Length() > 0.9)
//            {
//                if (choose_mat < 0.8)
//                {
//                    list[cnt++] = new Sphere(new Lambertian(Vector3f(RandFloat() * RandFloat(),
//                                                                     RandFloat() * RandFloat(),
//                                                                     RandFloat() * RandFloat())),
//                                             center, 0.2);
//                } else if (choose_mat < 0.95)
//                {
//                    list[cnt++] = new Sphere(new Metal(Vector3f(0.5 * (1 + RandFloat()),
//                                                                0.5 * (1 + RandFloat()),
//                                                                0.5 * (1 + RandFloat())),
//                                                       0.5 * RandFloat()),
//                                             center, 0.2);
//                } else
//                {
//                    list[cnt++] = new Sphere(new Dielectric(1.5), center, 0.2);
//                }
//            }
//        }
//    }
//    list[cnt++] = new Cylinder(nullptr, nullptr, false,new Metal(Vector3f(0.4, 0.8, 0.1), 0.0),
//                               Point3f(2, 1, 2), 1, 0, 2);
//    list[cnt++] = new Triangle(new Lambertian(Vector3f(0.9, 0.1, 0.1)),
//                               Point3f(-4, 1, 0), Point3f(-3, 2, 1), Point3f(-4, 3, 1));
//    list[cnt++] = new Sphere(new Lambertian(Vector3f(0.4, 0.2, 0.1)),
//                             Point3f(-4, 1, 0), 1);
//    list[cnt++] = new Sphere(new Dielectric(1.5),
//                             Point3f(0, 1, 0), 1.0);
//    list[cnt++] = new Cylinder(new Metal(Vector3f(0.7, 0.6, 0.5), 0.0),
//                               Point3f(4, 1, 0), 0.9, 0, 2);
//    char s[50] = "G:/workplace/ray/resources/test.obj";
    char s[50] = "G:/workplace/ray/resources/Wood_Table.obj";
    LoadObj(s, list, cnt);
}

#endif //RAY_OBJ_PARSER_H
