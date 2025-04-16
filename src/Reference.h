/*
    Reference is basically just a simplier implimentation of shared_ptr. it's described and used in pbrt
    so it has been implimented here, but no where in webrt is it used

    this file will most likely be deleted later
*/

#ifndef REFERENCE_H
#define REFERENCE_H

#include <memory.h>

class ReferenceCounted
{
public:
    ReferenceCounted() { references = 0; }
    int references;
private:
    ReferenceCounted(const ReferenceCounted&);
    ReferenceCounted& operator=(const ReferenceCounted&);
};

template <class T> class Reference
{
public:
    Reference(T* p = NULL)
    {
        ptr = p;
        if(ptr) ++ptr->references;
    }
    Reference(const Reference<T>& r)
    {
        ptr = r.ptr;
        if(ptr) ++ptr->references;
    }
    
    Reference& operator=(const Reference<T> &r)
    {
        if(r.ptr) r.ptr->references++;
        if(ptr && --ptr->references == 0) delete ptr;
        ptr = r.ptr;

        return *this;
    }
    Reference& operator=(T* p)
    {
        if(p) p->references++;
        if(ptr && --ptr->references == 0) delete ptr;
        ptr = p;

        return *this;
    }
    ~Reference()
    {
        if(ptr && --ptr->references == 0) delete ptr;
    }
private:
    T* ptr;
};

#endif