#pragma once

#include <gdiplus.h>
#include "mmsystem.h"

class Reptile 
{
public:
	Reptile();
	~Reptile();

	bool checkForKill(CPoint);

	bool isAlive();

	int getXPosition();
	int getYPosition();
	int getDeathYPos();
	float getXVel();
	float getYVel();
	int getWidth();
	int getHeight();
	int getCenterX();
	int getCenterY();
	int getYMax();
	int getYMin();

	void setXVel(float);
	void setYVel(float);
	void setXPosition(int);
	void setYPosition(int);
	void setDeathYPos(int);
	void setWidth(int);
	void setHeight(int);
	void setMaxMin(int, int);
	void setAlive(bool);

	void Move();
	bool checkForDelete();

private:
	bool alive;
	int xPos;
	int yPos;
	int deathYPos;
	float xVel;
	float yVel;
	int width;
	int height;

	int centerX;
	int centerY;

	int yMax;
	int yMin;

	void setCenter();
};
