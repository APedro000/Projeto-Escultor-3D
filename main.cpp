#include <iostream>
#include "sculptor.hpp"
#include <fstream>

using namespace std;

int main(void) {
	sculptor teste(200,200,200);
	//Corpo do boneco de neve
	teste.setColor(1,1,1,1);
	teste.putCube(30,61,1,31,1,31);
	teste.putCube(35,56,31,51,6,26);
	teste.putCube(40,51,51,64,9,23);
	//braços do boneco de neve
	teste.setColor(0,0.2,0,1);
	teste.putCube(56,66,46,49,15,18);
	teste.putCube(25,35,46,49,15,18);
	//Botões do peito
	teste.setColor(0,0,0,1);
	teste.putCube(44,47,46,49,26,27);
	teste.putCube(44,47,40,43,26,27);
	teste.putCube(44,47,34,37,26,27);
	//Olhos
	teste.putCube(42,44,60,62,23,24);
	teste.putCube(47,49,60,62,23,24);
	//Boca
	teste.putCube(43,48,54,55,23,24);
	teste.putVoxel(42,55,23);
	teste.putVoxel(48,55,23);
	//Nariz
	teste.setColor(1,0.5,0,1);
	teste.putCube(44,47,57,60,23,29);
	teste.putVoxel(45,58,29);

	
	teste.writeOFF((char*) "C:/Users/pedin/projeto/teste.off");
	
return 0;}
