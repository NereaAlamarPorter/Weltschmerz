#ifndef __CREDITS_SCENE_H__
#define __CREDITS_SCENE_H__

#include "cocos2d.h"

class Credits : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	Sprite* bg;
	void goToGameLvl1Scene(Ref *pSender);
	void goToMainMenuScene(Ref *pSender);
	void goToOptionsScene(Ref *pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Credits);
};

#endif