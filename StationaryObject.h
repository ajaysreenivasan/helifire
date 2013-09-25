#ifndef _STATIONARYOBJECT_
#define _STATIONARYOBJECT_

#include "GameObject.h"

class StationaryObject: public GameObject{
public:
	StationaryObject();
	~StationaryObject();

	void updateOnScreenPosition();
};

#endif	