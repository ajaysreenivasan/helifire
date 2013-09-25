#ifndef _MOVINGOBJECT_
#define _MOVINGOBJECT_

#include "GameObject.h"
class MovingObject: public GameObject{
public:
	MovingObject();
	~MovingObject();

	int getXVelocity() const;
	int getYVelocity() const;

	void updateCoordinates();

	virtual void updateXVelocity(int xVelocityChange) = 0;
	virtual void updateYVelocity(int yVelocityChange) = 0;

protected:
	int xVelocity;
	int yVelocity;
};

#endif	