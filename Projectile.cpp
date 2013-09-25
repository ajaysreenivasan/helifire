#include "Projectile.h"

Projectile::Projectile(){
}

Projectile::~Projectile(){
}

void Projectile::updateXVelocity(int xVelocityChange){
	this->xVelocity += xVelocityChange;
}

void Projectile::updateYVelocity(int yVelocityChange){
	this->yVelocity += yVelocityChange;
}