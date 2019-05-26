#include "MainMenuScene.h"
#include "GameLvl1Scene.h"
#include "GameLimboScene.h"
#include "CreditsScene.h"
#include "OptionsScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	bg = Sprite::create("images/MainMenu/fondo.png");
	bg->setPosition(visibleSize.width / 2, visibleSize.height/2);
	bg->setScale(2.0f);

	title = Sprite::create("images/MainMenu/titulo.png");
	title->setPosition(visibleSize.width / 2, visibleSize.height - 120);


	// Creating menu
	auto playItem = MenuItemImage::create("images/MainMenu/jugarnopulsado.png", "images/MainMenu/jugarpulsado.png", 
		CC_CALLBACK_1(MainMenu::goToGameScene, this));
	auto optionsItem = MenuItemImage::create("images/MainMenu/controlesnopulsado.png", "images/MainMenu/controlespulsado.png",
		CC_CALLBACK_1(MainMenu::goToOptionsScene, this));
	auto creditsItem = MenuItemImage::create("images/MainMenu/creditosnopulsado.png", "images/MainMenu/creditospulsado.png",
		CC_CALLBACK_1(MainMenu::goToCreditsScene, this));

	auto menu = Menu::create(playItem,optionsItem,creditsItem, NULL);
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 20);
	menu->setPositionY(visibleSize.height / 2 - 100);
	addChild(menu, 1);
	addChild(bg, 0);
	addChild(title, 1);

	/*
	//Movimiento	
	auto listenermove = EventListenerKeyboard::create();

	listenermove->onKeyPressed = CC_CALLBACK_2(MainMenu::onKeyPressed, this);
	listenermove->onKeyReleased = CC_CALLBACK_2(MainMenu::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenermove, this);
	*/


    return true;
}

void MainMenu::goToGameScene(Ref *pSender) 
{
	auto scene = GameLimboScene::createScene(0);//Siempre se empieza en el limbo, asi que se pasa 0
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
}
void MainMenu::goToCreditsScene(Ref *pSender)
{
	auto scene = Credits::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
}

void MainMenu::goToOptionsScene(Ref *pSender)
{
	auto scene = Options::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
}
/*
void MainMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event){
	switch (keyCode) {

	case EventKeyboard::KeyCode::KEY_SPACE:
		goToGameScene(this);
		break;

		//Botón Acción
	case EventKeyboard::KeyCode::KEY_X:
		goToGameLvl1Scene(this);

		break;
	}
}*/
