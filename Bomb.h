#ifndef _BOMB_
#define _BOMB_

#include "Projectile.h"
#include "Helicopter.h"

class Helicopter;

class Bomb: public Projectile{
public:
	Bomb(const Helicopter &helicopter);
	~Bomb();

	void draw();

private:
	static const int BOMB_WIDTH = 4;
	static const int BOMB_HEIGHT = 10;
};

#endif