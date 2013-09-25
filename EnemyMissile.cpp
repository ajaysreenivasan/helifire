#include "EnemyMissile.h"

EnemyMissile::EnemyMissile(const Turret &turret){
	this->xCoordinate = turret.getXCoordinate() + 2;
	this->yCoordinate = turret.getYCoordinate() - 4;

	this->xVelocity = -GameInfo::scrollSpeed;
	this->yVelocity = -GameInfo::enemyMissileSpeed;

	this->hitbox.leftBorder = this->xCoordinate + 2;
	this->hitbox.rightBorder = this->hitbox.leftBorder + ENEMY_MISSILE_WIDTH;
	this->hitbox.topBorder = this->yCoordinate + 15;
	this->hitbox.bottomBorder = this->hitbox.topBorder + ENEMY_MISSILE_WIDTH;
}

EnemyMissile::~EnemyMissile(){
}

void EnemyMissile::draw(){
	double xScale = GameInfo::xScale;
	double yScale = GameInfo::yScale;
	
	XPoint points9[] = {
		{ (3 + xCoordinate)*xScale, (29 + yCoordinate)*yScale },
		{ (6 + xCoordinate)*xScale, (38 + yCoordinate)*yScale },
		{ (9 + xCoordinate)*xScale, (29 + yCoordinate)*yScale },
		{ (3 + xCoordinate)*xScale, (29 + yCoordinate)*yScale }
	};
	int npoints9 = 4;
	XFillPolygon(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[6], points9, npoints9, Convex, CoordModeOrigin );

	XPoint points61[] = {
		{ (3 + xCoordinate)*xScale , (30 + yCoordinate)*yScale },
		{ (3 + xCoordinate)*xScale , (17 + yCoordinate)*yScale },
		{ (6 + xCoordinate)*xScale , (14 + yCoordinate)*yScale },
		{ (9 + xCoordinate)*xScale , (17 + yCoordinate)*yScale },
		{ (9 + xCoordinate)*xScale , (30 + yCoordinate)*yScale },
		{ (3 + xCoordinate)*xScale , (30 + yCoordinate)*yScale }
	};
	int npoints61 = 6;
	XFillPolygon(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[3], points61, npoints61, Convex, CoordModeOrigin );
	XDrawLines(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[2], points61, npoints61, CoordModeOrigin );

	XPoint points71[] = {
		{ (0 + xCoordinate)*xScale , (29 + yCoordinate)*yScale },
		{ (3 + xCoordinate)*xScale , (23 + yCoordinate)*yScale },
		{ (3 + xCoordinate)*xScale , (28 + yCoordinate)*yScale },
		{ (0 + xCoordinate)*xScale , (29 + yCoordinate)*yScale },
	};
	int npoints71 = 4;
	XFillPolygon(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[2], points71, npoints71, Convex, CoordModeOrigin );

	XFillRectangle(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[2], (6 + xCoordinate)*xScale, (23 + yCoordinate)*yScale, 1*xScale, 5*yScale);

	XPoint points81[] = {
		{ (12 + xCoordinate)*xScale , (29 + yCoordinate)*yScale },
		{ (9 + xCoordinate)*xScale , (23 + yCoordinate)*yScale },
		{ (9 + xCoordinate)*xScale , (28 + yCoordinate)*yScale },
		{ (12 + xCoordinate)*xScale , (29 + yCoordinate)*yScale },
	};
	int npoints81 = 4;
	XFillPolygon(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[2], points81, npoints81, Convex, CoordModeOrigin );
}