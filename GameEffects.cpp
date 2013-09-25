#include "GameEffects.h"

GameEffects::GameEffects(){
}

GameEffects::GameEffects(int xCoordinate, int yCoordinate){
	this->frameCount = 0;
	this->xCoordinate = xCoordinate;
	this->yCoordinate = yCoordinate;
}

GameEffects::~GameEffects(){
}

void GameEffects::drawExplosions(){
	double xScale = GameInfo::xScale;
	double yScale = GameInfo::yScale;

	if(this->frameCount == 0){
		XFillArc(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[3], (xCoordinate - frameCount - GameInfo::scrollSpeed + 10)*xScale, (yCoordinate + 10)*yScale, 10*xScale, 10*yScale, 0, 64*360); 
	}
	else if(this->frameCount == 1){
		XFillArc(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[5], (xCoordinate - frameCount - GameInfo::scrollSpeed + 5)*xScale, (yCoordinate + 12)*yScale, 20*xScale, 20*yScale, 0, 64*360); 
		XFillArc(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[8], (xCoordinate - frameCount - GameInfo::scrollSpeed + 13)*xScale, (yCoordinate + 15)*yScale, 15*xScale, 15*yScale, 0, 64*360); 
		XFillArc(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[3], (xCoordinate - frameCount - GameInfo::scrollSpeed + 10)*xScale, (yCoordinate + 10)*yScale, 10*xScale, 10*yScale, 0, 64*360); 
	}
	else if(this->frameCount == 2){
		XFillArc(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[6], (xCoordinate - frameCount - GameInfo::scrollSpeed)*xScale, (yCoordinate)*yScale, 25*xScale, 25*yScale, 0, 64*360); 
		XFillArc(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[5], (xCoordinate - frameCount - GameInfo::scrollSpeed + 13)*xScale, (yCoordinate + 5)*yScale, 20*xScale, 20*yScale, 0, 64*360); 
		XFillArc(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[8], (xCoordinate - frameCount - GameInfo::scrollSpeed + 10)*xScale, (yCoordinate + 10)*yScale, 15*xScale, 15*yScale, 0, 64*360); 
		XFillArc(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[3], (xCoordinate - frameCount - GameInfo::scrollSpeed + 10)*xScale, (yCoordinate + 10)*yScale, 10*xScale, 10*yScale, 0, 64*360); 
	}
	else if(this->frameCount == 3){
		XFillArc(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[6], (xCoordinate - frameCount - GameInfo::scrollSpeed)*xScale, yCoordinate*yScale, 30*xScale, 30*yScale, 0, 64*360); 
		XFillArc(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[5], (xCoordinate - frameCount - GameInfo::scrollSpeed + 13)*xScale, (yCoordinate + 5)*yScale, 25*xScale, 25*yScale, 0, 64*360); 
		XFillArc(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[8], (xCoordinate - frameCount - GameInfo::scrollSpeed + 10)*xScale, (yCoordinate + 10)*yScale, 20*xScale, 20*yScale, 0, 64*360); 
	}
	else if(this->frameCount == 4){
		XFillArc(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[6], (xCoordinate - frameCount - GameInfo::scrollSpeed + 5)*xScale, (yCoordinate + 2)*yScale, 20*xScale, 20*yScale, 0, 64*360); 
		XFillArc(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[5], (xCoordinate - frameCount - GameInfo::scrollSpeed + 13)*xScale, (yCoordinate + 5)*yScale, 15*xScale, 15*yScale, 0, 64*360); 
		XFillArc(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[8], (xCoordinate - frameCount - GameInfo::scrollSpeed + 10)*xScale, (yCoordinate + 10)*yScale, 10*xScale, 10*yScale, 0, 64*360); 
	}
	else if(this->frameCount == 5){
		XFillArc(GameInfo::display, GameInfo::pixmap, GameInfo::graphicsContextList[6], (xCoordinate - frameCount - GameInfo::scrollSpeed + 10)*xScale, (yCoordinate + 10)*yScale, 10*xScale, 10*yScale, 0, 64*360);  
	}
}

int GameEffects::getFrameCount(){
	return this->frameCount;
}

void GameEffects::updateFrameCount(){
	this->frameCount++;
}