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

        double intersect(Ray *r) {
            double t;
            Vec3 <double> distance = r->getOrigin().operator-(this->center);
            double a = Vec3<double>::dotProduct(r->getDirection(), r->getDirection());
            double b = 2 * Vec3<double>::dotProduct(distance, r->getDirection());
            double c = Vec3<double>::dotProduct(distance, distance) - (this->radius * this->radius);
            double delta = b * b - 4 * a * c;
            if (delta < 0) {
                return -1.0;
            } else {
                return (-b - sqrt(delta) ) / (2.0 * a);
            }
        }

        Vec3 <double> color(Ray *r) {
            double t = intersect(r);
            if(t > 0.0) {
                Vec3 <double> N = r->sample(t).operator-(this->center);
                N.normalise();
                Vec3 <double> v(0.5 * (N.getX() + 1) * 255, 0.5 * (N.getY() + 1) * 255, 0.5 * (N.getZ() + 1) * 255); 
                return v;
            }
            Vec3 <double> white(255, 255, 255);
            Vec3 <double> red(0, 0, 0);
            return red;
        }

        Vec3 <double> getPoint(){
            return this->center;
        }

        double getRadius() {
            return this->radius;
        }
};