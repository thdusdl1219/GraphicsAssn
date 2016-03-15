#include "tree.h"
#include "default.h"
#define TREE_SIZE (0.2)
tree::tree(float x, float y) : myObject(x, y) {

}

void tree::create() {
	glColor3f(1.0, 1.0, 0.0);
	//printf("%f", ((1.0 / MAP_DIVIDE_X) - TREE_SIZE));
	//glRectf(x + ((1.0 / MAP_DIVIDE_X) - TREE_SIZE), y + 0.07, x + TREE_SIZE * RATIO, y + TREE_SIZE);
	glRectf(x, y, x + TREE_SIZE * RATIO, y + TREE_SIZE);
}