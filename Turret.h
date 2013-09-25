#ifndef _TURRET_
#define _TURRET_

#include "StationaryObject.h"
#include "Building.h"
#include "EnemyMissile.h"

class EnemyMissile;

class Turret: public StationaryObject{
public:
	Turret(const Building &building);
	~Turret();

	void draw();

	int getTurretHeight() const;
	int getTurretWidth() const;

	bool missileReady();
	void resetCooldown();

	EnemyMissile* fireMissile();

private:
	static const int TURRET_WIDTH = 14;
	static const int TURRET_HEIGHT = 30;

	int turretHeight;
	int turretWidth;

	int cooldown;
	int maxCooldown;
};

#endif	