#ifndef __ESTRELLA_H__
#define __ESTRELLA_H__

#include "cocos2d.h"

USING_NS_CC;

class Estrella : public cocos2d::Layer
{

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite *estrella;
	int _tipo=7;

public:
	Estrella(cocos2d::Layer *layer, int X, int Y);
	int diferenceY;
	int Xx;
	bool visible = true;
	bool existe = true;

	void setPosition(float X, float Y);
	Vec2 Estrella::getPosition();
	void coger();
	void aparecer();
	int Action(float Rx, float Ry);
	void reposition();

};

#endif //__ESTRELLA_H__