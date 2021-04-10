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

float RandFloat();

Vector3f RandomInUnitSphere();

Vector3f RandomInUnitDisk();

inline float Fmin(float a, float b);

inline float Fmax(float a, float b);


#endif //RAY_UTILS_H
