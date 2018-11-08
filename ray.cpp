#pragma once
#include "Vec3.hpp"
#include <float.h>

class Ray{

    private:
        Vec3 <double> origin, direction;

    public:
        mutable double tmin = DBL_EPSILON, tmax = DBL_MAX;

        Ray(Vec3 <double> &origin, Vec3 <double> &direction) {
            this->origin = origin;
            this->direction = direction;
        }

        Vec3 <double> sample (const double& t) {
            Vec3 <double> desloc = this->direction.operator*(t);
            return this->origin.operator+(desloc);
        }

        Vec3 <double> getOrigin() {
            return this->origin;
        }

        Vec3 <double> getDirection() {
            return this->direction;
        }
};