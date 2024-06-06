#include "sim.hpp"
#include <iostream>

Sim::Sim() : container(Container(0.15f, 0.0f, 0.0000001f)) {
	this->win.create(sf::VideoMode(SIZE * SCALE, SIZE * SCALE), "Fluid-Simulation", sf::Style::Titlebar | sf::Style::Close);
}

Sim::~Sim() {}

void Sim::Run() {
	sf::Vector2i previousMouse = sf::Mouse::getPosition(this->win);
	sf::Vector2i currentMouse = sf::Mouse::getPosition(this->win);

	while (this->win.isOpen()) {		

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->container.AddDensity(currentMouse.y / SCALE, currentMouse.x / SCALE, 350);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			this->container.AddSolid(currentMouse.y / SCALE, currentMouse.x / SCALE);
			
		currentMouse = sf::Mouse::getPosition(this->win);

		float amountX = currentMouse.x - previousMouse.x;
		float amountY = currentMouse.y - previousMouse.y;

		this->container.AddVelocity(currentMouse.y / SCALE, currentMouse.x / SCALE, amountY / 10, amountX / 10);

		previousMouse = currentMouse;

		this->container.Step();
		this->container.Render(this->win);
		this->container.FadeDensity();

		this->win.display();
	}
}