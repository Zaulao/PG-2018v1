#include "ray.cpp"
#include "image.cpp"
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
            target.operator*(-1);
            this->axisZ = target;
            target.operator*(-1);
            this->axisX = Vec3<double>::crossProduct(target, up);
            this->axisY = Vec3<double>::crossProduct(this->axisX, target);
            this->near = near;
        }

        Ray* GetRay(double x, double y){
            Vec3 <double> point = this->position;
            point.setZ(point.getZ() - this->near);
            point.setX(point.getX() + (x - 0.5) * this->half_w * 2);
            point.setY(point.getY() + (y - 0.5) * this->half_h * 2);
            Vec3 <double> dir = point.operator-(this->position);
            dir.normalise();
            Ray *ray = new Ray(this->position, dir);
            return ray;
        }

};