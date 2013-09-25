#ifndef _ENEMYMISSILE_
#define _ENEMYMISSILE_

#include "Projectile.h"
#include "Turret.h"

class Turret;

class EnemyMissile: public Projectile{
public:
	EnemyMissile(const Turret &turret);
	~EnemyMissile();

	void draw();

private:
	static const int ENEMY_MISSILE_WIDTH = 8;
	static const int ENEMY_MISSILE_HEIGHT = 17;
};

#endif