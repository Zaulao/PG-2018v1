#include "ray.cpp"
#include <cmath>

const float PI = 3.14159265358979323846;

using namespace std;
class Camera{
    private:
        Vec3 <double> position, axisX, axisY, axisZ;
        double fov, aspect, near, half_h, half_w;
    
    
    public:
        Camera(Vec3 <double> &position, Vec3 <double> &target, Vec3 <double> &up, double fov, double near, double aspect) {
            double theta = fov * PI / 180.0;
            double half_h = near * tan (theta/2);
            double half_w = half_h * aspect;
            this->half_h = half_h;
            this->half_w = half_w;
            this->position = position;
            this->fov = fov;
            this->aspect = aspect;
            target.normalise();
            up.normalise();
            this->axisZ = target;
            this->axisX = Vec3<double>::crossProduct(up, target);
            this->axisY = Vec3<double>::crossProduct(target, this->axisX);
            this->near = near;
        }

        double getHalf_h() {
            return this->half_h;
        }

        double getHalf_w() {
            return this->half_w;
        }

        Ray* GetRay(double x, double y){
            Vec3 <double> point = this->position;
            point.setZ(point.getZ() - this->near);
            point.setX((point.getX() - this->half_w) + x);
            point.setY((point.getY() - this->half_h) + y);
            Vec3 <double> dir = point.operator-(this->position);
            dir.normalise();
            Ray *ray = new Ray(this->position, dir);
            return ray;
        }

};