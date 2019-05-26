#include "HUD.h"

USING_NS_CC;

HUD::HUD(cocos2d::Layer *layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();

	hud = Sprite::create("images/hud.jpg");
	hud->setPosition(visibleSize.width / 2, visibleSize.height - 20);
	hud->setScaleX(1.4f);

	fin = false;
	estrellas = 0;
	layer->addChild(hud, 10);
	
	//Tiempo
	auto  *text = __String::createWithFormat("Tiempo: %.0f  ", tiempo);
	_labelTiempo = Label::createWithTTF(text->getCString(), "fonts/MArker Felt.ttf", 24);
	_labelTiempo->setPosition(Vec2(visibleSize.width - 150, visibleSize.height - 30));
	_labelTiempo->setColor(Color3B::WHITE);
	layer->addChild(_labelTiempo, 11);

	//Vidas 
	text = __String::createWithFormat("Vidas: %d", vidas);
	_labelVidas = Label::createWithTTF(text->getCString(), "fonts/MArker Felt.ttf", 24);
	_labelVidas->setPosition(Vec2(150, visibleSize.height - 30));
	_labelVidas->setColor(Color3B::WHITE);
	layer->addChild(_labelVidas, 11);

	//Estrellas
	auto  *textn = __String::createWithFormat("Estrellas: %f ", estrellas);
	_labeln = Label::createWithTTF(textn->getCString(), "fonts/MArker Felt.ttf", 24);
	_labeln->setPosition(Vec2(visibleSize.width/2, visibleSize.height - 30));
	_labeln->setColor(Color3B::WHITE);
	layer->addChild(_labeln, 11);
}

void HUD::update(int vida)
{
	vidas = vida;
	//Vidas
	auto *text = __String::createWithFormat("Vidas: %d", vidas);
	_labelVidas->setString(text->getCString());

	//Tiempo
	if (tiempo > maxtiempo + 1) fin = true;
	if (tiempo > maxtiempo){
		auto *text = __String::createWithFormat("THE GAME IT'S OVER");
		_labelTiempo->setString(text->getCString());
	}
	else {
		auto *text = __String::createWithFormat("Tiempo: %.0f ", tiempo);
		_labelTiempo->setString(text->getCString());
	}

	//Estrellas
	auto *textq = __String::createWithFormat("Estrellas: %d ", estrellas);
	_labeln->setString(textq->getCString());

}
void HUD::UpdateTimer()
{
	tiempo++;
}


void HUD::getVidas(int v)
{
	vidas = v;
}
void HUD::changeEstrellas()
{
	estrellas++;
}
