#include <vector>
#include "Vec3.h"

using namespace std;

class Image{
	private:
		int width, height;
		vector <Vec3> buffer;
	
	public:
		Image(int width, int height);

		void SetPixel(int x, int y, const Vec3& color);

		void SaveAsPBM(const string& filePath) const;

};
