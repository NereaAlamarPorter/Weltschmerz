#include "Puerta.h"
#include "GameLvl1Scene.h"

USING_NS_CC;

Puerta::Puerta(cocos2d::Layer *layer, int X, int Y, int tipo)
{
	_tipo = tipo;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	diferenceY = Y;
	Xx = X;

	switch (tipo)
	{
	case 7:
		puerta = Sprite::create("images/Nivel1/cama.png");
		puerta->setScale(0.3f);
		_tipo = 1;
		disponible = false;
		break;

	default:

		puerta = Sprite::create("images/Limbo/puerta.png");
		puerta->setScaleX(0.4f);
		puerta->setScaleY(0.5f);

		break;
	}
	puerta->setPosition(Point(X, Y));
	//FISICAS
	auto body = PhysicsBody::createEdgeSegment(Point(puerta->getBoundingBox().size.width / -2, puerta->getBoundingBox().size.height / 2 - 5), Point(puerta->getBoundingBox().size.width / 2, puerta->getBoundingBox().size.height / 2 - 5));
	body->setDynamic(false);
	body->setContactTestBitmask(true);
	body->setTag(_puertag);
	body->setCategoryBitmask(true);
	puerta->setPhysicsBody(body);

	

	layer->addChild(puerta, 0);
}

void Puerta::setPosition(int X, int Y)
{
	puerta->setPosition(X, Y);
}

Vec2 Puerta::getPosition()
{
	return puerta->getPosition();
}

int Puerta::Action(int Rx, int Ry)
{
	if (puerta->getBoundingBox().containsPoint(Vec2(Rx, Ry)) && disponible == true)
	{
		return _tipo;
	}
	else return NULL;
}

void Puerta::changeDisponible(bool g)
{
	disponible = g;
	//if (disponible) puerta->setTexture(CCTextureCache::sharedTextureCache()->addImage("images/Limbo/puerta.png"));
	//else puerta->setTexture(CCTextureCache::sharedTextureCache()->addImage("images/Limbo/puertades.png"));
}

void Puerta::reposition()
{
	puerta->setPosition(Xx, diferenceY);
}
