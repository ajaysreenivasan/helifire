#ifndef _MISSILE_
#define _MISSILE_

#include "Projectile.h"
#include "Helicopter.h"

class Helicopter;

class Missile: public Projectile{
public:
	Missile(const Helicopter &helicopter);
	~Missile();

	void draw();

private:
	static const int MISSILE_WIDTH = 16;
	static const int MISSILE_HEIGHT = 2;
};

#endif