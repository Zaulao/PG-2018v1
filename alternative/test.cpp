#include <iostream>
#include "image.cpp"
#include "geometry.cpp"
#include "camera.cpp"
#include "ray.cpp"
#include "cmath"

using namespace std;
typedef Vec3 <double> vec3;

bool notshadow(Ray *r, vector<Sphere> &objetosCena, Sphere light) {
    Hit_record record;
    double lightDistance = Vec3<double>::getDistance(light.getPoint(), r->getOrigin());
    double objectDistance;
    int lightSource = 1000000;
    for (int i = 0; i < objetosCena.size(); i++) {
        objectDistance = Vec3<double>::getDistance(objetosCena.at(i).getPoint(), r->getOrigin());
        if (objectDistance < lightDistance) {
            if (objetosCena.at(i).intersect(lightSource, record, r)) {
                return false;
            }
        }
    }
    return true;
}

vec3 diffuse(Sphere light, Hit_record &rec) {
    vec3 intersectLight = light.getPoint().operator-(rec.p);
    intersectLight.normalise();
    double dot = Vec3<double>::dotProduct(rec.normal, intersectLight);
    // return kd * surfaceColor * lightSourceColor * dot;
    if (dot <= 0) {
        vec3 v(0,0,0);
        return v;
    } else {
        return light.getMaterial()->getColor().operator*(dot);
    }
}

vec3 reflect(vec3 v, vec3 n) {
    double dot = Vec3<double>::dotProduct(v, n);
    dot *= 2;
    n = n.operator*(dot);
    v = v.operator-(n);
    return v;
}

vec3 specular(Sphere light, Hit_record &rec, Ray *r, Sphere obj) {
    vec3 intersectLight = rec.p.operator-(light.getPoint());
    intersectLight.normalise();
    vec3 reflected = reflect(intersectLight, rec.normal);
    double dot = Vec3<double>::dotProduct(r->getDirection(), reflected);
    dot = pow(dot, obj.getMaterial()->getAlpha());
    cout << dot << endl;
    if (dot <= 0) {
        vec3 v(0,0,0);
        return v;
    } else {
        return light.getMaterial()->getColor().operator*(dot);
    }
}

bool hit (Ray *r, vector <Sphere> &objetosCena, double tmax, Hit_record &rec, vec3 &perc, vec3 &especular, Sphere light, vec3 &colores) {
    Hit_record record;
    bool hitAnything = false;
    double closest = tmax;
    bool notShadow = true;
    int index = 0;
    for (int i = 0; i < objetosCena.size(); i++) {
        if (objetosCena.at(i).intersect(closest, record, r)) {
            hitAnything = true;
            closest = record.t;
            rec.normal = record.normal;
            rec.p = record.p;
            vec3 l = light.getPoint().operator-(rec.p);
            l.normalise();
            Ray *normal = new Ray(record.p, l);
            notShadow = notshadow(normal, objetosCena, light);
            colores = objetosCena.at(i).getMaterial()->getColor().operator*(objetosCena.at(i).getMaterial()->getKe());
            index = i;
        }
    }
        perc = diffuse(light, record);
        perc = perc.operator*(objetosCena.at(index).getMaterial()->getKd());
        colores = colores.operator+(perc);
        especular = specular(light, record, r, objetosCena.at(index));
        especular = especular.operator*(objetosCena.at(index).getMaterial()->getKs());
        especular.display();
        colores = colores.operator+(especular);
    if (notShadow) {
        //vec3 light(10, -15, -5);

    }
    return hitAnything;
}


vec3 color(Ray *r, vector <Sphere> &objetosCena, Sphere light, vec3 coloures) {
    Hit_record rec;
    vec3 difusa;
    vec3 especular;
    if(hit(r, objetosCena, 99999.0, rec, difusa, especular, light, coloures)) {
        vec3 v = coloures;
        return v;
    } else {
        vec3 background(0, 0, 0);
        return background;
    }
}


int main(){
    
    vec3 camPos(0, 0, 10);
    vec3 camTarget(0, 0, -1);
    vec3 camUp(0, 1, 0);

    vec3 Ecenter (-5, -3, -50); //red
    vec3 Ecenter2(5, -3, -4); //blue
    vec3 Ecenter3(0, 0, -10); //green

    vec3 Lcenter (5, -5, -2);

    vec3 red(255, 0, 0);
    vec3 green(0, 255, 0);
    vec3 blue(0, 0, 255);
    vec3 brown(94, 58, 66);
    vec3 white(255,255,255);

//double ke, double kd, double ks, double alpha, Vec3 <double> color

    Material *material1 = new Material(0,0,1,0., red);
    Material *material2 = new Material(0,0,0.1,0.1, blue);
    Material *material3 = new Material(0,0,0.82,0.75, green);
    Material *material4 = new Material(0,0,1,1, brown);
    Material *luz = new Material(1,1,1,1, white);

    int fov = 75;
    double aspect = 1.7;
    double near = 1;
    Camera *cam = new Camera(camPos, camTarget, camUp, fov, near, aspect);
    Image *img = new Image(1280, 720);
    Ray *r;
    vec3 p;

    Sphere esfera(Ecenter, 1, material1);
    Sphere esfera2(Ecenter2, 1, material2);
    Sphere esfera3(Ecenter3, 6, material3);
    Sphere esferaGigante (vec3(0,10010,0), 10000, material4);

    Sphere light(Lcenter, 0.5, luz);

    vec3 background(123, 45, 140);
    vector <Sphere> objetosCena;
    objetosCena.push_back(esfera);
    objetosCena.push_back(esfera2);
    objetosCena.push_back(esfera3);
    objetosCena.push_back(esferaGigante);
    //objetosCena.push_back(light);


    for(int i = 0; i < img->getWidth(); i++) {
        for(int j = 0; j < img->getHeight(); j++) {
            r = cam->GetRay(i, j, img->getWidth(), img->getHeight());
            vec3 c = color(r, objetosCena, light, background);
            img->SetPixel(i, j, c);
        }
    }
    img->SaveAsPPM();
    return 0;
}