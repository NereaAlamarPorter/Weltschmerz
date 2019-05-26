#include "GameLimboScene.h"
#include "MainMenuScene.h"
#include "GameLvl1Scene.h"

#include "HUD.h"
#include "Classes/Objetos/Rooney.h"
#include "Niveles\Limbo.h"
#include "Objetos\Puerta.h"
#include "Niveles/Nivel1.h"
#include "Enemigos\Fantasma.h"
#include "Classes/Objetos/Estrella.h"
#include "Objetos\Agujero.h"
#include "Classes/Enemigos/Monstruo.h"

/*
HAY QUE APRENDER A MANDAR ARGUMENTOS EN CREATESCENE
*/

USING_NS_CC;

Scene* GameLimboScene::createScene(float lvl)
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); //para ver los cuadrados rojitos

	// 'layer' is an autorelease object
	auto layer = GameLimboScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld()); //Físicas

	layer->nivel = lvl;

	// add layer as a child to scene
	scene->addChild(layer);

	//PARA QUE APAREZCA AL PRIMER TICK
	scene->getPhysicsWorld()->setAutoStep(false);	// aqui le decimos al motor de fisicas que nosotros nos encargamos de llamar a
	//su actualización
	scene->getPhysicsWorld()->step(1.0f);			// aqui le decimos cuando es la siguiente actualización
	scene->getPhysicsWorld()->setAutoStep(true);	// Aquí le decimos que se encargue el solito

	//scene->getChildren()->layer->nivel = level;	//otro intento

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameLimboScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	estrellas = 0;
	hud = new HUD(this);


	//Creando el Mundo
	lvl = new Limbo(this);
	_gravity = lvl->_gravity;
	colision = false;
	left = false;
	right = false;

	//Creando a Rooney
	rooney = new Rooney(this, lvl->jump, lvl->speed);
	posRY = lvl->rooneyOrigin.y;
	rooney->setPosition(lvl->rooneyOrigin.x, lvl->rooneyOrigin.y);

	//Movimiento	
	auto listenermove = EventListenerKeyboard::create();

	listenermove->onKeyPressed = CC_CALLBACK_2(GameLimboScene::onKeyPressed, this);
	listenermove->onKeyReleased = CC_CALLBACK_2(GameLimboScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenermove, this);

	//Actualizaciónes constantes
	this->scheduleUpdate();
	this->schedule(schedule_selector(GameLimboScene::UpdateTimer), 1.0f);

	return true;
}

void GameLimboScene::update(float dt)
{
	lvl->desactivePB(rooney->getPosition().y - rooney->rooney->getBoundingBox().size.height / 2 + 10);
	float j = posRY - rooney->moveRooney();
	if (j<5 && j>-5) j = 0;

	lvl->Jump(j); //Se calcula el movimiento de Rooney y en caso de que salte el mundo tambien se mueve
	lvl->left = left;
	lvl->right = right;

	//evitar cosos raros en las animaciones
	if (left != rooney->left || right != rooney->right)
	{
		rooney->left = left;
		rooney->right = right;
		if (left || right) rooney->move = true;
		rooney->changeAnimation();
	}

	//if (!colision)lvl->Move(rooney->_speed); //Se calcula el movimiento del mundo

	lvl->Move(rooney->_speed);
	rooney->refresh();
	rooney->Fall();

	posRY = rooney->getPosition().y;

	if (rooney->vidas == 0) goToMainMenuScene(this);
	if (rooney->_loseLive == true){
		lvl->reposition();
		rooney->_loseLive = false;
	}

	hud->update(rooney->vidas);
	if (hud->fin) goToMainMenuScene(this);

}

//FISICAS

void GameLimboScene::setPhysicsWorld(PhysicsWorld *world)
{
	mWorld = world;
	mWorld->setGravity(_gravity);
	//mWorld->setGravity(Vec2::ZERO);
}

void GameLimboScene::recolocarObjetos()
{
	rooney->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
}

void GameLimboScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event){
	switch (keyCode) {
		//MOVIMIENTO NORMAL
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		left = true;
		rooney->left = true;
		rooney->move = true;
		rooney->changeAnimation();
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		right = true;
		rooney->right = true;
		rooney->move = true;
		rooney->changeAnimation();
		break;

	case EventKeyboard::KeyCode::KEY_SPACE:
		rooney->Jump();
		lvl->jumping = true;
		break;

		//Botón Acción
	case EventKeyboard::KeyCode::KEY_X:
		if (rooney->_canJump){
			int tipoaccion = NULL;
			rooney->accion = true;
			tipoaccion = lvl->Action(rooney->getPosition());
			doAction(tipoaccion);
		}
		break;

		/*OTROS*/

		//IR AL MENU
	case EventKeyboard::KeyCode::KEY_Q:
		goToMainMenuScene(this);
		break;

		//RECOLOCARRONEY 
	case EventKeyboard::KeyCode::KEY_P:
		rooney->setCanJump(false);
		recolocarObjetos();
		break;
	}
}

void GameLimboScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event){
	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE){
		rooney->setJumping(false);
	}
	else if (EventKeyboard::KeyCode::KEY_LEFT_ARROW == keyCode) {
		left = false;
		rooney->left = false;
		if (!right)rooney->move = false;
		rooney->changeAnimation();
	}
	else if (EventKeyboard::KeyCode::KEY_RIGHT_ARROW == keyCode) {
		right = false;
		rooney->right = false;
		if (!left) rooney->move = false;
		rooney->changeAnimation();

	}
	else if (EventKeyboard::KeyCode::KEY_X == keyCode) {
		rooney->accion = false;
	}
}

void GameLimboScene::goToMainMenuScene(Ref *pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameLimboScene::goToLevel1(Ref *pSender)
{
	auto scene = GameLvl1Scene::createScene(1);
	Director::getInstance()->replaceScene(scene);
}

void GameLimboScene::changeLevel(int i)
{
	switch (i)
	{
	case 0:
		//goToLimbo(this);
		//rooney->vidas = 0;
		break;
	case 1:
		goToLevel1(this);
		break;
	case 2:
		//goToLevel2(this);
		break;
	case 3:
		//goToLevel3(this);
		break;
	case 4:
		//goToLevel4(this);
		break;
	case 5:
		//goToLevel5(this);
		break;
	case 6:
		//goToLevel6(this);
		break;
	}
}

void GameLimboScene::UpdateTimer(float dt)
{
	hud->UpdateTimer();
}

void GameLimboScene::doAction(int tipo)
{
	switch (tipo){
	case 0:
		changeLevel(0);
		break;

	case 1: //Es el nivel 1
		changeLevel(1);
		break;

	case 2: //Es el nivel 1
		changeLevel(2);
		break;

	case 11: //Interruptor
		//rooney->changeOpacity(100);
		break;

	case 12: //Fantasma
		rooney->loseLive();
		lvl->reposition();
		break;

	case 13: //Agujero /*ES UN POCO ESTUPIDO TENER CASES QUE HAGAN LO MISMO, SE PODRIAN SIMPLIFICAR EN UN CASE PARA ENEMIGOS Y PUNTO*/
		rooney->loseLive();
		lvl->reposition();
		break;

	default:
		break;
	}
}