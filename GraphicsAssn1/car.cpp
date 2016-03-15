#include "car.h"
#include "default.h"


car::car(float x, float y, const std::string direction) : myObject(x, y) {
	this->direction = direction;
}

void car::create() {
	glColor3f(0.0, 1.0, 1.0);
	glRectf(x, y, x + (WORLD_SIZE / MAP_DIVIDE_X), y + (WORLD_SIZE/MAP_DIVIDE_Y));
}
void car::move()
{
	if (direction == "UP")
	{
		incY();
	}
	else decY();
}

void car::incY() {
	if (y < WORLD_SIZE - (WORLD_SIZE / MAP_DIVIDE_Y))
		y += WORLD_SIZE / MAP_DIVIDE_Y / SPEED;
	else {
		y = 0 - WORLD_SIZE / MAP_DIVIDE_Y;
	}
}

void car::decY() {
	if (y > 0)
		y -= WORLD_SIZE / MAP_DIVIDE_Y / SPEED;
	else y = WORLD_SIZE;
}
