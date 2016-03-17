#include "tree.h"
#include "default.h"

const float padding = WORLD_SIZE / 300.0;

tree::tree(float x, float y) : myObject(x, y) {

}

void tree::create() {
	glColor3f(1.0, 1.0, 0.0);
	//printf("%f", ((1.0 / MAP_DIVIDE_X) - TREE_SIZE));
	glRectf(x + padding, y, x + incX - padding, y + incY);
	//glRectf(x, y, x + TREE_SIZE * RATIO, y + TREE_SIZE);
}