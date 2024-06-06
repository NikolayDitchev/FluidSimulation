#pragma once
#include <SFML/Graphics.hpp>
#include "physics.hpp"

class Container {
private:
	Physics physics;

	int size;

	float dt;
	float diff;
	float visc;

	float px[SIZE][SIZE];
	float py[SIZE][SIZE];

	float x[SIZE][SIZE];
	float y[SIZE][SIZE];

	float previousDensity[SIZE][SIZE];
	float density[SIZE][SIZE];

	bool solid[SIZE][SIZE];

	void InitArr(float arr[][SIZE]);
	
public:
	Container(float dt, float diff, float visc);
	~Container();

	void AddDensity(int x, int y, float amount);
	void AddVelocity(int x, int y, float px, float py);
	void AddSolid(int x, int y);
	void InitSolid(bool solid[][SIZE]);
	void Step();
	void Render(sf::RenderWindow& win);
	void FadeDensity();
};