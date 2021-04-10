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

    bool Intersect(const Ray &r, float tMin, float tMax, hit_recorder &rec) const;

    bool ObjectBound(Bounds3f &box) const;

    Shape **list;
    int list_size;
};

bool ShapeList::Intersect(const Ray &r, float tMin, float tMax, hit_recorder &rec) const
{
    hit_recorder temp_rec;
    bool hit_anything = false;
    float closest_so_far = tMax;
    for (int i = 0; i < list_size; i++)
    {
        if (list[i]->Intersect(r, tMin, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

bool ShapeList::ObjectBound(Bounds3f &box) const
{
    if (list_size < 1)return false;
    Bounds3f tmp_box;
    bool ret=list[0]->ObjectBound(tmp_box);
    if(!ret)return false;
    for(int i=1;i<list_size;i++)
    {
        ret&=list[i]->ObjectBound(tmp_box);
        if(!ret)return false;
        else box=SurroundingBox(tmp_box, box);
    }
    return true;
}

#endif //RAY_SHAPE_LIST_H
