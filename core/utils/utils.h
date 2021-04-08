#ifndef RAY_UTILS_H
#define RAY_UTILS_H
#include<cassert>
#include<random>
#include<ctime>
#include<cmath>
#include<iostream>
#include<fstream>
#include<climits>
#include"../component/geometry.h"
#define PI 3.141593
#define Infinity INT_MAX

float RandFloat();

Vector3f RandomInUnitSphere();

Vector3f RandomInUnitDisk();

#endif //RAY_UTILS_H
