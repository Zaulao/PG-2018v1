#include <fstream>
#include <vector>
#include "ray.cpp"

using namespace std;

class Image{
	private:
		int width, height;
		vector <Vec3<double> > buffer;
	
	public:
		Image(int width, int height) {
			this->width = width;
			this->height = height;
			Vec3 <double> zero;
			for( int i = 0; i < this->width * this->height; i++) {
				this->buffer.push_back(zero);
			}
		}

		void SetPixel(int x, int y, Vec3<double> color) {
			this->buffer[ y * width + x] = color;
		}

		Vec3<double> GetPixel(int x, int y) {
			return this->buffer[ y * width + x];
		}

		Vec3<double> GetPixelOneCoord(int i) {
			return this->buffer[ i ];
		}

		void SetPixelOneCoord(int i, const Vec3<double> &color) {
			this->buffer[ i ] = color;
		}

		int getWidth() {
			return this->width;
		}

		int getHeight() {
			return this->height;
		}

		void SaveAsPPM() {
			int r, g, b;
			Vec3 <double> bit;
			FILE *f = fopen("image.ppm", "w");
			fprintf(f, "P3\n%d %d\n%d\n", this->width, this->height, 255);
			for ( int c = 0; c < this->height; c++) {
				for (int i=0; i < this->width; i++) {
					bit = this->GetPixel(i, c);
					r = int(bit.getX());
					g = int(bit.getY());
					b = int(bit.getZ());
					fprintf(f,"%d %d %d ", r, g, b);
				}
				fprintf(f, "\n");
			}
		}

};
