#include"shape.h"


Bounds3f Shape::WorldBound() const
{
    return Bounds3f();
}

Shape::Shape(Material* material):material(material)
{
    //TODO: change initialize code for transformSwapHandedness
}

