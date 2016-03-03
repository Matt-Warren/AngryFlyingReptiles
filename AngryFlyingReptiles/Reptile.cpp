#include "stdafx.h"
#include "Reptile.h"



Reptile::Reptile(){
	alive = true;
	xPos = 0;
	yPos = 0;
	xVel = 0;
	yVel = 0;
	deathYPos = 0;
}

Reptile::~Reptile(){


}


void Reptile::Move() {
	xPos += (int)xVel;
	yPos += (int)yVel;
	setCenter();
}

bool Reptile::checkForKill(CPoint point) {
	if(point.x >= (centerX-width/2) && point.x <= (centerX+width/2) && point.y >= (centerY-height/2) && point.y <=(centerY+height/2)){
		alive = false;
	}
	
	return !(isAlive());
}

bool Reptile::isAlive() {
	return alive;
}

float Reptile::getXVel() {
	return xVel;
}

float Reptile::getYVel() {
	return yVel;
}

int Reptile::getXPosition() {
	return xPos;
}

int Reptile::getYPosition() {
	return yPos;
}

int Reptile::getDeathYPos() {
	return deathYPos;
}

int Reptile::getWidth() {
	return width;
}

int Reptile::getHeight() {
	return height;
}

int Reptile::getCenterX() {
	return centerX;
}

int Reptile::getCenterY() {
	return centerY;
}


void Reptile::setXPosition(int x) {
	xPos = x;
}

void Reptile::setYPosition(int y) {
	yPos = y;
}

void Reptile::setDeathYPos(int deathHeight) {
	deathYPos = deathHeight;
}

void Reptile::setXVel(float x) {
	xVel = x;
}

void Reptile::setYVel(float y) {
	yVel = y;
}

void Reptile::setWidth(int w) {
	width = w;
	setCenter();
}

void Reptile::setHeight(int h) {
	height = h;
	setCenter();
}

void Reptile::setCenter() {
	centerX = xPos + width/2;
	centerY = yPos + height/2;
}

void Reptile::deathAnimation() {
	PlaySound(L"res/falling.wav", 0, SND_NOSTOP | SND_ASYNC | SND_LOOP);
}