#ifndef __PUERTA_H__
#define __PUERTA_H__


#include "cocos2d.h"
USING_NS_CC;

const int _puertag = 1;


class Puerta : public cocos2d::Layer
{

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	int _tipo;

public:
	Puerta(cocos2d::Layer *layer, int X, int Y, int tipo);

	bool disponible = false;	//Si se puede usar o no
	bool abierta = false;		//Si esta siendo usada o no
	int diferenceY;
	int Xx;

	cocos2d::Sprite *puerta;

	void setPosition(int X, int Y);
	Vec2 Puerta::getPosition();
	int Action(int Rx, int Ry);
	void changeDisponible(bool g);
	void reposition();



};

#endif