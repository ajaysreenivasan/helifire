#ifndef _HELICOPTER_
#define _HELICOPTER_

#include "MovingObject.h"
#include "Missile.h"
#include "Bomb.h"

class Missile;
class Bomb;

class Helicopter: public MovingObject{
public:
	Helicopter();
	~Helicopter();

	void draw();
	void drawHealthBar();

	void updateXCoordinate(int xChange);
	void updateYCoordinate(int yChange);

	void updateXVelocity(int xVelocityChange);
	void updateYVelocity(int yVelocityChange);

	void updateHitbox(int xChange, int yChange);

	void xSlowDown();
	void ySlowDown();

	bool missileReady();
	bool bombReady();
	void resetCooldown(int weaponType);
	void decreaseCooldown();

	int getHealth();
	void decreaseHealth();
	void decreaseHealth(int decrement);

	Missile* fireMissile();
	Bomb* dropBomb();

private:
	static const int HELICOPTER_MAX_HEALTH = 100;

	static const int HELICOPTER_MAX_SPEED = 10;
	static const int HELICOPTER_MIN_SPEED = -10;

	static const int HELICOPTER_WIDTH = 84;
	static const int HELICOPTER_HEIGHT = 29;

	static const int MAIN_ROTOR_WIDTH = 70;
	static const int MAIN_ROTOR_HEIGHT = 2;
	static const int TAIL_ROTOR_WIDTH = 13;
	static const int TAIL_ROTOR_HEIGHT = 13;

	static const int MAX_WEAPON_COOLDOWN = 20;

	int missileCooldown;
	int bombCooldown;

	int health;
	int shieldCharge;
};

#endif