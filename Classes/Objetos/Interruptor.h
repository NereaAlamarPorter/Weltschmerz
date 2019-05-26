#ifndef __INTERRUPTOR_H__
#define __INTERRUPTOR_H__

#include "cocos2d.h"

USING_NS_CC;

class Interruptor : public cocos2d::Layer
{

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite *interruptor1;
	cocos2d::Sprite *interruptor2;
	int _tipo;

public:
	Interruptor(cocos2d::Layer *layer, int X, int Y);
	int diferenceY;
	int Xx;
	bool activado = false;

	void setPosition(float X, float Y);
	Vec2 Interruptor::getPosition();
	void encender();
	void changeDisp(bool estado);
	int Action(float Rx, float Ry);
	void reposition();

};

#endif //__INTERRUPTOR_H__