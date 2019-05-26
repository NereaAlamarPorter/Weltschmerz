#include "Classes/Objetos/Estrella.h"
#include "GameLvl1Scene.h"

USING_NS_CC;

Estrella::Estrella(cocos2d::Layer *layer, int X, int Y)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	auto s=0.2f;
	_tipo = 5;

	//interruptor desactivado (luz encendida)
	visible = false;
	estrella = Sprite::create("images/estrella.png");
	estrella->setScale(s);
	estrella->setPosition(Point(X, Y));
	estrella->setVisible(visible);
	diferenceY = Y;
	Xx = X;

	layer->addChild(estrella, 4);
}

void Estrella::setPosition(float X, float Y)
{
	estrella->setPosition(X, Y);
}

Vec2 Estrella::getPosition()
{
	return estrella->getPosition();
}

void Estrella::coger(){
	if (visible){
		if (existe){
			existe = false;
		}
		aparecer();
	}
	

}

void Estrella::aparecer(){
	if (existe == true && !visible){
		visible = true;
	}
	else visible = false;
	estrella->setVisible(visible);
}


int Estrella::Action(float Rx, float Ry)
{
	auto pos = Vec2(Rx, Ry);

	if (this->estrella->getBoundingBox().containsPoint(pos) && existe && visible){
		coger();
		return 7;
	}
	return NULL;
}

void Estrella::reposition()
{
	estrella->setPosition(Xx, diferenceY);
}