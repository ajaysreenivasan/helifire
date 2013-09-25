#include "Helicopter.h"
#include <iostream>

Helicopter::Helicopter(){
	this->xCoordinate = 100;
	this->yCoordinate = 100;

	this->hitbox.leftBorder = this->xCoordinate + 7 - TAIL_ROTOR_WIDTH/2;
	this->hitbox.rightBorder = this->hitbox.leftBorder + HELICOPTER_WIDTH + TAIL_ROTOR_WIDTH/2;
	this->hitbox.topBorder = this->yCoordinate + 10 - TAIL_ROTOR_WIDTH/2;
	this->hitbox.bottomBorder = this->hitbox.topBorder + HELICOPTER_HEIGHT;

	this->health = HELICOPTER_MAX_HEALTH;
}

Helicopter::~Helicopter(){
}

void Helicopter::draw(){	
	double xScale = GameInfo::xScale;
	double yScale = GameInfo::yScale;

	// Helicopter Body
	XPoint points[] = {
		{ (6 + xCoordinate)*xScale , (6 + yCoordinate)*yScale },
		{ (10 + xCoordinate)*xScale , (12 + yCoordinate)*yScale },
		{ (14 + xCoordinate)*xScale , (14 + yCoordinate)*yScale },
		{ (36 + xCoordinate)*xScale , (14 + yCoordinate)*yScale },
		{ (42 + xCoordinate)*xScale , (10 + yCoordinate)*yScale },
		{ (56 + xCoordinate)*xScale , (10 + yCoordinate)*yScale },
		{ (60 + xCoordinate)*xScale , (8 + yCoordinate)*yScale },
		{ (66 + xCoordinate)*xScale , (10 + yCoordinate)*yScale },
		{ (80 + xCoordinate)*xScale , (21 + yCoordinate)*yScale },
		{ (82 + xCoordinate)*xScale , (24 + yCoordinate)*yScale },
		{ (83 + xCoordinate)*xScale , (26 + yCoordinate)*yScale },
		{ (82 + xCoordinate)*xScale , (28 + yCoordinate)*yScale },
		{ (78 + xCoordinate)*xScale , (32 + yCoordinate)*yScale },
		{ (74 + xCoordinate)*xScale , (33 + yCoordinate)*yScale },
		{ (44 + xCoordinate)*xScale , (33 + yCoordinate)*yScale },
		{ (40 + xCoordinate)*xScale , (32 + yCoordinate)*yScale },
		{ (38 + xCoordinate)*xScale , (30 + yCoordinate)*yScale },
		{ (36 + xCoordinate)*xScale , (26 + yCoordinate)*yScale },
		{ (32 + xCoordinate)*xScale , (22 + yCoordinate)*yScale },
		{ (8 + xCoordinate)*xScale , (16 + yCoordinate)*yScale },
		{ (6 + xCoordinate)*xScale , (12 + yCoordinate)*yScale },
		{ (4 + xCoordinate)*xScale , (8 + yCoordinate)*yScale },
		{ (6 + xCoordinate)*xScale, (6 + yCoordinate)*yScale }
	};
	int npoints = 23;
	XFillPolygon(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[3], points, npoints, Nonconvex, CoordModeOrigin );
	XDrawLines(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], points, npoints, CoordModeOrigin );

	// Cockpit
	XPoint points5[] = {
		{ (55 + xCoordinate)*xScale , (21 + yCoordinate)*yScale },
		{ (59 + xCoordinate)*xScale , (15 + yCoordinate)*yScale },
		{ (65 + xCoordinate)*xScale , (13 + yCoordinate)*yScale },
		{ (70 + xCoordinate)*xScale , (13 + yCoordinate)*yScale },
		{ (80 + xCoordinate)*xScale , (21 + yCoordinate)*yScale },
		{ (55 + xCoordinate)*xScale , (21 + yCoordinate)*yScale }
	};
	int npoints5 = 6;
	XFillPolygon(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[9], points5, npoints5, Convex, CoordModeOrigin );
	XDrawLines(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], points5, npoints5, CoordModeOrigin );

	// Rotors
	XPoint points4[] = {
		{ (52 + xCoordinate)*xScale , (10 + yCoordinate)*yScale },
		{ (52 + xCoordinate)*xScale , (9 + yCoordinate)*yScale },
		{ (51 + xCoordinate)*xScale , (8 + yCoordinate)*yScale },
		{ (51 + xCoordinate)*xScale , (7 + yCoordinate)*yScale },
		{ (53 + xCoordinate)*xScale , (6 + yCoordinate)*yScale },
		{ (55 + xCoordinate)*xScale , (7 + yCoordinate)*yScale },
		{ (55 + xCoordinate)*xScale , (8 + yCoordinate)*yScale },
		{ (54 + xCoordinate)*xScale , (9 + yCoordinate)*yScale },
		{ (54 + xCoordinate)*xScale , (10 + yCoordinate)*yScale },
		{ (52 + xCoordinate)*xScale , (10 + yCoordinate)*yScale }
	};
	int npoints4 = 10;
	XFillPolygon(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[2], points4, npoints4, Convex, CoordModeOrigin );

	XDrawArc(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[10], (xCoordinate + 20)*xScale, (yCoordinate + 6)*yScale, MAIN_ROTOR_WIDTH*xScale, MAIN_ROTOR_HEIGHT*yScale, 0, 64*360); 
	XFillArc(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[2], (xCoordinate + 5)*xScale, (yCoordinate + 8)*yScale, TAIL_ROTOR_WIDTH/3*xScale, TAIL_ROTOR_HEIGHT/3*yScale, 0, 64*360); 
	XDrawArc(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[11], (xCoordinate)*xScale, (yCoordinate + 3)*yScale, TAIL_ROTOR_WIDTH*xScale, TAIL_ROTOR_HEIGHT*yScale, 0, 64*360); 

	// Bomb
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

	// Weapons Bay
	XPoint points2[] = {
		{ (44 + xCoordinate)*xScale , (28 + yCoordinate)*yScale },
		{ (46 + xCoordinate)*xScale , (26 + yCoordinate)*yScale },
		{ (61 + xCoordinate)*xScale , (24 + yCoordinate)*yScale },
		{ (62 + xCoordinate)*xScale , (25 + yCoordinate)*yScale },
		{ (62 + xCoordinate)*xScale , (28 + yCoordinate)*yScale },
		{ (46 + xCoordinate)*xScale , (28 + yCoordinate)*yScale }
	};
	int npoints2 = 6;
	XFillPolygon(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], points2, npoints2, Convex, CoordModeOrigin );

	XPoint points3[] = {
		{ (50 + xCoordinate)*xScale , (28 + yCoordinate)*yScale },
		{ (58 + xCoordinate)*xScale , (28 + yCoordinate)*yScale },
		{ (58 + xCoordinate)*xScale , (34 + yCoordinate)*yScale },
		{ (50 + xCoordinate)*xScale , (34 + yCoordinate)*yScale },
		{ (50 + xCoordinate)*xScale , (28 + yCoordinate)*yScale }
	};
	int npoints3 = 5;
	XFillPolygon(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], points3, npoints3, Convex, CoordModeOrigin );

	// Missile
	XPoint points6[] = {
		{ (45 + xCoordinate)*xScale , (29 + yCoordinate)*yScale },
		{ (60 + xCoordinate)*xScale , (29 + yCoordinate)*yScale },
		{ (61 + xCoordinate)*xScale , (30 + yCoordinate)*yScale },
		{ (60 + xCoordinate)*xScale , (31 + yCoordinate)*yScale },
		{ (45 + xCoordinate)*xScale , (31 + yCoordinate)*yScale },
		{ (45 + xCoordinate)*xScale , (29 + yCoordinate)*yScale }
	};
	int npoints6 = 6;
	XDrawLines(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[2], points6, npoints6, CoordModeOrigin );

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
}

void Helicopter::drawHealthBar(){
	double xScale = GameInfo::xScale;
	double yScale = GameInfo::yScale;

	XFillRectangle(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[2], 20*xScale, 20*yScale, (560)*xScale, (25)*yScale);
	if(((double)this->health/(double)this->HELICOPTER_MAX_HEALTH) > 0.5)
		XFillRectangle(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[7], 30*xScale, 25*yScale, (double)((540)*((double)this->health/(double)this->HELICOPTER_MAX_HEALTH)*xScale), 15*yScale);
	else if(((double)this->health/(double)this->HELICOPTER_MAX_HEALTH) > 0.30)
		XFillRectangle(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[8], 30*xScale, 25*yScale, (double)((540)*((double)this->health/(double)this->HELICOPTER_MAX_HEALTH)*xScale), 15*yScale);
	else if	(((double)this->health/(double)this->HELICOPTER_MAX_HEALTH) > 0)
		XFillRectangle(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[6], 30*xScale, 25*yScale, (double)((540)*((double)this->health/(double)this->HELICOPTER_MAX_HEALTH)*xScale), 15*yScale);
}

void Helicopter::updateXCoordinate(int xVelocity){
	if(this->hitbox.leftBorder == 0 || (this->hitbox.leftBorder + xVelocity) < 0)
		this->xCoordinate = 0;
	else if((this->hitbox.rightBorder) > GameInfo::defaultScreenWidth){
		this->xCoordinate = GameInfo::defaultScreenWidth - HELICOPTER_WIDTH - TAIL_ROTOR_WIDTH/2 - 1;
		this->xVelocity = 0;
	}
	else{
		this->xCoordinate += xVelocity;
	}
}

void Helicopter::updateYCoordinate(int yVelocity){
	if(this->hitbox.topBorder == 0 || (this->hitbox.topBorder + yVelocity) < 0)
		this->yCoordinate = 0;
	else if(this->hitbox.bottomBorder > GameInfo::defaultScreenHeight){
		this->yCoordinate = GameInfo::defaultScreenHeight - HELICOPTER_HEIGHT - TAIL_ROTOR_WIDTH/2;
		this->yVelocity = 0;	
	}
	else{
		this->yCoordinate += yVelocity;
	}
}

void Helicopter::updateXVelocity(int xVelocityChange){
	if(this->hitbox.leftBorder +  (this->xVelocity + xVelocityChange) < 0){
		if(xVelocity + xVelocityChange < 0){
			this->xVelocity = 0;
		}
	}
	else if(this->hitbox.rightBorder + (this->xVelocity + xVelocityChange) > GameInfo::defaultScreenWidth){
		if(xVelocity + xVelocityChange > 0){
			this->xVelocity = 0;
		}
	}
	else{
		if(this->xVelocity + xVelocityChange < HELICOPTER_MAX_SPEED && this->xVelocity + xVelocityChange > HELICOPTER_MIN_SPEED){
			this->xVelocity += xVelocityChange;
		}
	}
}

void Helicopter::updateYVelocity(int yVelocityChange){
	if(this->hitbox.topBorder +  (this->yVelocity + yVelocityChange) < 0){
		if(yVelocity + yVelocityChange < 0){
			this->yVelocity = 0;
		}
	}
	else if(this->hitbox.bottomBorder + (this->yVelocity + yVelocityChange) > GameInfo::defaultScreenHeight){
		if(yVelocity + yVelocityChange > 0){
			this->xVelocity = 0;
		}
	}
	else{
		if(this->yVelocity + yVelocityChange< HELICOPTER_MAX_SPEED && this->yVelocity  + yVelocityChange> HELICOPTER_MIN_SPEED){
			this->yVelocity += yVelocityChange;
		}
	}
}

void Helicopter::updateHitbox(int xChange, int yChange){
	this->hitbox.leftBorder = this->xCoordinate + 7 - TAIL_ROTOR_WIDTH/2;
	this->hitbox.rightBorder = this->hitbox.leftBorder + HELICOPTER_WIDTH + TAIL_ROTOR_WIDTH/2;
	this->hitbox.topBorder = this->yCoordinate + 10 - TAIL_ROTOR_WIDTH/2;
	this->hitbox.bottomBorder = this->hitbox.topBorder + HELICOPTER_HEIGHT;
}

void Helicopter::xSlowDown(){
	if(this->xVelocity > 0)
		this->updateXVelocity(-1);
	else if(this->xVelocity < 0)
		this->updateXVelocity(1);
}

void Helicopter::ySlowDown(){
	if(this->yVelocity > 0)
		this->updateYVelocity(-1);
	else if(this->yVelocity < 0)
		this->updateYVelocity(1);
}

bool Helicopter::missileReady(){
	if(this->missileCooldown == 0){
		this->resetCooldown(1);
		return true;
	}
	else{
		return false;
	}
}

bool Helicopter::bombReady(){
	if(this->bombCooldown == 0){
		this->resetCooldown(2);
		return true;
	}
	else{
		return false;
	}
}

void Helicopter::resetCooldown(int weaponType){
	if(weaponType == 1)
		this->missileCooldown = this->MAX_WEAPON_COOLDOWN;
	else if(weaponType == 2)
		this->bombCooldown = this->MAX_WEAPON_COOLDOWN;
}

void Helicopter::decreaseCooldown(){
	if(this->missileCooldown != 0)
		this->missileCooldown--;
	if(this->bombCooldown != 0)
		this->bombCooldown--;
}

Missile* Helicopter::fireMissile(){
	Missile* newMissile = new Missile(*this);
	return newMissile;
}

Bomb* Helicopter::dropBomb(){
	Bomb* newBomb = new Bomb(*this);
	return newBomb;
}

void Helicopter::decreaseHealth(){
	this->health -= 10;
}

void Helicopter::decreaseHealth(int decrement){
	this->health -= decrement;
}

int Helicopter::getHealth(){
	return this->health;
}

