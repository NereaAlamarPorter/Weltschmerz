#ifndef __LIMBO_H__
#define __LIMBO_H__


#include "cocos2d.h"
#include "Objetos\Plataforma.h"
#include "Objetos\Puerta.h"

USING_NS_CC;

const int prtsN = 6;

class Limbo: public cocos2d::Layer
{

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	
	Sprite* background; //Fondo
	Plataforma* suelo; //Suelo
	Plataforma* plataforma; //Unica Plataforma
	Puerta* plvl1;
	Puerta* plvl2;
	Puerta* plvl3;
	Puerta* plvl4;
	Puerta* plvl5;
	Puerta* plvl6;

	Puerta* prts[prtsN];
	

	//Puerta* ptodas;




public:

	bool right = false;
	bool left = false;
	bool falling = false;
	bool jumping = false;

	//Variables Mundo
	const Vec2 _gravity = Vec2(0, -900);
	const int speed = 10;
	const int jump = 80 ;
	Vec2 rooneyOrigin;


	Limbo(cocos2d::Layer *layer);
	void Move( int speed);
	void Jump(float jump);
	void Fall();
	int Action(Vec2 pos);
	void removeThinks();
	void desactivePB(float pos);

	void reposition();

	void perSecond(); //funciones que se hagan cada segundo
	int ActionIA(Vec2 pos);

};

#endif