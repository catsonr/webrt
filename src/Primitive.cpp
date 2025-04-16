#include "Primitive.h"

void Primitive::fullyRefine(std::vector<std::shared_ptr<Primitive>>& refined) const
{
    std::vector<std::shared_ptr<Primitive>> todo;
    todo.push_back(std::const_pointer_cast<Primitive>(shared_from_this()));

    while(todo.size())
    {
        std::shared_ptr<Primitive> prim = todo.back();
        todo.pop_back();

        if(prim->canIntersect())
            refined.push_back(prim);
        else
            prim->refine(todo);
    }
}