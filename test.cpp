#include <iostream>
#include "image.cpp"

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
    for(int i = 0; i < 5; i++) {
        for(int c = 0; c < 5; c++) {
            img.GetPixel(i, c).display();
        }
    }
    return 0;
}