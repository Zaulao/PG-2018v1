#include "Ray.h"
#include <cmath>
#include "Vec3.h"
class Camera{
    private:
        Vec3 position, axisX, axisY, axisZ;
        double fov, near;
    
    
    public:
        Camera(Vec3 position, Vec3 target, Vec3 up, double fov, double near) {
            this->position = position;

            
        }

        Ray GetRay(double x, double y, int width, int height) const;

};