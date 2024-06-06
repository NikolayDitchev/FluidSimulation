#pragma once
#include "const.hpp"

class Physics {
private:
	void LinSolve(int b, float x[][SIZE], float x0[][SIZE], float a, float c, int iter, bool solid[][SIZE]);
	void SetBnd(int b, float x[][SIZE], bool solid[][SIZE]);
	void ReverseVelocity(int posX, int posY,float x[][SIZE], bool Solid[][SIZE]);
	
public:
	Physics();
	~Physics();

	void Diffuse(int b, float x[][SIZE], float x0[][SIZE], float diff, float dt, int iter, bool solid[][SIZE]);
	void Project(float vx[][SIZE], float vy[][SIZE], float p[][SIZE], float div[][SIZE], int iter, bool solid[][SIZE]);
	void Advect(int b, float d[][SIZE], float d0[][SIZE], float vx[][SIZE], float vy[][SIZE], float dt, bool solid[][SIZE]);
};