#include"core/tracer.h"


int main()
{
    char output[50] = "out.ppm";
    char objFile[50] = "../resources/test.obj";
    int canvasX = 200;
    int canvasY = 100;
    int sampleNum = 100;
    trace(output, objFile, false, canvasX, canvasY, sampleNum);
}