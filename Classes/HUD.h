#ifndef __HUD_H__
#define __HUD_H__

#include "cocos2d.h"

USING_NS_CC;

class HUD : public cocos2d::Layer
{
private:
	cocos2d::Size visibleSize;

public:
	HUD::HUD(cocos2d::Layer* layer);

	int estrellas;
	int vidas;

	Sprite* hud;

	//tiempo
	float tiempo = 0;
	float maxtiempo = 100;
	Label *_labelTiempo;
	Label *_labeln;
	Label *_labelVidas;
	bool fin;

	//FUNCIONES
	//Movimiento Rooney
	
	void update(int vidas);
	void HUD::UpdateTimer();
	void getVidas(int v);
	void changeEstrellas();
	
};

#endif 