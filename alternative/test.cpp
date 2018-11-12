#include <iostream>
#include "image.cpp"
#include "geometry.cpp"
#include "camera.cpp"

using namespace std;

int main(){
    Vec3 <double> vetor;
    double x = 10;
    double y = 5;
    double z = 2;
    vetor.set(x, y, z);
    // vetor.display();
    // vetor.normalise();
    // vetor.display();
    Vec3 <int> color(255, 0, 0);
    // color.display();
    Vec3 <double> camPos(0, 0, 0);
    Vec3 <double> camTarget(0, 0, -1);
    Vec3 <double> camUp(0, 1, 0);
    Vec3 <double> Ecenter(0, 0, -2);
    int fov = 120;
    double aspect = 1.25;
    double near = 1;
    Camera cam(camPos, camTarget, camUp, fov, near, aspect);
    Image img(cam->half_w * 2, cam->half_h * 2);
    for(int i = 0; i < img->width * img->height; i++) {
        img.SetPixelOneCoord(i, color);
    }
    Sphere esfera(Ecenter, 0.5);
    for(int i = 0; i < img->width; i++) {
        for(int j = 0; j < img->height; j++) {
            Ray r = cam.getRay(i, j);
            img.setPixel(i, j, esfera.color(r));
        }
    }
    img.SaveAsPPM();
    return 0;
}