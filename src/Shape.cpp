#include "Shape.h"

Shape::Shape(const Transform& T_objectToWorld, bool reverseOrientation) :
    object_to_world(T_objectToWorld),
    world_to_object(T_objectToWorld.mInv),
    reverseOrientation(reverseOrientation),
    transformSwapsHandedness(object_to_world.swapsHandedness())
{
}