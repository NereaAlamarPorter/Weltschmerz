#ifndef __PLATAFORMA_H__
#define __PLATAFORMA_H__


#include "cocos2d.h"
USING_NS_CC;

const int _ptag = 1;


class Plataforma : public cocos2d::Layer
{

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	int _tipo;

	//Plataformas que desaparecen
	bool desaparece; //Si tiene algun condicionante para desaparecer
	bool existe; //Si exite en este momento
	int tiempoReap; //Tiempo que no existe
	int tiempoDesp; //Tiempo antes de desaparecer



public:
	Plataforma(cocos2d::Layer *layer, int X, int Y, int tipo);


	cocos2d::Sprite *plataforma;

	int diferenceY;
	int Xx;

	void setPosition(int X, int Y);
	Vec2 Plataforma::getPosition();
	void reposition();


};

#endif //__PLATAFORMA_H__