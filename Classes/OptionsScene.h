#ifndef __OPTIONS_SCENE_H__
#define __OPTIONS_SCENE_H__

#include "cocos2d.h"

class Options : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	Sprite* bg;
	void goToMainMenuScene(Ref *pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Options);
};

#endif