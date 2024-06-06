#pragma once
#include <vector>
#include "container.hpp"

class Sim {
private:
	sf::RenderWindow win;
	Container container;
public:
	Sim();
	~Sim();
	void Run();
};