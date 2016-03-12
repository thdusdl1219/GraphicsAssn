#pragma once

class myObject {
public :
	myObject(float x, float y);
	void refresh();
	float getX();
	float getY();
protected :
	float x;
	float y;
};