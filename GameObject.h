#ifndef _GAMEOBJECT_
#define _GAMEOBJECT_

#include <X11/Xlib.h>
#include <X11/Xutil.h>

struct GameInfo{
	static Display* display;
	static Window window;
	static GC graphicsContextList[13];
	static int screen;

	static Pixmap pixmap;
	static int width;
	static int height;

	static int defaultScreenWidth;
	static int defaultScreenHeight;

	static double xScale;
	static double yScale;

	static double scrollSpeed;
	static double enemyMissileSpeed;
	static int turretFireRate;
	static int turretSpawnRate;
};

struct Hitbox{
	int leftBorder;
	int rightBorder;
	int topBorder;
	int bottomBorder;
};

class GameObject{
public:
	GameObject();
	~GameObject();

	int getXCoordinate() const;
	int getYCoordinate() const;
	Hitbox getHitbox() const;

	virtual void draw();

	virtual void updateXCoordinate(int xChange);
	virtual void updateYCoordinate(int yChange);
	virtual void updateHitbox(int xChange, int yChange);

protected:
	Hitbox hitbox;
	int xCoordinate;
	int yCoordinate;
};

#endif	