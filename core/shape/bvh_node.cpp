#include "bvh_node.h"

int BoxXCompare(const void *a, const void *b)
{
    Bounds3f left_box, right_box;
    Shape *shape_a = *(Shape **) a;
    Shape *shape_b = *(Shape **) b;
    if (!shape_a->ObjectBound(left_box) || !shape_b->ObjectBound(right_box))
    {
        std::cerr << "No Bounding Box!\n\n\n";
    }
    if (left_box.pMin.x - right_box.pMin.x < 0.0)
    {
        return -1;
    } else return 1;
}

int BoxYCompare(const void *a, const void *b)
{
    Bounds3f left_box, right_box;
    Shape *shape_a = *(Shape **) a;
    Shape *shape_b = *(Shape **) b;
    if (!shape_a->ObjectBound(left_box) || !shape_b->ObjectBound(right_box))
    {
        std::cerr << "No Bounding Box!\n\n\n";
    }
    if (left_box.pMin.y - right_box.pMin.y < 0.0)
    {
        return -1;
    } else return 1;
}

int BoxZCompare(const void *a, const void *b)
{
    Bounds3f left_box, right_box;
    Shape *shape_a = *(Shape **) a;
    Shape *shape_b = *(Shape **) b;
    if (!shape_a->ObjectBound(left_box) || !shape_b->ObjectBound(right_box))
    {
        std::cerr << "No Bounding Box!\n\n\n";
    }
    if (left_box.pMin.z - right_box.pMin.z < 0.0)
    {
        return -1;
    } else return 1;
}


BvhNode::BvhNode(Shape **l, int n) : Shape(nullptr)
{
    left = right = nullptr;
    int axis = int(RandFloat() * 3);
    if (axis == 0)
    {
        qsort(l, n, sizeof(Shape *), BoxXCompare);
    } else if (axis == 1)
    {
        qsort(l, n, sizeof(Shape *), BoxYCompare);
    } else
    {
        qsort(l, n, sizeof(Shape *), BoxZCompare);
    }
    if (n == 1)
    {
        left = right = l[0];
    } else if (n == 2)
    {
        left = l[0];
        right = l[1];
    } else
    {
        left = new BvhNode(l, n / 2);
        right = new BvhNode(l + n / 2, n - n / 2);
    }
    Bounds3f box_left, box_right;
    if (!left->ObjectBound(box_left) || !right->ObjectBound(box_right))
    {
        std::cerr << "No Bounding Box!\n\n\n";
    }
    box = SurroundingBox(box_left, box_right);
}

bool BvhNode::ObjectBound(Bounds3f &b) const
{
    b = box;
    return true;
}

bool BvhNode::Intersect(const Ray &r, float tMin, float tMax, hit_recorder &rec) const
{
    if (box.hit(r, tMin, tMax))
    {
        hit_recorder left_rec, right_rec;
        bool hit_left = left->Intersect(r, tMin, tMax, left_rec);
        bool hit_right = right->Intersect(r, tMin, tMax, right_rec);
        if (hit_left && hit_right)
        {
            rec = left_rec.t < right_rec.t ? left_rec : right_rec;
            return true;
        } else if (hit_left)
        {
            rec = left_rec;
            return true;
        } else if (hit_right)
        {
            rec = right_rec;
            return true;
        } else
        {
            return false;
        }
    } else return false;
}


