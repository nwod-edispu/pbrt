cmake_minimum_required(VERSION 3.17)
project(ray)

set(CMAKE_CXX_STANDARD 14)

add_executable(ray main.cpp core/shape/shape.h core/component/transform.h core/component/bounds.h core/shape/shape.cpp core/shape/sphere.cpp core/shape/sphere.h core/component/camera.h core/shape/shape_list.h core/utils/utils.h core/component/material.h core/utils/utils.cpp core/shape/plane.cpp core/shape/plane.h core/shape/cylinder.cpp core/shape/cylinder.h core/shape/disk.cpp core/shape/disk.h core/shape/triangle.cpp core/shape/triangle.h core/shape/obj_parser.h core/shape/triangle_mesh.h core/shape/triangle_mesh.cpp core/shape/bvh_node.cpp core/shape/bvh_node.h core/utils/const.h)