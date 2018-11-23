#include <iostream>
#include "image.cpp"
#include "geometry.cpp"
#include "camera.cpp"
#include "ray.cpp"

using namespace std;

bool hit (Ray *r, vector <Sphere> &objetosCena, double tmax, Hit_record &rec) {
    Hit_record record;
    bool hitAnything = false;
    double closest = tmax;
    for (int i = 0; i < objetosCena.size(); i++) {
        if (objetosCena.at(i).intersect(closest, record, r)) {
            hitAnything = true;
            closest = record.t;
            rec.normal = record.normal;
            rec.p = record.p;
        }
    }
    return hitAnything;
}
Vec3 <double> color(Ray *r, vector <Sphere> &objetosCena) {
    Hit_record rec;
    if(hit(r, objetosCena, 99999.0, rec)) {
        Vec3 <double> N = rec.normal;
        Vec3 <double> v(0.5 * (N.getX() + 1) * 255, 0.5 * (N.getY() + 1) * 255, 0.5 * (N.getZ() + 1) * 255); 
        return v;
    } else {
        Vec3 <double> background(123, 45, 140);
        return background;
    }
}


int main(){
    Vec3 <double> vetor;
    double x = 10;
    double y = 5;
    double z = 2;
    vetor.set(x, y, z);
    // vetor.display();
    // vetor.normalise();
    // vetor.display();
    // color.display();
    Vec3 <double> camPos(0, 0, 0);
    Vec3 <double> camTarget(0, 0, -1);
    Vec3 <double> camUp(0, 1, 0);
    Vec3 <double> Ecenter(0, 0, -15);
    Vec3 <double> Ecenter2(5, 0, -8);
    int fov = 90;
    double aspect = 1.25;
    double near = 1;
    Camera *cam = new Camera(camPos, camTarget, camUp, fov, near, aspect);
    Image *img = new Image(400, 300);
    Ray *r;
    Vec3 <double> p;
    Sphere esfera(Ecenter, 6);
    Sphere esfera2(Ecenter2, 6);
    Vec3 <double> background(123, 45, 140);
    vector <Sphere> objetosCena;
    objetosCena.push_back(esfera);
    objetosCena.push_back(esfera2);


    for(int i = 0; i < 400; i++) {
        for(int j = 0; j < 300; j++) {
            r = cam->GetRay(i, j, img->getWidth(), img->getHeight());
            Vec3 <double> c = color(r, objetosCena);
            img->SetPixel(i, j, c);
        }
    }
    img->SaveAsPPM();
    return 0;
}