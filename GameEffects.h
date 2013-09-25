#ifndef _GAMEEFFECTS_
#define _GAMEEFFECtS_

#include "GameObject.h"

class GameEffects{
public:
	GameEffects();
	GameEffects(int xCoordinate, int yCoordinate);
	~GameEffects();

	void drawExplosions();

	int getFrameCount();
	void updateFrameCount();

private:
	int frameCount;
	int xCoordinate;
	int yCoordinate;
};

#endif