#pragma once

#include "ray.cpp"
#include "objectIntersection.cpp"
#include <cmath>

// class Geometry{
//     public:
//         virtual bool intersect(const Ray& r, ObjectIntersection* info = nullptr) const = 0;

//         virtual Vec3 <double> getPoint();

// };

class Sphere {
    private:
        Vec3 <double> center;
        double radius;
    
    public:


        Sphere() {
            Vec3 <double> a;
            this->center = a;
            this->radius = 0;
        }
    
        Sphere(Vec3 <double> center, double radius) {
            this->center = center;
            this->radius = radius;
        }

        //bool intersect(const Ray& r, ObjectIntersection* info = nullptr);

        Vec3 <double> getPoint(){
            return this->center;
        }

        double getRadius() {
            return this->radius;
        }
}