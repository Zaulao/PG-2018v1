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
    Image img(500, 500);
    for(int i = 0; i < 250000; i++) {
        // for( int c = 15; c < 35; c++) {
            img.SetPixelOneCoord(i, color);

        // }
    }
    Vec3 <double> camPos(0, 0, 0);
    Vec3 <double> camTarget(0, 0, -1);
    Vec3 <double> camUp(0, 1, 0);
    Vec3 <double> Ecenter(0, 0, -1);
    Camera cam(camPos, camTarget, camUp, 20.5, 1)
    Sphere esfera(Ecenter, 0.5);
    for(int i = 0; i < 500; i++) {
        for(int j = 0; j < 500; j++) {
            Ray r = cam.getRay(j, i, 500, 500);
            img.setPixelOneCoord(i, color(r));
        }
    }
    // for(int i = 0; i < 50; i++) {
    //     for(int c = 0; c < 50; c++) {
    //         cout << img.GetPixel(i, c).getX() << " ";
    //     }
    //     cout << endl;
    // }
    img.SaveAsPPM();
    return 0;
}