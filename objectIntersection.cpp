#pragma once
#include "object.cpp"

class Object;

struct ObjectIntersection {
    double t;
    Vec3 <double> p, n;
    Object* o;
}