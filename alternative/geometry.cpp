#pragma once

#include "ray.cpp"
#include "hit_record.cpp"
#include "material.cpp"
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
        Material *material;
    
    public:
        Sphere(Vec3 <double> center, double radius, Material *material) {
            this->center = center;
            this->radius = radius;
            this->material = material;
        }

        bool intersect(double max, Hit_record &rec, Ray *r) {
            Vec3 <double> distance = r->getOrigin().operator-(this->center);
            double a = Vec3<double>::dotProduct(r->getDirection(), r->getDirection());
            double b = 2 * Vec3<double>::dotProduct(distance, r->getDirection());
            double c = Vec3<double>::dotProduct(distance, distance) - (this->radius * this->radius);
            double delta = b * b - 4 * a * c;
            if (delta > 0) {
                double temp = (-b - sqrt(delta) ) / (2.0 * a);
                if( temp < max){
                    rec.t = temp;
                    rec.p = r->sample(temp);
                    Vec3 <double> op = rec.p.operator-(this->center);
                    op.normalise();
                    rec.normal = op;
                    return true;
                }
                temp = (-b + sqrt(delta) ) / (2.0 * a);
                if( temp < max){
                    rec.t = temp;
                    rec.p = r->sample(temp);
                    Vec3 <double> op = rec.p.operator-(this->center);
                    op.normalise();
                    rec.normal = op;
                    return true;
                }
            } 
            return false;
        }
        

        // Vec3 <double> color(Ray *r) {
        //     double t = intersect(r);
        //     if(t > 0.0) {
        //         Vec3 <double> N = r->sample(t).operator-(this->center);
        //         N.normalise();
        //         Vec3 <double> v(0.5 * (N.getX() + 1) * 255, 0.5 * (N.getY() + 1) * 255, 0.5 * (N.getZ() + 1) * 255); 
        //         return v;
        //     }
        //     Vec3 <double> white(255, 255, 255);
        //     Vec3 <double> background(123, 45, 140);
        //     return background;
        // }

        Vec3 <double> getPoint(){
            return this->center;
        }

        Material* getMaterial(){
            return this->material;
        }

        double getRadius() {
            return this->radius;
        }
};