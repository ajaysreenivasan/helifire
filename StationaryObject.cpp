#include "StationaryObject.h"

StationaryObject::StationaryObject(){
}

StationaryObject::~StationaryObject(){
}

void StationaryObject::updateOnScreenPosition(){
	this->xCoordinate -= GameInfo::scrollSpeed;
	this->hitbox.rightBorder -= GameInfo::scrollSpeed;
	this->hitbox.leftBorder -= GameInfo::scrollSpeed;
}