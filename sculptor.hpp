#ifndef SCULPTOR_H
#define SCULPTOR_H
#include <string>
#include <vector>

struct Voxel {
  float r, g, b; // Colors
  float a; // Transparency
  bool isOn; // Included or not
};

class sculptor
{
	private:
		Voxel ***v; 
  		int x, y, z; 
  		float r, g, b, a; 
  		int h, i, j; 
  		
	public:
		sculptor(int _x=1, int _y=1, int _z=1);
 		~sculptor();
  		void setColor(float r, float g, float b, float a);
  		void putVoxel(int x0, int y0, int z0);
  		void cutVoxel(int x0, int y0, int z0);
  		void putCube(int x0, int x1, int y0, int y1, int z0, int z1);
  		void cutCube(int x0, int x1, int y0, int y1, int z0, int z1);
  		void putSphere(int x0, int y0, int z0, int r0);
  		void cutSphere(int x0, int y0, int z0, int r0);
  		void writeOFF(char* filename);
};

#endif
