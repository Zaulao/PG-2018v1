#pragma once
#include "Object.h"
#include "ObjectIntersection.h"
#include <vector>
using namespace std;
class Scene{
    private: vector<Object*> objects;

    public:

        bool intersect(const Ray& r, ObjectIntersection* info = nullptr)const;

        Vec3 trace(const Ray& r, int recursionlevel = 0) const;

        void add(Object* object)

};