#ifndef __GAME_LVL1_SCENE_H__
#define __GAME_LVL1_SCENE_H__

#include "HUD.h"
#include "cocos2d.h"
#include "Classes/Objetos/Rooney.h"
#include "Classes/Objetos/Plataforma.h"
#include "Niveles\Limbo.h"
#include "Objetos\Puerta.h"
#include "Niveles\Nivel1.h"
#include "Enemigos\Fantasma.h"
#include "Classes/Objetos/Estrella.h"
#include "Objetos\Agujero.h"

USING_NS_CC;

class GameLvl1Scene : public cocos2d::Layer
{
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	Vec2 _gravity;
	
	//Fisicas
	PhysicsWorld *mWorld;

public:
	static cocos2d::Scene* createScene(float level);
	virtual bool init();

	bool left;
	bool right;
	bool colision;

	//NIVELES
	//float nivel=NULL;
	float nivel;

	//Limbo* lvl;
	Nivel1* lvl;

	//VARIABLES PROPIAS
	float posRY;

	HUD* hud;

	int estrellas;
	

	//ACTORES
	Rooney * rooney;

	//FUNCIONES

	//Utiles
	void GameLvl1Scene::goToMainMenuScene(Ref *pSender);
	void GameLvl1Scene::goToLimbo(Ref *pSender);

	//Movimiento Rooney
	void update(float dt);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	void changeLevel(int i);

	void GameLvl1Scene::UpdateTimer(float dt);

	//Fisicas
	
	void setPhysicsWorld(PhysicsWorld *world);
	bool GameLvl1Scene::onContactBegin(const PhysicsContact& contact);
	bool GameLvl1Scene::onContactSeparate(const PhysicsContact& contact);

	void recolocarObjetos();
	void doAction(int tipo);

	// implement the "static create()" method manually
	CREATE_FUNC(GameLvl1Scene);
};

#endif // __GAME_SCENE_H__
