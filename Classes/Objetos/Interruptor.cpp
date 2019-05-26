#include "Classes/Objetos/Interruptor.h"
#include "GameLvl1Scene.h"

USING_NS_CC;

Interruptor::Interruptor(cocos2d::Layer *layer, int X, int Y)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	auto s=0.38f;
	_tipo = 11;

	//interruptor desactivado (luz encendida)
	interruptor1 = Sprite::create("images/Nivel1/interruptor/encendido.png");
	interruptor1->setScale(s);
	interruptor1->setPosition(Point(X, Y));
	//interruptor1->setVisible(true);
	diferenceY = Y;
	Xx = X;

	//interruptor activado (luz apagada)
	interruptor2 = Sprite::create("images/Nivel1/interruptor/apagadoHalo.png");
	interruptor2->setScale(s);
	interruptor2->setPosition(Point(X, Y));
	interruptor2->setVisible(false);	

	layer->addChild(interruptor1, 0);
	layer->addChild(interruptor2, 4);
}

void Interruptor::setPosition(float X, float Y)
{
	interruptor1->setPosition(X, Y);
	interruptor2->setPosition(X, Y);
}

Vec2 Interruptor::getPosition()
{
	return interruptor1->getPosition();
}

void Interruptor::encender(){

	if (activado == false)
	{
		activado = true;
		interruptor2->setVisible(true);
	}
	else
	{
		activado = false;
		interruptor2->setVisible(false);
	}
}

int Interruptor::Action(float Rx, float Ry)
{
	auto pos = Vec2(Rx, Ry);

	if (this->interruptor1->getBoundingBox().containsPoint(pos)){
		encender();
		return _tipo;
	}
	else return NULL;
	return 0;

}

void Interruptor::changeDisp(bool estado)
{
	activado = estado;
	//interruptor1->setVisible(!estado);
	interruptor2->setVisible(estado);
}

void Interruptor::reposition()
{
	interruptor1->setPosition(Xx, diferenceY);
	interruptor2->setPosition(Xx, diferenceY);
}
