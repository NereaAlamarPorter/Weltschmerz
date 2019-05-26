#ifndef __MONSTRUO_H__
#define __MONSTRUO_H__


#include "cocos2d.h"

USING_NS_CC;

//const int _mtag = 1;


class Monstruo : public cocos2d::Layer
{

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	int _tipo = 12;
	int speed;
	float dx;
	float dy;
	int DX;
	int DY;
	float xius;
	float yius;
	bool ida;		//si ha cojido a rooney
	int jisus;
	bool espera;

public:
	Monstruo(cocos2d::Layer *layer, int X, int Y, int twe); //Constructor

	cocos2d::Sprite *mano; //Sprite

	int diferenceY; //Para moverlo respecto al suelo
	int diferenceY2;
	int Xx;

	Vec2 spawnArmario;
	int pelotas;

	bool existe;		//Si exite (es visible) = true
	int contX;		//Contador mientras esta con vida
	int contY;		//Contador mientras está muerto
	Vec2 spawnPoint;	//Donde reaparece

	int contlibe;		//Contador que acumula pulsaciones de X
	int contlibeMAX;	//Contador que acumula pulsaciones de X, MAXIMO


	//Getters y setters
	void Monstruo::setPosition(int X, int Y);
	Vec2 Monstruo::getPosition();

	void Monstruo::Move();//Para moverlos

	void Monstruo::Move2(Vec2 sA);//Para moverlos
	int Monstruo::takeRooney(int Rx, int Ry);// Para cuando coje a rooney
	void Monstruo::updateConts();
	int Action(int Rx, int Ry);
	void jump(Vec2 sy);

	void Monstruo::perSecond();
	void reposition();
};

#endif //__MONSTRUO_H__