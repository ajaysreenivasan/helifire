#include <cstdlib>

#include "Building.h"

Building::Building(){
	this->buildingHeight = (rand() % 75)*2 + 70;
	this->buildingWidth = (rand() % 75)*2 + 70;

	this->xCoordinate = GameInfo::defaultScreenWidth;
	this->yCoordinate = GameInfo::defaultScreenHeight - buildingHeight + 2;

	this->hitbox.leftBorder = GameInfo::defaultScreenWidth;
	this->hitbox.rightBorder = GameInfo::defaultScreenWidth + buildingWidth;
	this->hitbox.topBorder = GameInfo::defaultScreenHeight - buildingHeight;
	this->hitbox.bottomBorder = GameInfo::defaultScreenHeight;
}

Building::~Building(){
}

void Building::draw(){
	double xScale = GameInfo::xScale;
	double yScale = GameInfo::yScale;

	XFillRectangle(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[4], this->xCoordinate*xScale, this->yCoordinate*yScale, buildingWidth*xScale, buildingHeight*yScale);
}

int Building::getBuildingHeight() const{
	return this->buildingHeight;
}

int Building::getBuildingWidth() const{
	return this->buildingWidth;
}