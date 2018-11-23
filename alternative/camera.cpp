#include "ray.cpp"
#include <cmath>

const float PI = 3.14159265358979323846;

using namespace std;
class Camera{
    private:
        Vec3 <double> position, axisX, axisY, axisZ;
        double fov, aspect, near, vertical, horizontal;
    
    
    public:
        Camera(Vec3 <double> &position, Vec3 <double> &target, Vec3 <double> &up, double fov, double near, double aspect) {
            double theta = fov * PI / 180.0;
            double half_h = near * tan (theta/2);
            double half_w = half_h * aspect;
            this->vertical = half_h * 2;
            this->horizontal = half_w * 2;
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

        double getHorizontal() {
            return this->horizontal;
        }

        double getVertical() {
            return this->vertical;
        }

        Ray* GetRay(double x, double y, int width, int height){
            Vec3 <double> point = this->position;
            double camPosX = x * this->horizontal / width;
            double camPosY = y * this->vertical / height;
            point.setZ(point.getZ() - this->near);
            point.setX((point.getX() - this->horizontal/2) + camPosX);
            point.setY((point.getY() - this->vertical/2) + camPosY);
            Vec3 <double> dir = point.operator-(this->position);
            dir.normalise();
            Ray *ray = new Ray(point, dir);
            return ray;
        }

};