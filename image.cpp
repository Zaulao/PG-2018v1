#include <vector>
#include "Vec3.hpp"
#include "./PPM_library/easyppm/easyppm.h"

using namespace std;

class Image{
	private:
		int width, height;
		vector <Vec3<int> > buffer;
	
	public:
		Image(int width, int height) {
			this->width = width;
			this->height = height;
			buffer.reserve(width * height);
		}

		vector <Vec3<int> > getBuffer(){
			return this->buffer;
		}

		void SetPixel(int x, int y, const Vec3<int> &color) {
			this->buffer[ y * width + x] = color;
		}

		Vec3<int> GetPixel(int x, int y) {
			return this->buffer[ y * width + x];
		}

		void SaveAsPPM(PPM ppm, vector <Vec3<int> > buffer){
			for(int i = 0; i < this->width * this->height; i++){
				int x = i % this->width;
				int y = i / this->width;
				Vec3 <int> pos = GetPixel(x, y);
				easyppm_set(&ppm, x , y, easyppm_rgb(pos.getX(), pos.getY(), pos.getZ()));
			}
				easyppm_write(&ppm, "img.ppm");
				easyppm_destroy(&ppm);
		}


		


};
