#include <fstream>
#include <vector>
#include "ray.cpp"

using namespace std;

class Image{
	private:
		int width, height;
		vector <Vec3<int> > buffer;
	
	public:
		Image(int width, int height) {
			this->width = width;
			this->height = height;
			Vec3 <int> zero;
			for( int i = 0; i < width * height; i++) {
				this->buffer.push_back(zero);
			}
		}

		void SetPixel(int x, int y, const Vec3<int> &color) {
			this->buffer[ y * width + x] = color;
		}

		Vec3<int> GetPixel(int x, int y) {
			return this->buffer[ y * width + x];
		}

		Vec3<int> GetPixelOneCoord(int i) {
			return this->buffer[ i ];
		}

		void SetPixelOneCoord(int i, const Vec3<int> &color) {
			this->buffer[ i ] = color;
		}

		void SaveAsPPM() {
			int r, g, b;
			Vec3 <int> bit;
			FILE *f = fopen("image.ppm", "w");
			fprintf(f, "P3\n%d %d\n%d\n", this->width, this->height, 1);
			for (int i=0; i < this->width; i++) {
				for ( int c = 0; c < this->height; c++) {
					bit = this->GetPixel(i, c);
					r = bit.getX();
					g = bit.getY();
					b = bit.getZ();
					fprintf(f,"%d %d %d ", r, g, b);
				}
				fprintf(f, "\n");
			}
		}

};
