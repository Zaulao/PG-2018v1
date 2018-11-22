#include <iostream>
#include "image.cpp"
#include "geometry.cpp"
#include "camera.cpp"

using namespace std;

// Vec3 <double> color(Ray *r, vector <Sphere> objetosCena) {
//             double t = intersect(999999.0, objetosCena,r);
//             if(t > 0.0) {
//                 Vec3 <double> N = r->sample(t).operator-(this->center);
//                 N.normalise();
//                 Vec3 <double> v(0.5 * (N.getX() + 1) * 255, 0.5 * (N.getY() + 1) * 255, 0.5 * (N.getZ() + 1) * 255); 
//                 return v;
//             }
//             Vec3 <double> white(255, 255, 255);
//             Vec3 <double> background(123, 45, 140);
//             return background;
//         }

int main(){
    Vec3 <double> vetor;
    double x = 10;
    double y = 5;
    double z = 2;
    vetor.set(x, y, z);
    // vetor.display();
    // vetor.normalise();
    // vetor.display();
    Vec3 <double> color(255, 0, 0);
    // color.display();
    Vec3 <double> camPos(0, 0, 0);
    Vec3 <double> camTarget(0, 0, -1);
    Vec3 <double> camUp(0, 1, 0);
    Vec3 <double> Ecenter(0, 0, -5);
    Vec3 <double> Ecenter2(-3, -1, -5);
    int fov = 90;
    double aspect = 1.25;
    double near = 1;
    Camera *cam = new Camera(camPos, camTarget, camUp, fov, near, aspect);
    Image *img = new Image(400, 300);
    Ray *r;
    Vec3 <double> p;
    Sphere esfera(Ecenter, 2);
    Sphere esfera2(Ecenter2, 3);
    Vec3 <double> background(123, 45, 140);

    for(int i = 0; i < 400; i++) {
        for(int j = 0; j < 300; j++) {
                img->SetPixel(i, j, background);
        }
    }
    vector <Sphere> objetosCena;
    objetosCena.push_back(esfera);
    objetosCena.push_back(esfera2);

    vector <double> intercesoes;

    for(int i=0;i< objetosCena.size();i++){

    }



    for(int i = 0; i < 400; i++) {
        for(int j = 0; j < 300; j++) {
            r = cam->GetRay(i, j, img->getWidth(), img->getHeight());
            // p = esfera.color(r);
            // img->SetPixel(i, j, p);
            for(int a=0;a<objetosCena.size();a++){
                Vec3 <double> color = objetosCena.at(a).color(r);
                if (!color.operator==(background)){
                    img->SetPixel(i, j, color);
                }
            }
        }
    }
    img->SaveAsPPM();
    return 0;
}