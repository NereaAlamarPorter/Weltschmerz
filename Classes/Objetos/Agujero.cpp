#include "Objetos\Agujero.h"
#include "GameLvl1Scene.h"
#include "Plataforma.h"

USING_NS_CC;

Agujero::Agujero(cocos2d::Layer *layer, int X, int Y)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	agujero = Sprite::create("images/Nivel1/escalones.png");
	agujero->setScale(0.4f);

	layer->addChild(agujero, 1);

	plataforma1 = new Plataforma(layer, X - 110, Y + 59, 8);
	plataforma2 = new Plataforma(layer, X + 110, Y + 59, 8);
	agujero->setPosition(Point(X, Y-30));
	plataforma1->setPosition(X - 110, Y + 59);
	plataforma2->setPosition(X + 110, Y + 59);

	diferenceY = Y-30;
	Xx = X;
}

void Agujero::setPosition(int X, int Y)
{
	agujero->setPosition(X, Y);
	plataforma1->setPosition(X - 110, Y + 59);
	plataforma2->setPosition(X + 110, Y + 59);
}

Vec2 Agujero::getPosition()
{
	return agujero->getPosition();
}
int Agujero::Action(int Rx, int Ry)
{
	if (agujero->getBoundingBox().containsPoint(Vec2(Rx, Ry)))
	{
		return _tipo;
	}
	return NULL;
}
void Agujero::reposition()
{
	agujero->setPosition(Xx, diferenceY-30);
	plataforma1->setPosition(Xx - 110, diferenceY + 59);
	plataforma2->setPosition(Xx + 110, diferenceY + 59);
}