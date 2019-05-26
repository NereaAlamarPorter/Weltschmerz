#ifndef __AGUJERO_H__
#define __AGUJERO_H__

#include "plataforma.h"

#include "cocos2d.h"
USING_NS_CC;

const int _atag = 1;


class Agujero : public cocos2d::Layer 
{
private:
	cocos2d::Size visibleSize; 
	cocos2d::Vec2 origin; 
	int _tipo=13;

public:
	Agujero(cocos2d::Layer *layer, int X, int Y);
	cocos2d::Sprite *agujero;
	int diferenceY;
	int Xx;
	void setPosition(int X, int Y);
	Vec2 Agujero::getPosition();
	int Action(int Rx, int Ry);
	Plataforma* plataforma1;
	Plataforma* plataforma2;
	void reposition();

};

#endif