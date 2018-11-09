#pragma once

#include "geometry.cpp"
#include "material.cpp"
#include "objectIntersection.cpp"

class Object{
    public: 
        Sphere geometry;
        //Material* material;

    public:
    //, Material*material//
        Object(Sphere geometry) {
            this->geometry = geometry;
            //this->material = material;
        }

        bool intersect(Ray &r, ObjectIntersection* info = nullptr) {
            for(double t = r.tmin; t < r.tmax; t+=0.1) {
                Vec3 <double> point = r.sample(t);
                Vec3 <double> subtract = point.operator-(this->geometry.getPoint());
                double a = subtract.dotProduct(subtract);
                double rad = this->geometry.getRadius() * this->geometry.getRadius();
                if( a == rad ) {
                    info->t = t;
                    Object *clone = new Object(this->geometry);
                    info->o = clone;
                    info->p = point;
                    return true;
                }
            }
            return false;
        }
};