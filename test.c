#include <stdio.h>
#include "./PBM_library/easyppm/easyppm.c"
#include "./../../image.cpp"

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
    Vec3 <int> color(20, 30, 40);
    // color.display();
    Image img(5, 5);
    img.SetPixel(1, 1, color);
    img.SetPixel(1, 2, color);
    img.SetPixel(1, 3, color);
    PPM ppm;
    img.SaveAsPPM(ppm, img.getBuffer());
    return 0;
}