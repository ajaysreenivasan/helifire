#include "MovingObject.h"

MovingObject::MovingObject(){
}

MovingObject::~MovingObject(){
}

int MovingObject::getXVelocity() const{
	return this->xVelocity;
}

int MovingObject::getYVelocity() const{
	return this->yVelocity;
}

void MovingObject::updateCoordinates(){
	updateXCoordinate(this->xVelocity);
	updateYCoordinate(this->yVelocity);
	updateHitbox(this->xVelocity, this->yVelocity);
}