#include "Classes/Enemigos/Fantasma.h"
#include <math.h>

USING_NS_CC;

Fantasma::Fantasma(cocos2d::Layer *layer, int Fx, int Fy)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	existe = true;
	spawnPoint = Vec2(Fx, Fy);
	contvida = 0;	//Maximo 2
	contmuerte = 0;	//Máximo 1
	speed = 8;
	diferenceY = Fy;
	diferenceY2 = diferenceY;
	Xx = Fx;
	dx = 0;
	dy = 0;

	rtaked = false;
	contlibe = 0;
	contlibeMAX = 20;

	fantasma = Sprite::create("images/Nivel1/Fantasma/Fantasma_000.png");
	fantasma->setPosition(spawnPoint);

	/*
	Vector<SpriteFrame*> animframes(20);
	char str[100] = { 0 };
	for (int i = 0; i < 20; i++)
	{
		sprintf(str, "images/Nivel1/Fantasma/Fantasma_%03d.png", i);
		animframes.pushBack(SpriteFrame::create(str,
			Rect(spawnPoint,fantasma->getBoundingBox().size)));
	}

	Animation* animation =	Animation::createWithSpriteFrames(animframes, (0.05f));
	Animate* animate =		Animate::create(animation);
	fantasma->runAction(RepeatForever::create(animate));
	*/
	calculateDirection();

	layer->addChild(fantasma, 1);
}

void Fantasma::setPosition(int X, int Y)
{
	fantasma->setPosition(X, Y);
}

Vec2 Fantasma::getPosition()
{
	return fantasma->getPosition();
}

void Fantasma::Move()
{
	if ( existe && contvida <= 3)
	{
		fantasma->setVisible(true);
		fantasma->setPosition(fantasma->getPosition().x + dx, fantasma->getPosition().y + dy);
		diferenceY2 += dy;
	}
	else
	{
		fantasma->setPosition(spawnPoint);
		fantasma->setVisible(false);
	}
}

void Fantasma::updateConts()
{
	if (existe)
	{
		contvida++;
		if (contvida > 1) {
			existe = false;
			contmuerte = 0;
		}
	}
	else 
	{
		contmuerte++;
		if (contmuerte > 0){
			existe = true;
			contvida = 0;
			calculateDirection();
			diferenceY2 = diferenceY;
		}
	}
}

int Fantasma::takeRooney(int Rx, int Ry)
{
	if (fantasma->getBoundingBox().containsPoint(Vec2(Rx, Ry)) && existe == true)
	{
		rtaked = true;
		existe = false;
		return  _tipo;
	}
	else return NULL;
	
}

void Fantasma::calculateDirection()
{
	spawnAng = rand() % speed;
	int J = rand() % 3;
	if (J > 1) J = 1;
	else if (J < 1) J = -1;
	dy = spawnAng* J;
	while (dy<-6) dy = dy / 2;
	J = rand() % 3;
	if (J > 1) J = 1;
	else if (J < 1) J = -1;
	dx = (speed-spawnAng)* J;

	if (dx>0) fantasma->setFlipX(true);
	else fantasma->setFlipX(false);
}

int Fantasma::Action(int Rx, int Ry)
{
	if (rtaked == false){
		return takeRooney(Rx, Ry);
	}
	else if (existe)
	{
		contlibe++;
		if (contlibe == contlibeMAX)
		{
			existe = false;
			rtaked = false;
			contlibe = 0;
		}
		return _tipo;
	}
	return NULL;
}

void Fantasma::reposition()
{
	fantasma->setPosition(Xx, diferenceY);

	existe = true;
	spawnPoint = Vec2(Xx, diferenceY);
	contvida = 0;	//Maximo 2
	contmuerte = 0;	//Máximo 1
	speed = 8;
	diferenceY = diferenceY;
	diferenceY2 = diferenceY;
	Xx = Xx;
	dx = 0;
	dy = 0;

	rtaked = false;
}