#include "Limbo.h"
#include "GameLvl1Scene.h"
#include "Objetos\Plataforma.h"
#include "Objetos\Puerta.h"

USING_NS_CC;

Limbo::Limbo(cocos2d::Layer *layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	background = Sprite::create("images/Limbo/fondo2.png");
	background->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2));
	background->setScale(2.0); //Hay que escalarlo bien 
	layer->addChild(background, 0);

	rooneyOrigin = Vec2(visibleSize.width / 2 + origin.x,175);

	

	plvl1 = new Puerta(layer, visibleSize.width * 3/2 - 200, 280, 1);
	plvl3 = new Puerta(layer, visibleSize.width * 3 / 2 + 200, 280, 3);
	plvl5 = new Puerta(layer, visibleSize.width * 3 / 2 + 600, 280, 5);
	plvl2 = new Puerta(layer, visibleSize.width * 3 / 2 - 200, visibleSize.height * 4 / 5 + 20 + 300, 2);
	plvl4 = new Puerta(layer, visibleSize.width * 3 / 2 + 200, visibleSize.height * 4 / 5 + 20 + 300, 4);
	plvl6 = new Puerta(layer, visibleSize.width * 3 / 2 + 600, visibleSize.height * 4 / 5 + 20 + 300, 6);

	plataforma = new Plataforma(layer, visibleSize.width * 3 / 2 + 200, visibleSize.height * 4 / 5 + 20, 3);
	suelo = new Plataforma(layer, 0, 0, 2);
	
	plvl1->changeDisponible(true);
	plvl2->changeDisponible(false);
	plvl3->changeDisponible(false);
	plvl4->changeDisponible(false);
	plvl5->changeDisponible(false);
	plvl6->changeDisponible(false);


	prts[0] = plvl1;
	prts[1] = plvl2;
	prts[2] = plvl3;
	prts[3] = plvl4;
	prts[4] = plvl5;
	prts[5] = plvl6;
}

void Limbo::Move(int speed)
{
	if (right)
	{
		plataforma->setPosition(plataforma->getPosition().x - speed, plataforma->getPosition().y);
		for (int i = 0; i < prtsN; i++)
		{
			prts[i]->setPosition(prts[i]->getPosition().x - speed, prts[i]->getPosition().y);
		}
	}
	else if (left)
	{
		plataforma->setPosition(plataforma->getPosition().x + speed, plataforma->getPosition().y);

		for (int i = 0; i < prtsN; i++)
		{
			prts[i]->setPosition(prts[i]->getPosition().x + speed, prts[i]->getPosition().y);
		}
	}
}

void Limbo::Jump(float jump)
{
	suelo->setPosition(suelo->getPosition().x, suelo->getPosition().y + jump);
	int sY = suelo->getPosition().y;

	for (int i = 0; i < prtsN; i++)
	{
		prts[i]->setPosition(prts[i]->getPosition().x, sY + prts[i]->diferenceY);
	}
	plataforma->setPosition(plataforma->getPosition().x, sY + plataforma->diferenceY);
	background->setPosition(background->getPosition().x, sY + background->getBoundingBox().size.height / 2);
}

int Limbo::Action(Vec2 pos)
{
	int tipo;
	for (int i = 0; i < prtsN; i++)
	{
		tipo = prts[i]->Action(pos.x,pos.y);
		if (tipo != NULL) return tipo;
	}
	return tipo;
}

void Limbo::desactivePB(float pos)
{
	for (int i = 0; i < prtsN; i++)
	{
		if (prts[i]->getPosition().y > pos){ prts[i]->puerta->getPhysicsBody()->setEnable(false); }
		else prts[i]->puerta->getPhysicsBody()->setEnable(true);

	}
	if (plataforma->getPosition().y > pos){ plataforma->plataforma->getPhysicsBody()->setEnable(false); }
	else plataforma->plataforma->getPhysicsBody()->setEnable(true);
}

void Limbo::reposition() 
{
	suelo->setPosition(visibleSize.width / 2, 0);
	int sY = suelo->getPosition().y;
	plataforma->reposition();
	for (int a = 0; a < prtsN; a++)
	{
		prts[a]->reposition();
	}
}