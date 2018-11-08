#include "ray.cpp"
#include <cmath>

using namespace std;
class Camera{
    private:
        Vec3 <double> position, axisX, axisY, axisZ;
        double fov, near;
    
    
    public:
        Camera(Vec3 <double> &position, Vec3 <double> &target, Vec3 <double> &up, double fov, double near) {
            this->position = position;
            target.normalise();
            up.normalise();
            target.operator*(-1);
            this->axisZ = target;
            target.operator*(-1);
            this->axisX = Vec3<double>::crossProduct(target, up);
            this->axisY = Vec3<double>::crossProduct(this->axisX, target);
            this->fov = fov;
            this->near = near;
        }

        Ray* GetRay(double x, double y, int width, int height) {
            Vec3 <double> point = this->position;
            point.setZ(point.getZ() - this->near);
            point.setX(point.getX() + x);
            point.setY(point.getY() + y);
            Vec3 <double> dir = point.operator-(this->position);
            dir.normalise();
            Ray *ray = new Ray(this->position, dir);
            return ray;
        }

};