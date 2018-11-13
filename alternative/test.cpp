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
    Vec3 <double> Ecenter(0, 0, -10);
    int fov = 120;
    double aspect = 1.25;
    double near = 10;
    Camera *cam = new Camera(camPos, camTarget, camUp, fov, near, aspect);
    Image *img = new Image(cam->getHalf_w() * 2, cam->getHalf_h() * 2);
    for(int i = 0; i < img->getWidth() * img->getHeight(); i++) {
        //img->SetPixelOneCoord(i, color);
    }
    Ray *r;
    Vec3 <int> p;
    Sphere esfera(Ecenter, 5);
    for(int i = 0; i < img->getWidth(); i++) {
        for(int j = 0; j < img->getHeight(); j++) {
            r = cam->GetRay(i, j);
            p = esfera.color(r);
            img->SetPixel(i, j, p);
        }
    }
    img->SaveAsPPM();
    return 0;
}