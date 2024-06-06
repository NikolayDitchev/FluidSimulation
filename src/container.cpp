#include "container.hpp"
#include <iostream>

Container::Container(float dt, float diff, float visc) : physics(Physics()) {
	
	this->dt = dt;
	this->diff = diff;
	this->visc = visc;

	this->InitArr(this->px);
	this->InitArr(this->py);
	this->InitArr(this->x);
	this->InitArr(this->y);
	this->InitArr(this->previousDensity);
	this->InitArr(this->density);
	this->InitSolid(this->solid);
}

Container::~Container() {}

void Container::InitArr(float arr[][SIZE]) {
	for (int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++)
		arr[i][j] = 0;
	}
}

void Container::InitSolid(bool solid[][SIZE]) {
	for (size_t i = 0; i < SIZE; i++)
	{
		for (size_t j = 0; j < SIZE; j++)
		{
			solid[i][j] = false;
		}
	}
}

void Container::AddSolid(int x, int y) {
	this->solid[x][y] = true;
}

void Container::AddDensity(int x, int y, float amount) {
	this->density[x][y] += amount;
}

void Container::AddVelocity(int x, int y, float px, float py) {

	this->x[x][y] += px;
	this->y[x][y] += py;
}

void Container::Step() {
	this->physics.Diffuse(1, this->px, this->x, this->visc, this->dt, 6, this->solid);
	this->physics.Diffuse(2, this->py, this->y, this->visc, this->dt, 6, this->solid);

	this->physics.Project(this->px, this->py, this->x, this->y, 6, this->solid);

	this->physics.Advect(1, this->x, this->px, this->px, this->py, this->dt, this->solid);
	this->physics.Advect(2, this->y, this->py, this->px, this->py, this->dt, this->solid);

	this->physics.Project(this->x, this->y, this->px, this->py, 6, this->solid);

	this->physics.Diffuse(0, this->previousDensity, this->density, this->diff, this->dt, 6, this->solid);
	this->physics.Advect(0, this->density, this->previousDensity, this->x, this->y, this->dt, this->solid);
}

void Container::Render(sf::RenderWindow& win) {
	win.clear();
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			sf::RectangleShape rect;
			rect.setSize(sf::Vector2f(SCALE, SCALE));
			rect.setPosition(j * SCALE, i * SCALE);

			if (!solid[i][j]) {

				rect.setFillColor(sf::Color(255, 255, 255, (this->density[i][j] > 255) ? 255 : this->density[i][j]));
			}
			else {
				rect.setFillColor(sf::Color(0, 100, 0, 255));
			}
				
			win.draw(rect);
		}
	}
}

void Container::FadeDensity() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			float d = this->density[i][j];
			density[i][j] = (d - 0.1f < 0) ? 0 : d - 0.05f;
		}
	}
}