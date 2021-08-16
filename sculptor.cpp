#include "sculptor.hpp"
#include <stdlib.h>   
#include <string>
#include <iostream>   
#include <fstream>    
#include <iomanip>    
#include <cmath>     
#include <vector>     

using namespace std;

//CONSTRUTOR DA CLASSE:Cria a matriz tridimensional v, e realiza a alocação dinâmica de memório para o struct que irá armazenar os dados dos voxels
sculptor::sculptor(int _x, int _y, int _z){ 
	x = _x;
  	y = _y;
  	z = _z;
  	r = g = b = a = 0.5;
    v = new Voxel**[x];
  	for (int h=0; h<x; h++){
		v[h] = new Voxel*[y];
  	}

  	for(int h=0; h<x; h++){
		for(int i = 0; i<y; i++){
			v[h][i] = new Voxel[z];
		}
  	} 
  
  	for(int h=0; h<x; h++){
        for (int i=0; i<y; i++){
            for (int j=0; j<z; j++){
                v[h][i][j].isOn = false;
        		v[h][i][j].r = r;
        		v[h][i][j].g = g;
        		v[h][i][j].b = b;
        		v[h][i][j].a = a;
            }
        }
    }
}

//DESTRUTOR DA CLASSE: Libera a memória alocada
sculptor::~sculptor(){
  	for(int h=0; h<x; h++){
  		for(int i=0; i<y; i++){
  	   		delete [] v[h][i];	
		}
  	}
  	for(int h=0; h<x; h++){
  		delete [] v[h];
  	}
  	delete [] v;  
}

//Define cor
void sculptor::setColor(float _r, float _g, float _b, float _a){
  	r = _r;
  	g = _g;
  	b = _b;
  	a = _a;
}

//Elimina o voxel
void sculptor::cutVoxel(int x0, int y0, int z0){
    v[x0][y0][z0].isOn = false;
}

//Cria um Voxel
void sculptor::putVoxel(int x0, int y0, int z0){
	v[x0][y0][z0].isOn = true;
    v[x0][y0][z0].r = r;
    v[x0][y0][z0].g = g;
    v[x0][y0][z0].b = b;
    v[x0][y0][z0].a = a;
}

//Cria cubo
void sculptor::putCube(int x0, int x1, int y0, int y1, int z0, int z1){
	for (int h=x0; h<x1; h++){
    	for (int i=y0; i<y1; i++){
        	for (int j=z0; j<z1; j++){
        		v[h][i][j].isOn = true;
    			v[h][i][j].r = r;
    			v[h][i][j].g = g;
    			v[h][i][j].b = b;
    			v[h][i][j].a = a;
    		}
    	}
    }
}

//Elimina cubo
void sculptor::cutCube(int x0, int x1, int y0, int y1, int z0, int z1){
	for (int h=x0; h<x1; h++){
    	for (int i=y0; i<y1; i++){
        	for (int j=z0; j<z1; j++){
        		v[h][i][j].isOn = false;
        	}
        }
    }
}

//Cria esfera
void sculptor::putSphere(int x0, int y0, int z0, int r0){
	double dx, dy, dz;
	for (int h=0; h<x; h++){
        for (int i=0; i<y; i++){
            for (int j=0; j<z; j++){
            dx = ((double)(h-x0)*(double)(h-x0));
            dy = ((double)(i-y0)*(double)(i-y0));
            dz = ((double)(j-z0)*(double)(j-z0));
				if ((dx+dy+dz)<(r0*r0)){
            		v[h][i][j].isOn = true;
            		v[h][i][j].r = r;
            		v[h][i][j].g = g;
           		 	v[h][i][j].b = b;
            		v[h][i][j].a = a;
            	}
            }
        }
	}
}

//Elimina esfera
void sculptor::cutSphere(int x0, int y0, int z0, int r0){
	double dx, dy, dz;
	for (int h=0; h<x; h++){
        for (int i=0; i<y; i++){
            for (int j=0; j<z; j++){
            dx = ((double)(h-x0)*(double)(h-x0));
            dy = ((double)(i-y0)*(double)(i-y0));
            dz = ((double)(j-z0)*(double)(j-z0));
				if ((dx+dy+dz)<(r0*r0)){
            		v[h][i][j].isOn = false;
            	}
            }
        }
    }
}

void sculptor::writeOFF(char *filename){
	int total, index;
    ofstream f;
    total = 0;
    f.open(filename);
    f << "OFF\n";
    for (h=0; h<x; h++){
        for (i=0; i<y; i++){
            for (j=0; j<z; j++){
        		if(v[h][i][j].isOn == true){
            		total++;
        		}
            }
        }
    }
   	f << total*8 << " " << total * 6 <<" "<< 0 << "\n"; 
   	for (h=0; h<x; h++){
        for (i=0; i<y; i++){
            for (j=0; j<z; j++){
        		if(v[h][i][j].isOn == true){
        			f << h - 0.5 << " " << i + 0.5 << " " << j - 0.5 << "\n" << flush;
        			f << h - 0.5 << " " << i - 0.5 << " " << j - 0.5 << "\n" << flush;
                    f << h + 0.5 << " " << i - 0.5 << " " << j - 0.5 << "\n" << flush;
                    f << h + 0.5 << " " << i + 0.5 << " " << j - 0.5 << "\n" << flush;
                    f << h - 0.5 << " " << i + 0.5 << " " << j + 0.5 << "\n" << flush;
                    f << h - 0.5 << " " << i - 0.5 << " " << j + 0.5 << "\n" << flush;
                    f << h + 0.5 << " " << i - 0.5 << " " << j + 0.5 << "\n" << flush;
                    f << h + 0.5 << " " << i + 0.5 << " " << j + 0.5 << "\n" << flush;
                }
            }
        }
    }
    total=0;
    for (h=0; h<x; h++){
        for (i=0; i<y; i++){
            for (j=0; j<z; j++){
        		if(v[h][i][j].isOn == true){
        			index = total*8;
        			f << fixed;
        			f<< 4 << " " << index + 0 << " " << index + 3 << " " << index + 2 << " " << index + 1 << " ";
                    f << setprecision(2) << v[h][i][j].r << " " << setprecision(2) << v[h][i][j].g << " " << setprecision(2) << v[h][i][j].b << " " <<setprecision(2) << v[h][i][j].a << setprecision(2) << "\n";

                    f<< 4 << " " << index + 4 << " " << index + 5 << " " << index + 6 << " " << index + 7 << " ";
                    f << setprecision(2) << v[h][i][j].r << " " << setprecision(2) << v[h][i][j].g << " " << setprecision(2) << v[h][i][j].b << " " << setprecision(2) << v[h][i][j].a << setprecision(2) << "\n";

                    f<< 4 << " " << index + 0 << " " << index + 1 << " " << index + 5 << " " << index + 4 << " ";
                    f << setprecision(2) << v[h][i][j].r << " " << setprecision(2) << v[h][i][j].g << " " << setprecision(2) << v[h][i][j].b << " " << setprecision(2) << v[h][i][j].a << setprecision(2) << "\n";

                    f<< 4 << " " << index + 0 << " " << index + 4 << " " << index + 7 << " " << index + 3 << " ";
                    f << setprecision(2) << v[h][i][j].r << " " << setprecision(2) << v[h][i][j].g << " " << setprecision(2) << v[h][i][j].b << " " << setprecision(2) << v[h][i][j].a << setprecision(2) << "\n";

                    f<< 4 << " " << index + 7 << " " << index + 6 << " " << index + 2 << " " << index + 3 << " ";
                    f << setprecision(2) << v[h][i][j].r << " " <<setprecision(2) << v[h][i][j].g << " " << setprecision(2) << v[h][i][j].b << " " <<setprecision(2) << v[h][i][j].a << setprecision(2) << "\n";

                    f<< 4 << " " << index + 1 << " " << index + 2 << " " << index + 6 << " " << index + 5 << " ";
                    f << setprecision(2) << v[h][i][j].r << " " << setprecision(2) << v[h][i][j].g << " " << setprecision(2) << v[h][i][j].b << " " << setprecision(2) << v[h][i][j].a << setprecision(2) << "\n";

                    total++;
                }
            }
        }
    }
    f.close();
}


