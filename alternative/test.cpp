#include <iostream>
#include "image.cpp"
#include "geometry.cpp"
#include "camera.cpp"
#include "ray.cpp"
#include "cmath"
#include "reader.cpp"
#include <map>

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
    vec3 intersectLight =  light.getPoint().operator-(rec.p);
    intersectLight.normalise();
    vec3 reflected = reflect(intersectLight, rec.normal);
    reflected.normalise();
    double dot = Vec3<double>::dotProduct(r->getDirection(), reflected);
    dot = max(0.0, dot);
    dot = pow(dot, obj.getMaterial()->getAlpha());
    return light.getMaterial()->getColor().operator*(dot);    
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
    if (notShadow) {
        perc = diffuse(light, record);
        perc = perc.operator*(objetosCena.at(index).getMaterial()->getKd());
        colores = colores.operator+(perc);
        especular = specular(light, record, r, objetosCena.at(index));
        especular = especular.operator*(objetosCena.at(index).getMaterial()->getKs());
        colores = colores.operator+(especular);
       
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
        vec3 background(123, 45, 140);
        return coloures;
    }
}


int main(){

    map <string, double> res;
    map <string, double> camera;
    map <string, double> material;
    map <string, double> objetos;
    
    Reader *aux = new Reader(res, camera, material, objetos);
    Reader *data = new Reader(res, camera, material, objetos);
    data = aux->read_file();
    vec3 camPos(data->camera["px"], data->camera["py"], data->camera["pz"]);
    vec3 camTarget(data->camera["tx"], data->camera["ty"], data->camera["tz"]);
    vec3 camUp(data->camera["ux"], data->camera["uy"], data->camera["uz"]);
    vec3 Lcenter (0, -150, -10);
    vec3 white(255,255,255);

//material(r g b kd ks ke alpha)
    Material *material1 = new Material(vec3(data->material["red_r"],data->material["red_g"],data->material["red_b"]), data->material["red_kd"],data->material["red_ks"],data->material["red_ke"] ,data->material["red_alpha"]);
    Material *material2 = new Material(vec3(data->material["blue_r"],data->material["blue_g"],data->material["blue_b"]), data->material["blue_kd"],data->material["blue_ks"],data->material["blue_ke"] ,data->material["blue_alpha"]);
    Material *material3 = new Material(vec3(data->material["green_r"],data->material["green_g"],data->material["green_b"]), data->material["green_kd"],data->material["green_ks"],data->material["green_ke"] ,data->material["green_alpha"]);
    Material *material4 = new Material(vec3(data->material["rose_r"],data->material["rose_g"],data->material["rose_b"]), data->material["rose_kd"],data->material["rose_ks"],data->material["rose_ke"] ,data->material["rose_alpha"]);
    Material *luz = new Material(white,1,1,1,1);


    double aspect = data->res["w"]/data->res["h"];
    Camera *cam = new Camera(camPos, camTarget, camUp, data->camera["fov"], data->camera["f"], 1.7); //falta ajeitar o aspect pra ser calculado pelo que vem do objeto 
    Image *img = new Image(data->res["w"],data->res["h"]);
    Ray *r;
    vec3 p;

    Sphere esfera(vec3(data->objetos["sphere0_cx"],data->objetos["sphere0_cy"],data->objetos["sphere0_cz"]), data->objetos["sphere0_r"], material1);
    Sphere esfera2(vec3(data->objetos["sphere1_cx"],data->objetos["sphere1_cy"],data->objetos["sphere1_cz"]), data->objetos["sphere1_r"], material2);
    Sphere esfera3(vec3(data->objetos["sphere2_cx"],data->objetos["sphere2_cy"],data->objetos["sphere2_cz"]), data->objetos["sphere2_r"], material3);
    Sphere esferaGigante (vec3(data->objetos["sphere3_cx"],data->objetos["sphere3_cy"],data->objetos["sphere3_cz"]), data->objetos["sphere3_r"], material4);

    Sphere light(Lcenter, 0.5, luz);

    //vec3 background(123, 45, 140);
    vec3 background (149,229,249);
    vector <Sphere> objetosCena;
    objetosCena.push_back(esfera);
    objetosCena.push_back(esfera2);
    objetosCena.push_back(esfera3);
    objetosCena.push_back(esferaGigante);
    
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