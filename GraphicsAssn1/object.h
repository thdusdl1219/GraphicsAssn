#pragma once
class myObject {
public :
	myObject(float x, float y);
	void refresh();
	float getX();
	float getY();
	virtual void create() = 0;
protected :
	float x;
	float y;
};