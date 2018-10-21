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
    Vec3 <int> color(255, 0, 0);
    // color.display();
    Image img(2, 2);
    for(int i = 0; i < 4; i++) {
        // for( int c = 15; c < 35; c++) {
            img.SetPixelOneCoord(i, color);

        // }
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