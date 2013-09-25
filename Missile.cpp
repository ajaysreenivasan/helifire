#include "Missile.h"

Missile::Missile(const Helicopter &helicopter){
	this->xCoordinate = helicopter.getXCoordinate();
	this->yCoordinate = helicopter.getYCoordinate();

	if(helicopter.getXVelocity() > 0)
		this->xVelocity = helicopter.getXVelocity() + 2;
	else
		this->xVelocity = 4;

	this->yVelocity = 0;

	this->hitbox.leftBorder = this->xCoordinate + 45;
	this->hitbox.rightBorder = this->hitbox.leftBorder + MISSILE_WIDTH;
	this->hitbox.topBorder = this->yCoordinate + 29;
	this->hitbox.bottomBorder = this->hitbox.topBorder + MISSILE_HEIGHT;
}

Missile::~Missile(){
}

void Missile::draw(){
	double xScale = GameInfo::xScale;
	double yScale = GameInfo::yScale;

	XPoint points6[] = {
		{ (45 + xCoordinate)*xScale , (29+ yCoordinate)*yScale },
		{ (60 + xCoordinate)*xScale , (29 + yCoordinate)*yScale },
		{ (61 + xCoordinate)*xScale , (30 + yCoordinate)*yScale },
		{ (60 + xCoordinate)*xScale , (31 + yCoordinate)*yScale },
		{ (45 + xCoordinate)*xScale , (31 + yCoordinate)*yScale },
		{ (45 + xCoordinate)*xScale , (29 + yCoordinate)*yScale }
	};
	int npoints6 = 6;
	XFillPolygon(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[3], points6, npoints6, Convex, CoordModeOrigin );
	XDrawLines(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], points6, npoints6, CoordModeOrigin );

	XPoint points7[] = {
		{ (47 + xCoordinate)*xScale , (29 + yCoordinate)*yScale },
		{ (47 + xCoordinate)*xScale , (26 + yCoordinate)*yScale },
		{ (52 + xCoordinate)*xScale , (29 + yCoordinate)*yScale },
		{ (47 + xCoordinate)*xScale , (29 + yCoordinate)*yScale }
	};
	int npoints7 = 4;
	XFillPolygon(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[2], points7, npoints7, Convex, CoordModeOrigin );

	XPoint points8[] = {
		{ (47 + xCoordinate)*xScale , (31 + yCoordinate)*yScale },
		{ (47 + xCoordinate)*xScale , (33 + yCoordinate)*yScale },	
		{ (52 + xCoordinate)*xScale , (31 + yCoordinate)*yScale },
		{ (47 + xCoordinate)*xScale , (31 + yCoordinate)*yScale }
	};
	int npoints8 = 4;
	XFillPolygon(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[2], points8, npoints8, Convex, CoordModeOrigin );

	XPoint points9[] = {
		{ (45 + xCoordinate)*xScale, (29 + yCoordinate)*yScale },
		{ (38 + xCoordinate)*xScale, (30 + yCoordinate)*yScale },
		{ (45 + xCoordinate)*xScale, (31 + yCoordinate)*yScale },
		{ (45 + xCoordinate)*xScale, (29 + yCoordinate)*yScale }
	};
	int npoints9 = 4;
	XFillPolygon(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[6], points9, npoints9, Convex, CoordModeOrigin );
}