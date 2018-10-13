#include <vector>
#include "Vec3.hpp"

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

		void SetPixel(int x, int y, const Vec3<int> &color) {
			buffer[ y * width + x] = color;
		}

		Vec3<int> GetPixel(int x, int y) {
			return buffer[ y * width + x];
		}

		void SaveAsPBM(const string& filePath) const;

};
