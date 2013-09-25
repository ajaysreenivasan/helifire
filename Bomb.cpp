#include "Bomb.h"

Bomb::Bomb(const Helicopter &helicopter){
	this->xCoordinate = helicopter.getXCoordinate();
	this->yCoordinate = helicopter.getYCoordinate();

	if(helicopter.getXVelocity() != 0)
		this->xVelocity = helicopter.getXVelocity();
	else
		this->xVelocity = 0;

	this->yVelocity = +4;

	this->hitbox.leftBorder = this->xCoordinate + 52;
	this->hitbox.rightBorder = this->hitbox.leftBorder + BOMB_WIDTH;
	this->hitbox.topBorder = this->yCoordinate + 25;
	this->hitbox.bottomBorder = this->hitbox.topBorder + BOMB_HEIGHT;
}

Bomb::~Bomb(){
}

void Bomb::draw(){
	double xScale = GameInfo::xScale;
	double yScale = GameInfo::yScale;

	XPoint points12[] = {
		{ (52 + xCoordinate)*xScale , (33 + yCoordinate)*yScale },
		{ (52 + xCoordinate)*xScale , (28 + yCoordinate)*yScale },
		{ (53 + xCoordinate)*xScale , (27 + yCoordinate)*yScale },
		{ (52 + xCoordinate)*xScale , (26 + yCoordinate)*yScale },
		{ (52 + xCoordinate)*xScale , (25 + yCoordinate)*yScale },
		{ (54 + xCoordinate)*xScale , (26 + yCoordinate)*yScale },
		{ (56 + xCoordinate)*xScale , (25 + yCoordinate)*yScale },
		{ (56 + xCoordinate)*xScale , (26 + yCoordinate)*yScale },
		{ (55 + xCoordinate)*xScale , (27 + yCoordinate)*yScale },
		{ (56 + xCoordinate)*xScale , (28 + yCoordinate)*yScale },
		{ (56 + xCoordinate)*xScale , (33 + yCoordinate)*yScale },
		{ (52 + xCoordinate)*xScale , (33 + yCoordinate)*yScale }
	};
	int npoints12 = 12;
	XFillPolygon(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[2], points12, npoints12, Nonconvex, CoordModeOrigin );

	XPoint points13[] = {
		{ (53 + xCoordinate)*xScale , (35 + yCoordinate)*yScale },
		{ (52 + xCoordinate)*xScale , (33 + yCoordinate)*yScale },
		{ (56 + xCoordinate)*xScale , (33 + yCoordinate)*yScale },
		{ (55 + xCoordinate)*xScale , (35 + yCoordinate)*yScale },
		{ (53 + xCoordinate)*xScale , (35 + yCoordinate)*yScale }
	};
	int npoints13 = 5;
	XFillPolygon(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[6], points13, npoints13, Convex, CoordModeOrigin );
}