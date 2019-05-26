#include "GameLvl1Scene.h"
#include "GameLimboScene.h"
#include "MainMenuScene.h"
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

Scene* GameLvl1Scene::createScene(float lvl)
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); //para ver los cuadrados rojitos

	// 'layer' is an autorelease object
	auto layer = GameLvl1Scene::create();
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
bool GameLvl1Scene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	hud = new HUD(this);
	estrellas = 0;

	//Creando el Mundo
	lvl= new Nivel1(this);
	//lvl = new Limbo(this);
	_gravity = lvl->_gravity;
	colision = false;
	left = false;
	right = false;
	
	//Creando a Rooney
	rooney = new Rooney(this, lvl->jump,lvl->speed);
	posRY = lvl->rooneyOrigin.y;
	rooney->setPosition(lvl->rooneyOrigin.x, lvl->rooneyOrigin.y);

	//Movimiento	
	auto listenermove = EventListenerKeyboard::create();

	listenermove->onKeyPressed = CC_CALLBACK_2(GameLvl1Scene::onKeyPressed, this);
	listenermove->onKeyReleased = CC_CALLBACK_2(GameLvl1Scene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenermove, this);
	/*
	//Contacto
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLvl1Scene::onContactBegin, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	*/
	/*auto descontactListener = EventListenerPhysicsContact::create();
	descontactListener->onContactSeparate = CC_CALLBACK_1(GameLvl1Scene::onContactSeparate, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(descontactListener, this);
	*/

	//Actualizaciónes constantes
	this->scheduleUpdate();
	this->schedule(schedule_selector(GameLvl1Scene::UpdateTimer), 1.0f);

	return true;
}

bool GameLvl1Scene::onContactSeparate(const PhysicsContact& contact)
{
	colision = false;
	return true;
}


bool GameLvl1Scene::onContactBegin(const PhysicsContact& contact)
{
	/*
	A VER...
	YA DETECTA COLISIONES PERO SI SE APRETA UNA SEGUNDA VEZ NO FUNCIONA BIEN...Y MAS COSAS
	*/

	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

	if (spriteA->getName().compare("rooney") && spriteB->getName().compare("solido"))
	{
		CCLOG("Rooney contacta con un solido");
		//colision = true;
		if (spriteA->getPositionX() > spriteB->getPositionX() && spriteA->getPositionY() < spriteB->getPositionY())
		{
			CCLOG("Rooney mas a la izquierda");
			
			left = false;
		}
		else {
			right = false;
		}
	}

	return true;
}


void GameLvl1Scene::update(float dt)
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
		if (left || right) rooney->move=true;
		rooney->changeAnimation();
	}

	//if (!colision)lvl->Move(rooney->_speed); //Se calcula el movimiento del mundo

	lvl->Move(rooney->_speed);
	rooney->refresh();
	rooney->Fall();

	posRY = rooney->getPosition().y;

	doAction(lvl->ActionIA(rooney->getPosition()));
	if (rooney->vidas == 0) goToMainMenuScene(this);
	if (rooney->_loseLive ==true){
		lvl->reposition();
		rooney->_loseLive = false;
	}

	hud->update(rooney->vidas);
	if (hud->fin) goToMainMenuScene(this);

}

//FISICAS

void GameLvl1Scene::setPhysicsWorld(PhysicsWorld *world)
{
	mWorld = world;
	mWorld->setGravity(_gravity);
}

void GameLvl1Scene::recolocarObjetos()
{
	rooney->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 +origin.y);
}

void GameLvl1Scene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event){
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
			int tipoaccion=NULL;
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

void GameLvl1Scene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event){
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

void GameLvl1Scene::goToMainMenuScene(Ref *pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameLvl1Scene::goToLimbo(Ref *pSender)
{
	auto scene = GameLimboScene::createScene(1);
	Director::getInstance()->replaceScene(scene);
}

void GameLvl1Scene::changeLevel(int i)
{
	auto scene = GameLimboScene::createScene(1);
	Director::getInstance()->replaceScene(scene);
}

void GameLvl1Scene::UpdateTimer(float dt)
{
	hud->UpdateTimer();
	lvl->perSecond();
}

void GameLvl1Scene::doAction(int tipo)
{
	switch (tipo){
	case 0:
		break;
	case 1: //Es el nivel 1
		changeLevel(1);
		break;
	
	case 7: //Estrellas
		//estrellas++;
		hud->changeEstrellas();
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