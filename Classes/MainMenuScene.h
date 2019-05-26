#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MainMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	Sprite* bg;
	Sprite* title;

	void goToGameScene(Ref *pSender);
	void goToCreditsScene(Ref *pSender);
	void goToOptionsScene(Ref *pSender);
	/*
	void MainMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event *event);
	void MainMenu::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *event);
    */
    // implement the "static create()" method manually
	CREATE_FUNC(MainMenu);
};

#endif // __MAINMENU_SCENE_H__
