#ifndef RAY_SHAPE_LIST_H
#define RAY_SHAPE_LIST_H

#include"shape.h"

class ShapeList
{
public:
    ShapeList(Shape **l, int n)
    {
        list = l;
        list_size = n;
    }

    bool hit(const Ray &r, float tMin, float tMax, hit_recorder &rec) const;

    Shape **list;
    int list_size;
};

bool ShapeList::hit(const Ray &r, float tMin, float tMax, hit_recorder &rec) const
{
    hit_recorder temp_rec;
    bool hit_anything = false;
    float closest_so_far = tMax;
    for (int i = 0; i < list_size; i++)
    {
        if (list[i]->intersect(r, tMin, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif //RAY_SHAPE_LIST_H
