#include <cstdlib>

#include "Turret.h"

Turret::Turret(const Building &building){
	this->turretHeight = TURRET_HEIGHT;
	this->turretWidth = TURRET_WIDTH;

	this->maxCooldown = rand()%20 + GameInfo::turretFireRate;
	this->cooldown = this->maxCooldown;

	this->xCoordinate = building.getXCoordinate() + building.getBuildingWidth()/3;
	this->yCoordinate = building.getYCoordinate() - TURRET_HEIGHT;

	this->hitbox.leftBorder = this->xCoordinate;
	this->hitbox.rightBorder = this->hitbox.leftBorder + TURRET_WIDTH;
	this->hitbox.topBorder = this->yCoordinate;
	this->hitbox.bottomBorder = this->yCoordinate + TURRET_HEIGHT;
}

Turret::~Turret(){
}

void Turret::draw(){
	double xScale = GameInfo::xScale;
	double yScale = GameInfo::yScale;

	XFillRectangle(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[2], xCoordinate*xScale, yCoordinate*yScale, TURRET_WIDTH*xScale, TURRET_HEIGHT*yScale);

	XPoint points13[] = {
		{ (-6 + xCoordinate)*xScale , (30 + yCoordinate)*yScale },
		{ (-2 + xCoordinate)*xScale , (22 + yCoordinate)*yScale },
		{ (16 + xCoordinate)*xScale , (22 + yCoordinate)*yScale },
		{ (20 + xCoordinate)*xScale , (30 + yCoordinate)*yScale },
		{ (-5 + xCoordinate)*xScale , (30 + yCoordinate)*yScale }
	};
	int npoints13 = 5;
	XFillPolygon(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[2], points13, npoints13, Convex, CoordModeOrigin );

}

int Turret::getTurretHeight() const{
	return this->turretHeight;
}

int Turret::getTurretWidth() const{
	return this->turretWidth;
}

bool Turret::missileReady(){
	if(this->cooldown == 0){
		this->resetCooldown();
		return true;
	}
	else{
		this->cooldown--;
		return false;
	}
}

void Turret::resetCooldown(){
	this->cooldown = this->maxCooldown;
}

EnemyMissile* Turret::fireMissile(){
	EnemyMissile* newEnemyMissile = new EnemyMissile(*this);
	return newEnemyMissile;
}