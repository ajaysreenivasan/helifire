#ifndef _PROJECTILE_
#define _PROJECTILE_

#include "MovingObject.h"

class Projectile: public MovingObject{
public:
	Projectile();
	~Projectile();

	void updateXVelocity(int xVelocityChange);
	void updateYVelocity(int yVelocityChange);
};

#endif