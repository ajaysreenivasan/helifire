#ifndef _BUILDING_
#define _BUILDING_

#include "StationaryObject.h"

class Building: public StationaryObject{
public:
	Building();
	~Building();

	void draw();

	int getBuildingHeight() const;
	int getBuildingWidth() const;

private:
	int buildingHeight;
	int buildingWidth;
};

#endif	