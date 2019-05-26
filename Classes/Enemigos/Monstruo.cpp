#include "Classes/Enemigos/Monstruo.h"
#include <math.h>

USING_NS_CC;

Monstruo::Monstruo(cocos2d::Layer *layer, int Fx, int Fy, int twe)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	spawnPoint = Vec2(Fx, Fy);
	spawnArmario = Vec2(visibleSize.width * 8 - 400, 385);
	pelotas = Fy - spawnArmario.y;

	contX = 0;	//Maximo 2
	contY = 0;	//Máximo 1
	speed = 100;
	diferenceY = Fy;
	diferenceY2 = diferenceY;
	Xx = Fx;
	espera = false;
	existe = true;
	
	xius = 0;
	yius = 0;
	ida = true;
	jisus = twe;

	mano = Sprite::create("images/Nivel1/brazo.png");
	mano->setScale(0.5f);
	mano->setPosition(spawnPoint);

	switch (twe)
	{
	case 0:
		mano->setFlipX(true);
		mano->setFlipY(true);

		dx = 0;
		dy = 1;
		
		DX = 1;
		DY = 1;
		break;
	case 1:
		mano->setFlipX(true);
		mano->setFlipY(false);

		dx = 0;
		dy = -1;
		
		DX = -1;
		DY = -1;
		break;
	case 2:
		mano->setFlipX(false);
		mano->setFlipY(true);

		dx = 0;
		dy = 1;

		DX = 1;
		DY = 1;
		break;
	case 3:
		mano->setFlipX(false);
		mano->setFlipY(false);

		dx = 0;
		dy = -1;

		DX = -1;
		DY = -1;
		break;
	default:
		break;
	}

	layer->addChild(mano, 1);
}

void Monstruo::setPosition(int X, int Y) {mano->setPosition(X, Y);}

Vec2 Monstruo::getPosition()  {	return mano->getPosition();}

void Monstruo::Move()
{
	updateConts();
	if (!espera)
	{
		diferenceY += yius * dy;
		//if (yius == -15) diferenceY = diferenceY2;
	}
	mano->setPosition(mano->getPosition().x + xius, diferenceY);
}

void Monstruo::Move2(Vec2 sA)
{
	sA = spawnArmario;

	//
	int g = DX;
	int a = 100;
	if (ida){
		yius += 5;
		if (yius >= a) ida = false;
	}
	else{
		if (yius == 0) espera = true;
		else{
			yius -= 5;
			if (yius <= -a)ida = true;
		}
	}
	//
	if (!espera)
	{
		diferenceY2 = spawnArmario.y + pelotas + yius*dy;
		//diferenceY += yius*dy;
	}
	else 
	{
		diferenceY2 = spawnArmario.y + pelotas;
	}
	mano->setPosition(mano->getPosition().x + xius, diferenceY2);
}
void Monstruo::jump(Vec2 sY)
{
	//diference
}


void Monstruo::updateConts()
{
	int g = DX;
	int a = 15;
	if (ida)
	{
		//mano->setOpacity(250);
		//mano->setOpacity(mano->getOpacity() - 10);
		yius += 1;
		if (yius >= a)
		{
			ida = false;
		}
	}
	else
	{
		if (yius == 0) espera = true;
		else
		{
			//mano->setOpacity(250);
			//mano->setOpacity(mano->getOpacity() - 10);
			yius -= 1;

			if (yius <= -a){
				ida = true;
				//mano->setVisible(false);
				
			}
		}
	}
}

int Monstruo::Action(int Rx, int Ry)
{
	if (mano->getBoundingBox().containsPoint(Vec2(Rx, Ry)) && existe)
	{
		return  _tipo;
	}
	else return NULL;
}

void Monstruo::reposition()
{
	diferenceY = spawnPoint.y;
	mano->setPosition(spawnPoint);
	
	Xx = Xx;

	dx = DX;
	dy = DY;
	espera = false;
	ida = true;
	contX = 0;
	yius = 0;

}

void Monstruo::perSecond()
{
	if (espera)
	{
		contX++;
		if (contX == 2)
		{
			contX = 0;
			espera = false;
			yius--;
		}
	}
}


/*
void Monstruo::updateConts()
{
int g = DX;
if (!ida) g *= -1;

yius = g * (dx/10);
xius = g *(1 + abs(yius) / 10);
dx += g;

g = abs(dx);

if ( g >= speed) ida = false;
else if (g <= 0) ida = true;
}
*/