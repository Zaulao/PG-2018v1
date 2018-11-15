#pragma once

#include "ray.cpp"
//#include "objectIntersection.cpp"
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
        Sphere(Vec3 <double> center, double radius) {
            this->center = center;
            this->radius = radius;
        }

        bool intersect(Ray *r) {
            double t;
            Vec3 <double> distance = r->getOrigin().operator-(this->center);
            double a = Vec3<double>::dotProduct(r->getDirection(), r->getDirection());
            double b = 2 * Vec3<double>::dotProduct(distance, r->getDirection());
            double c = Vec3<double>::dotProduct(distance, distance) - (this->radius * this->radius);
            double delta = b * b - 4 * a * c;
            return (delta > 0);
        }

        Vec3 <int> color(Ray *r) {
            Vec3 <int> white(255, 255, 255);
            Vec3 <int> red(0, 0, 0);
            if(intersect(r)) {
                return white;
            }
            return red;
        }

        Vec3 <double> getPoint(){
            return this->center;
        }

        double getRadius() {
            return this->radius;
        }
};