#include "GameObject.h"

GameObject::GameObject(){
}

GameObject::~GameObject(){
}

int GameObject::getXCoordinate() const{
	return this->xCoordinate;
}

int GameObject::getYCoordinate() const{
	return this->yCoordinate;
}

Hitbox GameObject::getHitbox() const{
	return this->hitbox;
}

void GameObject::draw(){
}

void GameObject::updateXCoordinate(int xChange){
	this->xCoordinate += xChange;
}

void GameObject::updateYCoordinate(int yChange){
	this->yCoordinate += yChange;
}

void GameObject::updateHitbox(int xChange, int yChange){
	this->hitbox.leftBorder += xChange;
	this->hitbox.rightBorder += xChange;
	this->hitbox.topBorder += yChange;
	this->hitbox.bottomBorder += yChange;
}

