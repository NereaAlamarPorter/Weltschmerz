#ifndef __FANTASMA_H__
#define __FANTASMA_H__


#include "cocos2d.h"

USING_NS_CC;

const int _ftag = 1;


class Fantasma : public cocos2d::Layer
{

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	int _tipo = 12;
	int speed;
	float dx;
	float dy;
	float spawnAng;		//Angulo con el que reaparece
	bool rtaked;		//si ha cojido a rooney

	Vector<SpriteFrame*> animframes();
	Animate* animate;
	Animation* animation;

public:
	Fantasma::Fantasma(cocos2d::Layer *layer, int X, int Y); //Constructor

	cocos2d::Sprite *fantasma; //Sprite

	int diferenceY; //Para moverlo respecto al suelo
	int diferenceY2;
	int Xx;

	bool existe;		//Si exite (es visible) = true
	int contvida;		//Contador mientras esta con vida
	int contmuerte;		//Contador mientras está muerto
	Vec2 spawnPoint;	//Donde reaparece

	int contlibe;		//Contador que acumula pulsaciones de X
	int contlibeMAX;	//Contador que acumula pulsaciones de X, MAXIMO


	//Getters y setters
	void Fantasma::setPosition(int X, int Y);
	Vec2 Fantasma::getPosition();

	void Fantasma::Move();//Para moverlos
	int Fantasma::takeRooney(int Rx, int Ry);// Para cuando coje a rooney
	void Fantasma::updateConts();
	void Fantasma::calculateDirection();
	int Action(int Rx, int Ry);

	void reposition();
};

#endif //__FANTASMA_H__