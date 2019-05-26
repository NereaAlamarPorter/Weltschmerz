#ifndef __GAME_LIMBO_SCENE_H__
#define __GAME_LIMBO_SCENE_H__


#include "cocos2d.h"
#include "Classes/Objetos/Rooney.h"
#include "Classes/Objetos/Plataforma.h"

#include "HUD.h"
#include "Niveles\Limbo.h"
#include "Objetos\Puerta.h"
#include "Niveles\Nivel1.h"
#include "Enemigos\Fantasma.h"
#include "Classes/Objetos/Estrella.h"
#include "Objetos\Agujero.h"

USING_NS_CC;

class GameLimboScene : public cocos2d::Layer
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

	int estrellas;
	bool left;
	bool right;
	bool colision;

	//NIVELES
	//float nivel=NULL;
	float nivel;

	Limbo* lvl;

	//VARIABLES PROPIAS
	float posRY;


	//ACTORES
	Rooney * rooney;

	HUD* hud;

	//FUNCIONES

	//Utiles
	void GameLimboScene::goToMainMenuScene(Ref *pSender);
	void GameLimboScene::goToLevel1(Ref *pSender);

	//Movimiento Rooney
	void update(float dt);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
	void changeLevel(int i);

	void GameLimboScene::UpdateTimer(float dt);

	//Fisicas

	void setPhysicsWorld(PhysicsWorld *world);
	bool GameLimboScene::onContactBegin(const PhysicsContact& contact);
	bool GameLimboScene::onContactSeparate(const PhysicsContact& contact);

	void recolocarObjetos();
	void doAction(int tipo);

	// implement the "static create()" method manually
	CREATE_FUNC(GameLimboScene);
};

#endif // __GAME_SCENE_H__
