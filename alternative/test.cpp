#include <iostream>
#include "image.cpp"
#include "geometry.cpp"
#include "camera.cpp"
#include "ray.cpp"
#include "cmath"

using namespace std;

bool shadow(Ray *r, vector<Sphere> &objetosCena) {
    Hit_record record;
    int lightSource = 1000000;
    for (int i = 0; i < objetosCena.size(); i++) {
        if (objetosCena.at(i).intersect(lightSource, record, r)) {
            return false;
        }
    }
    return true;
}

double diffuse(Vec3 <double> lightSource, Hit_record &rec) {
    Vec3 <double> intersectLight = lightSource.operator-(rec.p);
    intersectLight.normalise();
    double dot = Vec3<double>::dotProduct(rec.normal, intersectLight);
    // return kd * surfaceColor * lightSourceColor * dot;
    if (dot <= 0) {
        return 0;
    } else {
        return dot;
    }
    //IMPLEMENTAR: COR FIXA PARA CADA ESFERA, FONTE DE LUZ E SUA COR
}

bool hit (Ray *r, vector <Sphere> &objetosCena, double tmax, Hit_record &rec, double &perc, Sphere light, Vec3 <double> &colores) {
    Hit_record record;
    bool hitAnything = false;
    double closest = tmax;
    bool isShadow = false;
    for (int i = 0; i < objetosCena.size(); i++) {
        if (objetosCena.at(i).intersect(closest, record, r)) {
            hitAnything = true;
            closest = record.t;
            rec.normal = record.normal;
            rec.p = record.p;
            Ray *normal = new Ray(record.p, rec.normal);
            isShadow = shadow(normal, objetosCena);
            colores = objetosCena.at(i).getMaterial()->getColor();
        }
    }
    if (!isShadow) {
        //Vec3 <double> light(10, -15, -5);
        perc = diffuse(light.getPoint(), record);
    }
    return hitAnything;
}


Vec3 <double> color(Ray *r, vector <Sphere> &objetosCena, Sphere light, Vec3 <double> coloures) {
    Hit_record rec;
    double perc;
    if(hit(r, objetosCena, 99999.0, rec, perc, light, coloures)) {
        Vec3 <double> N = rec.normal;
        Vec3 <double> v = coloures.operator*(perc); 
        return v;
    } else {
        Vec3 <double> background(123, 45, 140);
        return background;
    }
}


int main(){
    
    Vec3 <double> camPos(0, 0, 0);
    Vec3 <double> camTarget(0, 0, -1);
    Vec3 <double> camUp(0, 1, 0);
    Vec3 <double> Ecenter(0, 0, -15);
    Vec3 <double> Ecenter2(5, -5, -25);
    Vec3 <double> Lcenter (10, -5, -5);

    Vec3 <double> red(255, 0, 0);
    Vec3 <double> green(0, 255, 0);
    Vec3 <double> blue(0, 0, 255);

    Material *material1 = new Material(1,1,1,1, red);
    Material *material2 = new Material(1,1,1,1, blue);

    int fov = 90;
    double aspect = 1.7;
    double near = 1;
    Camera *cam = new Camera(camPos, camTarget, camUp, fov, near, aspect);
    Image *img = new Image(1920, 1080);
    Ray *r;
    Vec3 <double> p;

    Sphere esfera(Ecenter, 6, material1);
    Sphere esfera2(Ecenter2, 6, material2);
    Sphere light(Lcenter, 0.5, material1);

    Vec3 <double> background(123, 45, 140);
    vector <Sphere> objetosCena;
    objetosCena.push_back(esfera);
    objetosCena.push_back(esfera2);


    for(int i = 0; i < img->getWidth(); i++) {
        for(int j = 0; j < img->getHeight(); j++) {
            r = cam->GetRay(i, j, img->getWidth(), img->getHeight());
            Vec3 <double> c = color(r, objetosCena, light, background);
            img->SetPixel(i, j, c);
        }
    }
    img->SaveAsPPM();
    return 0;
}