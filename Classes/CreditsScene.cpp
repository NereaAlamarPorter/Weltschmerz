#include "MainMenuScene.h"
#include "CreditsScene.h"

USING_NS_CC;

Scene* Credits::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Credits::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Credits::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	bg = Sprite::create("images/MainMenu/fondo.png");
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	bg->setScale(2.0f);

	auto b = Sprite::create("images/provisional/MainMenu/creditosbg.png");
	b->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(b, 1);

	// Creating menu
	auto menuItem = MenuItemImage::create("images/MainMenu/menunopulsado.png", "images/MainMenu/menupulsado.png", 
		CC_CALLBACK_1(Credits::goToMainMenuScene, this));
	
	auto menu = Menu::create(menuItem, NULL);
	//menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
	menu->setPosition(visibleSize.width - 300, 120);

	addChild(bg, 0);
	addChild(menu, 1);

	return true;
}

void Credits::goToMainMenuScene(Ref *pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
}

