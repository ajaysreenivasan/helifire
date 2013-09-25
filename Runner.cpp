#include <X11/Xlib.h>
#include <iostream>
#include <list>
#include <cstdlib>
#include <sys/time.h>
#include <math.h>
#include <stdio.h>
#include <X11/Xutil.h>
#include <ctime>
#include <unistd.h>

#include "GameObject.h"
#include "Helicopter.h"
#include "Building.h"
#include "Turret.h"
#include "GameEffects.h"

using namespace std;

static const int BORDER = 5;
static const int FPS = 45;
static const int BUFFERSIZE = 10;
static const int GRAPHICS_CONTEXT_COUNT = 13;

static const int DEFAULT_SCROLL_SPEED = 2;
static const int DEFAULT_X_SCALE = 1;
static const int DEFAULT_Y_SCALE = 1;

static const int DEFAULT_SCREEN_WIDTH = 600;
static const int DEFAULT_SCREEN_HEIGHT = 400;

static const int DEFAULT_ENEMY_MISSILE_SPEED = 3;
static const int DEFAULT_TURRET_SPAWN_RATE = 10;
static const int DEFAULT_TURRET_FIRE_RATE = 40;

static Helicopter* playerHelicopter = new Helicopter();

static bool leftPressed = false;
static bool rightPressed = false;
static bool upPressed = false;
static bool downPressed = false;
static bool fireMissilePressed = false;
static bool dropBombPressed = false;
static bool pauseEnabled = true;
static bool godModeEnabled = false;
static bool gameOver = false;
static bool replay = true;

static std::list<Building*> buildingList;
static std::list<Turret*> turretList;
static std::list<Missile*> missileList;
static std::list<Bomb*> bombList;
static std::list<EnemyMissile*> enemyMissileList;
static std::list<GameEffects*> gameEffectsList;

static std::list<Building *>::iterator buildingListBegin = buildingList.begin();
static std::list<Building *>::iterator buildingListEnd = buildingList.end();
static std::list<Turret *>::iterator turretListBegin = turretList.begin();
static std::list<Turret *>::iterator turretListEnd = turretList.end();
static std::list<Missile *>::iterator missileListBegin = missileList.begin();
static std::list<Missile *>::iterator missileListEnd = missileList.end();
static std::list<Bomb *>::iterator bombListBegin = bombList.begin();
static std::list<Bomb *>::iterator bombListEnd = bombList.end();
static std::list<EnemyMissile *>::iterator enemyMissileListBegin = enemyMissileList.begin();
static std::list<EnemyMissile *>::iterator enemyMissileListEnd = enemyMissileList.end();
static std::list<GameEffects *>::iterator gameEffectsListBegin = gameEffectsList.begin();
static std::list<GameEffects *>::iterator gameEffectsListEnd = gameEffectsList.end();

static XSizeHints hints;

Display* GameInfo::display;
Window GameInfo::window;
GC GameInfo::graphicsContextList[GRAPHICS_CONTEXT_COUNT];
int GameInfo::screen;

Pixmap GameInfo::pixmap;
int GameInfo::width;
int GameInfo::height;

int GameInfo::defaultScreenWidth;
int GameInfo::defaultScreenHeight;

double GameInfo::xScale;
double GameInfo::yScale;

double GameInfo::scrollSpeed;
double GameInfo::enemyMissileSpeed;

int GameInfo::turretFireRate = DEFAULT_TURRET_FIRE_RATE;
int GameInfo::turretSpawnRate = DEFAULT_TURRET_SPAWN_RATE;


void drawSplashScreen ()
{
	XFillRectangle(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[2], 100 * GameInfo::xScale, 50 * GameInfo::yScale, 
		400 * GameInfo::xScale, 300* GameInfo::yScale);
	XFillRectangle(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[3], 120 * GameInfo::xScale, 70 * GameInfo::yScale, 
		360 * GameInfo::xScale, 260* GameInfo::yScale);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 140 * GameInfo::xScale, 90 * GameInfo::yScale,
		"Ajay Sreenivasan 951",20);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 140 * GameInfo::xScale, 110 * GameInfo::yScale,
		"Instructions:",13);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 150 * GameInfo::xScale, 120 * GameInfo::yScale,
		"Destroy the turrets while avoiding their attacks.",49);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 150 * GameInfo::xScale, 130 * GameInfo::yScale,
		"Flying into a turret will hurt you.",35);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 150 * GameInfo::xScale, 140 * GameInfo::yScale,
		"Crashing into a building leads to an instant game over.",55);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 140 * GameInfo::xScale, 160 * GameInfo::yScale,
		"Controls:",9);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 150 * GameInfo::xScale, 170 * GameInfo::yScale,
		"Up - w",6);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 150 * GameInfo::xScale, 180 * GameInfo::yScale,
		"Down - s",8);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 150 * GameInfo::xScale, 190 * GameInfo::yScale,
		"Left - a",8);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 150 * GameInfo::xScale, 200 * GameInfo::yScale,
		"Right - d",9);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 150 * GameInfo::xScale, 210 * GameInfo::yScale,
		"Pause/Unpause - f",17);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 150 * GameInfo::xScale, 220 * GameInfo::yScale,
		"Shoot Missile - e",17);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 150 * GameInfo::xScale, 230 * GameInfo::yScale,
		"Drop Bomb - Space",17);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 150 * GameInfo::xScale, 240 * GameInfo::yScale,
		"Quit - q",8);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 140 * GameInfo::xScale, 260 * GameInfo::yScale,
		"Settings:",9);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 150 * GameInfo::xScale, 270 * GameInfo::yScale,
		"Press p to toggle Godmode on/off.",33);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 150 * GameInfo::xScale, 280 * GameInfo::yScale,
		"Increase/Decrease scroll speed - t/y",36);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 150 * GameInfo::xScale, 290 * GameInfo::yScale,
		"Increase/Decrease turret fire rate - u/i",40);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 150 * GameInfo::xScale, 300 * GameInfo::yScale,
		"Increase/Decrease turret frequency - g/h",40);
}

void drawGameOverScreen ()
{
	XFillRectangle(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[2], 100 * GameInfo::xScale, 50 * GameInfo::yScale, 
		400 * GameInfo::xScale, 300* GameInfo::yScale);
	XFillRectangle(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[3], 120 * GameInfo::xScale, 70 * GameInfo::yScale, 
		360 * GameInfo::xScale, 260* GameInfo::yScale);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 140 * GameInfo::xScale, 90 * GameInfo::yScale,
		"GG. No re.", 10);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 140 * GameInfo::xScale, 100 * GameInfo::yScale,
		"You've died, either by getting shot down or crashing into a building.", 57);
	XDrawString(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[0], 150 * GameInfo::xScale, 150 * GameInfo::yScale,
		"Press q to quit.", 16);
}

void error(std::string message){
	std::cerr << message << std::endl;
	exit(0);
}

bool collisionCheck(const Hitbox hitbox1, const Hitbox hitbox2){
	if (hitbox1.leftBorder < hitbox2.rightBorder && hitbox1.rightBorder > hitbox2.leftBorder && hitbox1.topBorder < hitbox2.bottomBorder && hitbox1.bottomBorder> hitbox2.topBorder){
		return true;
	}
	return false;
}

void initializeGraphicsContexts(){
	int i;

	// Black Line, Transparent Fill
	i = 0;
	GameInfo::graphicsContextList[i] = XCreateGC(GameInfo::display, GameInfo::window, 0, 0);
	XSetForeground(GameInfo::display, GameInfo::graphicsContextList[i], BlackPixel(GameInfo::display, GameInfo::screen));
	XSetBackground(GameInfo::display, GameInfo::graphicsContextList[i], WhitePixel(GameInfo::display, GameInfo::screen));
	XSetFillStyle(GameInfo::display, GameInfo::graphicsContextList[i], FillSolid);
	XSetLineAttributes(GameInfo::display, GameInfo::graphicsContextList[i],
		1, LineSolid, CapButt, JoinRound);

	// White Line, Transparent Fill
	i = 1;
	GameInfo::graphicsContextList[i] = XCreateGC(GameInfo::display, GameInfo::window, 0, 0);
	XSetForeground(GameInfo::display, GameInfo::graphicsContextList[i], WhitePixel(GameInfo::display, GameInfo::screen));
	XSetBackground(GameInfo::display, GameInfo::graphicsContextList[i], BlackPixel(GameInfo::display, GameInfo::screen));
	XSetFillStyle(GameInfo::display, GameInfo::graphicsContextList[i], FillSolid);
	XSetLineAttributes(GameInfo::display, GameInfo::graphicsContextList[i],
		1, LineSolid, CapButt, JoinRound);

	// Black Fill, Opaque
	i = 2;
	GameInfo::graphicsContextList[i] = XCreateGC(GameInfo::display, GameInfo::window, 0, 0);
	XSetForeground(GameInfo::display, GameInfo::graphicsContextList[i], 0x000000);
	XSetFillStyle(GameInfo::display, GameInfo::graphicsContextList[i], FillSolid);
	XSetLineAttributes(GameInfo::display, GameInfo::graphicsContextList[i],
		1, LineSolid, CapButt, JoinBevel);

	// White Fill, Opaque
	i = 3;
	GameInfo::graphicsContextList[i] = XCreateGC(GameInfo::display, GameInfo::window, 0, 0);
	XSetForeground(GameInfo::display, GameInfo::graphicsContextList[i], 0xEBEBEB);
	XSetFillStyle(GameInfo::display, GameInfo::graphicsContextList[i], FillSolid);
	XSetLineAttributes(GameInfo::display, GameInfo::graphicsContextList[i],
		1, LineSolid, CapButt, JoinBevel);

	// Grey Fill, Opaque
	i = 4;
	GameInfo::graphicsContextList[i] = XCreateGC(GameInfo::display, GameInfo::window, 0, 0);
	XSetForeground(GameInfo::display, GameInfo::graphicsContextList[i], 0x4D4D4D);
	XSetFillStyle(GameInfo::display, GameInfo::graphicsContextList[i], FillSolid);
	XSetLineAttributes(GameInfo::display, GameInfo::graphicsContextList[i],
		1, LineSolid, CapButt, JoinBevel);

	// Orange Fill, Opaque
	i = 5;
	GameInfo::graphicsContextList[i] = XCreateGC(GameInfo::display, GameInfo::window, 0, 0);
	XSetForeground(GameInfo::display, GameInfo::graphicsContextList[i], 0xEB7D2C);
	XSetFillStyle(GameInfo::display, GameInfo::graphicsContextList[i], FillSolid);
	XSetLineAttributes(GameInfo::display, GameInfo::graphicsContextList[i],
		1, LineSolid, CapButt, JoinBevel);

	// Red Fill, Opaque
	i = 6;
	GameInfo::graphicsContextList[i] = XCreateGC(GameInfo::display, GameInfo::window, 0, 0);
	XSetForeground(GameInfo::display, GameInfo::graphicsContextList[i], 0xDF0000);
	XSetFillStyle(GameInfo::display, GameInfo::graphicsContextList[i], FillSolid);
	XSetLineAttributes(GameInfo::display, GameInfo::graphicsContextList[i],
		1, LineSolid, CapButt, JoinBevel);

	// Green Fill, Opaque
	i = 7;
	GameInfo::graphicsContextList[i] = XCreateGC(GameInfo::display, GameInfo::window, 0, 0);
	XSetForeground(GameInfo::display, GameInfo::graphicsContextList[i], 0x009700);
	XSetFillStyle(GameInfo::display, GameInfo::graphicsContextList[i], FillSolid);
	XSetLineAttributes(GameInfo::display, GameInfo::graphicsContextList[i],
		1, LineSolid, CapButt, JoinBevel);

	// Yellow Fill, Opaque
	i = 8;
	GameInfo::graphicsContextList[i] = XCreateGC(GameInfo::display, GameInfo::window, 0, 0);
	XSetForeground(GameInfo::display, GameInfo::graphicsContextList[i], 0xFBCF05);
	XSetFillStyle(GameInfo::display, GameInfo::graphicsContextList[i], FillSolid);
	XSetLineAttributes(GameInfo::display, GameInfo::graphicsContextList[i],
		1, LineSolid, CapButt, JoinBevel);

	// Blue Fill, Opaque
	i = 9;
	GameInfo::graphicsContextList[i] = XCreateGC(GameInfo::display, GameInfo::window, 0, 0);
	XSetForeground(GameInfo::display, GameInfo::graphicsContextList[i], 0x4682B4);
	XSetFillStyle(GameInfo::display, GameInfo::graphicsContextList[i], FillSolid);
	XSetLineAttributes(GameInfo::display, GameInfo::graphicsContextList[i],
		1, LineSolid, CapButt, JoinBevel);

	// Black Line, Bevelled for Main Rotor
	i = 10;
	GameInfo::graphicsContextList[i] = XCreateGC(GameInfo::display, GameInfo::window, 0, 0);
	XSetForeground(GameInfo::display, GameInfo::graphicsContextList[i], BlackPixel(GameInfo::display, GameInfo::screen));
	XSetBackground(GameInfo::display, GameInfo::graphicsContextList[i], WhitePixel(GameInfo::display, GameInfo::screen));
	XSetFillStyle(GameInfo::display, GameInfo::graphicsContextList[i], FillSolid);
	XSetLineAttributes(GameInfo::display, GameInfo::graphicsContextList[i],
		5, LineOnOffDash, CapButt, JoinBevel);

	// Black Line, Bevelled for Tail Rotor
	i = 11;
	GameInfo::graphicsContextList[i] = XCreateGC(GameInfo::display, GameInfo::window, 0, 0);
	XSetForeground(GameInfo::display, GameInfo::graphicsContextList[i], BlackPixel(GameInfo::display, GameInfo::screen));
	XSetBackground(GameInfo::display, GameInfo::graphicsContextList[i], WhitePixel(GameInfo::display, GameInfo::screen));
	XSetFillStyle(GameInfo::display, GameInfo::graphicsContextList[i], FillSolid);
	XSetLineAttributes(GameInfo::display, GameInfo::graphicsContextList[i],
		10, LineOnOffDash, CapButt, JoinBevel);
}

void initializeGame(int argc, char* argv[]){
	unsigned long white;
	unsigned long black;

	GameInfo::display = XOpenDisplay("");
	if(!GameInfo::display)
		error("Error: Cannot open display.");

	GameInfo::screen = DefaultScreen(GameInfo::display);
	GameInfo::scrollSpeed = DEFAULT_SCROLL_SPEED;
	GameInfo::enemyMissileSpeed = DEFAULT_ENEMY_MISSILE_SPEED;

	white = XWhitePixel(GameInfo::display, GameInfo::screen);
	black = XBlackPixel(GameInfo::display, GameInfo::screen);

	GameInfo::xScale = DEFAULT_X_SCALE;
	GameInfo::yScale = DEFAULT_Y_SCALE;

	XSizeHints hints;
	hints.x = 100;
	hints.y = 100;
	hints.width = DEFAULT_SCREEN_WIDTH;
	hints.height = DEFAULT_SCREEN_HEIGHT;
	hints.flags = PPosition | PSize;

	GameInfo::window = XCreateSimpleWindow(
		GameInfo::display,						// display where window appears
		DefaultRootWindow(GameInfo::display),	// window's parent in window tree
		hints.x, hints.y,						// upper left corner location
		hints.width, hints.height,				// size of the window
		BORDER,									// width of window's border
		black,									// window border colour
		white );								// window background colour

	XSetStandardProperties(
		GameInfo::display,		// display containing the window
		GameInfo::window,		// window whose properties are set
		"Helicopterz",			// window's title
		"Helicopterz",			// icon's title
		None,				// pixmap for the icon
		argv, argc,			// applications command line args
		&hints );			// size hints for the window

	initializeGraphicsContexts();

	XSelectInput(GameInfo::display, GameInfo::window,
		ButtonPressMask | KeyPressMask | KeyReleaseMask | ExposureMask | PointerMotionMask | EnterWindowMask | LeaveWindowMask  
		);

	int depth = DefaultDepth(GameInfo::display, DefaultScreen(GameInfo::display));

	GameInfo::pixmap = XCreatePixmap(GameInfo::display, GameInfo::window, hints.width, hints.height, depth);
	GameInfo::width = hints.width;
	GameInfo::height = hints.height;

	GameInfo::defaultScreenWidth = DEFAULT_SCREEN_WIDTH;
	GameInfo::defaultScreenHeight = DEFAULT_SCREEN_HEIGHT;

	XMapRaised(GameInfo::display, GameInfo::window);
	XFlush(GameInfo::display);
	//sleep(2);
}

void redraw(){
	XWindowAttributes windowInfo;
	XGetWindowAttributes(GameInfo::display, GameInfo::window, &windowInfo);
	unsigned int currentWindowWidth = windowInfo.width;
	unsigned int currentWindowHeight = windowInfo.height;

	GameInfo::xScale = (double)currentWindowWidth/(double)GameInfo::defaultScreenWidth;
	GameInfo::yScale = (double)currentWindowHeight/(double)GameInfo::defaultScreenHeight;
	XFreePixmap(GameInfo::display, GameInfo::pixmap);
	int depth = DefaultDepth(GameInfo::display, DefaultScreen(GameInfo::display));
	GameInfo::pixmap = XCreatePixmap(GameInfo::display, GameInfo::window, currentWindowWidth, currentWindowHeight, depth);
	GameInfo::width = currentWindowWidth;
	GameInfo::height = currentWindowHeight;

	XFillRectangle(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[9], 0, 0, GameInfo::width, GameInfo::height);

	buildingListBegin = buildingList.begin();
	buildingListEnd = buildingList.end();

	turretListBegin = turretList.begin();
	turretListEnd = turretList.end();

	missileListBegin = missileList.begin();
	missileListEnd = missileList.end();

	bombListBegin = bombList.begin();
	bombListEnd = bombList.end();

	enemyMissileListBegin = enemyMissileList.begin();
	enemyMissileListEnd = enemyMissileList.end();	

	gameEffectsListBegin = gameEffectsList.begin();
	gameEffectsListEnd = gameEffectsList.end();	

	if(pauseEnabled)
	{
		drawSplashScreen();
	}
	else if(gameOver)
	{
		drawGameOverScreen();
	}
	else
	{
		while( buildingListBegin != buildingListEnd ) {
			Building* building = *buildingListBegin;
			building->draw();
			buildingListBegin++;
		}
		playerHelicopter->draw();
		while( enemyMissileListBegin != enemyMissileListEnd ) {
			EnemyMissile* enemyMissile = *enemyMissileListBegin;
			enemyMissile->draw();
			enemyMissileListBegin++;
		}
		while( turretListBegin != turretListEnd ) {
			Turret* turret = *turretListBegin;
			turret->draw();
			turretListBegin++;
		}

		while( missileListBegin != missileListEnd ) {
			Missile* missile = *missileListBegin;
			missile->draw();
			missileListBegin++;
		}
		while( bombListBegin != bombListEnd ) {
			Bomb* bomb = *bombListBegin;
			bomb->draw();
			bombListBegin++;
		}
		while( gameEffectsListBegin != gameEffectsListEnd ) {
			GameEffects* gf = *gameEffectsListBegin;
			gf->drawExplosions();
			gameEffectsListBegin++;
		}

		playerHelicopter->drawHealthBar();	
	}

	XCopyArea(GameInfo::display, GameInfo::pixmap, GameInfo::window, GameInfo::graphicsContextList[0], 0, 0, GameInfo::width, GameInfo::height, 0, 0);
	XFlush( GameInfo::display );
}

unsigned long now() {
	timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

void handleKeyPress(XEvent &event){
	KeySym key;
	char text[BUFFERSIZE];

	int i = XLookupString( 
		(XKeyEvent *)&event, 	// the keyboard event
		text, 					// buffer when text will be written
		BUFFERSIZE, 			// size of the text buffer
		&key, 					// workstation-independent key symbol
		NULL );					// pointer to a composeStatus structure (unused)
	if ( i == 1) {
		if (text[0] == 'q') {
			error("Terminating normally.");
		}
		else if (text[0] == 'w'){
			upPressed = true;
		}
		else if (text[0] == 's'){
			downPressed = true;
		}
		else if (text[0] == 'd'){
			rightPressed = true;
		}
		else if (text[0] == 'a'){
			leftPressed = true;
		}
		else if (text[0] == 'e'){
			fireMissilePressed = true;
		}
		else if (text[0] == ' '){
			dropBombPressed = true;
		}
		else if (text[0] == 'f'){
			pauseEnabled = !pauseEnabled;
		}
		else if (text[0] == 'p'){
			godModeEnabled = !godModeEnabled;
		}
		else if (text[0] == 't'){
			if(GameInfo::scrollSpeed < 8)
				GameInfo::scrollSpeed++;
		}
		else if (text[0] == 'y'){
			if(GameInfo::scrollSpeed > 1)
				GameInfo::scrollSpeed--;
		}
		else if (text[0] == 'u'){
			if(GameInfo::turretFireRate > 2)
				GameInfo::turretFireRate--;
		}
		else if (text[0] == 'i'){
			if(GameInfo::turretFireRate < 15)
				GameInfo::turretFireRate++;
		}
		else if (text[0] == 'g'){
			if(GameInfo::turretSpawnRate > 1)
				GameInfo::turretSpawnRate--;
		}
		else if (text[0] == 'h'){
			if(GameInfo::turretSpawnRate < 10)
				GameInfo::turretSpawnRate++;
		}
	}
}

void handleKeyRelease(XEvent &event) {
	KeySym key;
	char text[BUFFERSIZE];

	int i = XLookupString( 
		(XKeyEvent *)&event, 	// the keyboard event
		text, 					// buffer when text will be written
		BUFFERSIZE, 			// size of the text buffer
		&key, 					// workstation-independent key symbol
		NULL );					// pointer to a composeStatus structure (unused)
	if ( i == 1) {
		if (text[0] == 'q') {
			error("Terminating normally.");
		}
		else if (text[0] == 'w'){
			upPressed = false;
		}
		else if (text[0] == 's'){
			downPressed = false;
		}
		else if (text[0] == 'd'){
			rightPressed = false;
		}
		else if (text[0] == 'a'){
			leftPressed = false;
		}
		else if (text[0] == 'e'){
			fireMissilePressed = false;
		}
		else if (text[0] == ' '){
			dropBombPressed = false;
		}
	}
}

void motionHandler(bool upPressed, bool downPressed, bool leftPressed, bool rightPressed){
	if(upPressed == true){
		playerHelicopter->updateYVelocity(-1);
	}
	if(downPressed == true){
		playerHelicopter->updateYVelocity(1);
	}
	if(leftPressed == true){
		playerHelicopter->updateXVelocity(-1);
	}
	if(rightPressed == true){
		playerHelicopter->updateXVelocity(1);
	}

	if(leftPressed == false && rightPressed == false)
		playerHelicopter->xSlowDown();
	if(downPressed == false && upPressed == false)
		playerHelicopter->ySlowDown();
}

void eventLoop() {
	Building* newBuilding = new Building();
	buildingList.push_back(newBuilding);

	XEvent event;

	unsigned long lastRepaint = 0;
	int inside = 0;

	int emptyBuildingCount = 0;

	while( true ) {
		if (XPending(GameInfo::display) > 0) {
			XNextEvent(GameInfo::display, &event );
			switch( event.type ) {
			case KeyPress:
				handleKeyPress(event);
				break;
			case KeyRelease:
				handleKeyRelease(event);
				break;
			}
		}
		unsigned long end = now();

		if (end - lastRepaint > 1000000/FPS) {
			if(pauseEnabled == false){
				motionHandler(upPressed, downPressed, leftPressed, rightPressed);

				if((*(--buildingList.end()))->getHitbox().rightBorder < GameInfo::defaultScreenWidth){
					Building* newBuilding = new Building();

					int spawn = (rand() % 20 + 1)%GameInfo::turretSpawnRate ;

					if(spawn == 0){
						Turret* newTurret = new Turret(*newBuilding);
						turretList.push_back(newTurret);
					} 
					else if(spawn != 0){
						emptyBuildingCount++;
						if(emptyBuildingCount >= 4){
							Turret* newTurret = new Turret(*newBuilding);
							turretList.push_back(newTurret);
							emptyBuildingCount = 0;
						}
					}

					buildingList.push_back(newBuilding);
				}

				turretListBegin = turretList.begin();
				while(turretListBegin != turretListEnd){
					Turret *turret = *turretListBegin;
					turret->updateOnScreenPosition();
					if(turret->missileReady()){
						EnemyMissile* enemyMissile = turret->fireMissile();
						enemyMissileList.push_back(enemyMissile);
					}
					turretListBegin++;
				}

				if(fireMissilePressed){
					if(playerHelicopter->missileReady()) {
						Missile* newMissile = playerHelicopter->fireMissile();
						missileList.push_back(newMissile);
					}
				}

				if(dropBombPressed){
					if(playerHelicopter->bombReady()) {
						Bomb* newBomb = playerHelicopter->dropBomb();
						bombList.push_back(newBomb);
					}
				}

				buildingListBegin = buildingList.begin();
				turretListBegin = turretList.begin();
				missileListBegin = missileList.begin();
				bombListBegin = bombList.begin();
				enemyMissileListBegin = enemyMissileList.begin();
				gameEffectsListBegin = gameEffectsList.begin();

				buildingListEnd = buildingList.end();
				turretListEnd = turretList.end();
				missileListEnd = missileList.end();
				bombListEnd = bombList.end();
				enemyMissileListEnd = enemyMissileList.end();
				gameEffectsListEnd = gameEffectsList.end();

				while(gameEffectsListBegin != gameEffectsListEnd) {
					GameEffects* gameEffects = *gameEffectsListBegin;
					gameEffects->updateFrameCount();

					if(gameEffects->getFrameCount() > 5){
						delete gameEffects;
						gameEffectsListBegin = gameEffectsList.erase(gameEffectsListBegin);
					}

					gameEffectsListBegin++;
				}

				// Delete buildings that have scrolled off screen
				while(buildingListBegin != buildingListEnd) {
					Building* building = *buildingListBegin;
					building->updateOnScreenPosition();

					if(building->getHitbox().rightBorder < 0 - building->getBuildingWidth()){
						delete building;
						buildingListBegin = buildingList.erase(buildingListBegin);
					}

					buildingListBegin++;
				}

				// Delete turrets that have scrolled off screen
				while(turretListBegin != turretListEnd) {
					Turret* turret = *turretListBegin;

					if(turret->getHitbox().rightBorder < 0){
						delete turret;
						turretListBegin = turretList.erase(turretListBegin);
						turret = *turretListBegin;
					}

					turretListBegin++;
				}

				// Delete missiles that have scrolled off screen
				while(missileListBegin != missileListEnd) {
					Missile* missile = *missileListBegin;
					missile->updateCoordinates();

					if(missile->getHitbox().leftBorder > GameInfo::defaultScreenWidth || missile->getHitbox().topBorder > GameInfo::defaultScreenHeight){
						delete missile;
						missileListBegin = missileList.erase(missileListBegin);
						missile = *missileListBegin;
					}

					missileListBegin++;
				}

				// Delete bombs that have scrolled off screen
				while(bombListBegin != bombListEnd) {
					Bomb* bomb = *bombListBegin;
					bomb->updateCoordinates();

					if(bomb->getHitbox().leftBorder > GameInfo::defaultScreenWidth || bomb->getHitbox().topBorder > GameInfo::defaultScreenHeight){
						delete bomb;
						bombListBegin = bombList.erase(bombListBegin);
					}

					bombListBegin++;
				}

				// Delete enemy missiles that have scrolled off screen
				while(enemyMissileListBegin != enemyMissileListEnd) {
					EnemyMissile* enemyMissile = *enemyMissileListBegin;
					enemyMissile->updateCoordinates();

					if(enemyMissile->getHitbox().rightBorder < 0 || enemyMissile->getHitbox().bottomBorder < 0){
						delete enemyMissile;					
						enemyMissileListBegin = enemyMissileList.erase(enemyMissileListBegin);
					}

					enemyMissileListBegin++;
				}

				// Check if the player is still alive
				if(playerHelicopter->getHealth() == 0){
					gameOver = true;
				}

				// Update the helicopter's coordinates and weapon cooldown
				playerHelicopter->updateCoordinates();
				playerHelicopter->decreaseCooldown();

				buildingListBegin = buildingList.begin();
				turretListBegin = turretList.begin();
				missileListBegin = missileList.begin();
				bombListBegin = bombList.begin();
				enemyMissileListBegin = enemyMissileList.begin();

				buildingListEnd = buildingList.end();
				turretListEnd = turretList.end();
				missileListEnd = missileList.end();
				bombListEnd = bombList.end();
				enemyMissileListEnd = enemyMissileList.end();
				gameEffectsListEnd = gameEffectsList.end();

				if(!godModeEnabled){
					// Check if the player has crashed into a building
					while(buildingListBegin != buildingListEnd){
						Building* building = *buildingListBegin;

						if(collisionCheck(playerHelicopter->getHitbox(), building->getHitbox())){
							gameOver = true;
						}

						buildingListBegin++;
					}

					// Check if the player has crashed into a turret
					while(turretListBegin != turretListEnd){
						Turret* turret = *turretListBegin;

						if(collisionCheck(playerHelicopter->getHitbox(), turret->getHitbox())){
							playerHelicopter->decreaseHealth(1);
						}

						turretListBegin++;
					}

					// Check if an enemy missile has hit the player
					while(enemyMissileListBegin != enemyMissileListEnd){
						EnemyMissile* enemyMissile = *enemyMissileListBegin;

						if(collisionCheck(playerHelicopter->getHitbox(), enemyMissile->getHitbox())){
							delete enemyMissile;
							enemyMissileListBegin = enemyMissileList.erase(enemyMissileListBegin);
							enemyMissile = *enemyMissileListBegin;

							playerHelicopter->decreaseHealth();
						}

						enemyMissileListBegin++;
					}
				}

				missileListBegin = missileList.begin();				
				missileListEnd = missileList.end();
				bombListBegin = bombList.begin();
				bombListEnd = bombList.end();

				// Check if the player has destroyed a turret
				while(missileListBegin != missileListEnd){
					Missile* missile = *missileListBegin;

					turretListBegin = turretList.begin();
					turretListEnd = turretList.end();
					while(turretListBegin != turretListEnd){
						Turret* turret = *turretListBegin;
						if(collisionCheck(missile->getHitbox(), turret->getHitbox())){
							GameEffects *gameEffects = new GameEffects(missile->getHitbox().rightBorder, missile->getHitbox().bottomBorder);
							gameEffectsList.push_back(gameEffects);

							delete turret;
							turretListBegin = turretList.erase(turretListBegin);
							turret = *turretListBegin;

							delete missile;
							missileListBegin = missileList.erase(missileListBegin);
							break;
						}
						turretListBegin++;
					}
					missileListBegin++;
				}

				turretListBegin = turretList.begin();
				turretListEnd = turretList.end();

				while(bombListBegin != bombListEnd){
					Bomb* bomb = *bombListBegin;

					turretListBegin = turretList.begin();
					turretListEnd = turretList.end();
					while(turretListBegin != turretListEnd){
						Turret* turret = *turretListBegin;
						if(collisionCheck(bomb->getHitbox(), turret->getHitbox())){
							GameEffects *gameEffects = new GameEffects(bomb->getHitbox().rightBorder, bomb->getHitbox().bottomBorder);
							gameEffectsList.push_back(gameEffects);

							delete turret;
							turretListBegin = turretList.erase(turretListBegin);
							turret = *turretListBegin;

							delete bomb;
							bombListBegin = bombList.erase(bombListBegin);
							break;
						}
						turretListBegin++;
					}
					bombListBegin++;
				}


				missileListBegin = missileList.begin();				
				missileListEnd = missileList.end();

				while(missileListBegin != missileListEnd){
					Missile* missile = *missileListBegin;

					enemyMissileListBegin = enemyMissileList.begin();
					enemyMissileListEnd = enemyMissileList.end();
					while(enemyMissileListBegin != enemyMissileListEnd){
						EnemyMissile* enemyMissile = *enemyMissileListBegin;
						if(collisionCheck(missile->getHitbox(), enemyMissile->getHitbox())){
							GameEffects *gameEffects = new GameEffects(missile->getHitbox().rightBorder, missile->getHitbox().bottomBorder);
							gameEffectsList.push_back(gameEffects);

							delete enemyMissile;
							enemyMissileListBegin = enemyMissileList.erase(enemyMissileListBegin);
							enemyMissile = *enemyMissileListBegin;

							delete missile;
							missileListBegin = missileList.erase(missileListBegin);
							break;
						}
						enemyMissileListBegin++;
					}
					missileListBegin++;
				}


				bombListBegin = bombList.begin();				
				bombListEnd = bombList.end();
				buildingListBegin = buildingList.begin();				
				buildingListEnd = buildingList.end();

				while(bombListBegin != bombListEnd){
					Bomb* bomb = *bombListBegin;

					buildingListBegin = buildingList.begin();
					buildingListEnd = buildingList.end();
					while(buildingListBegin != buildingListEnd){
						Building* building = *buildingListBegin;
						if(collisionCheck(bomb->getHitbox(), building->getHitbox())){
							GameEffects *gameEffects = new GameEffects(bomb->getHitbox().rightBorder, bomb->getHitbox().bottomBorder);
							gameEffectsList.push_back(gameEffects);

							delete bomb;
							bombListBegin = bombList.erase(bombListBegin);
							break;
						}
						buildingListBegin++;
					}
					bombListBegin++;
				}

				missileListBegin = missileList.begin();				
				missileListEnd = missileList.end();
				buildingListBegin = buildingList.begin();				
				buildingListEnd = buildingList.end();

				while(missileListBegin != missileListEnd){
					Missile* missile = *missileListBegin;

					buildingListBegin = buildingList.begin();
					buildingListEnd = buildingList.end();
					while(buildingListBegin != buildingListEnd){
						Building* building = *buildingListBegin;
						if(collisionCheck(missile->getHitbox(), building->getHitbox())){
							GameEffects *gameEffects = new GameEffects(missile->getHitbox().rightBorder, missile->getHitbox().bottomBorder);
							gameEffectsList.push_back(gameEffects);

							delete missile;
							missileListBegin = missileList.erase(missileListBegin);
							break;
						}
						buildingListBegin++;
					}
					missileListBegin++;
				}
			}

			redraw();
			lastRepaint = now();		
		}

		if (XPending(GameInfo::display) == 0) {
			usleep(1000000/FPS - (end - lastRepaint));
		}
	}
}

int main(int argc, char* argv[]){
	srand(time(NULL));
	initializeGame(argc, argv);
	eventLoop();
	XCloseDisplay(GameInfo::display);
}

