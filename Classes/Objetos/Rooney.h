#ifndef __ROONEY_H__
#define __ROONEY_H__

#include "cocos2d.h"

USING_NS_CC;

const int _rooneytag = 0;

//const String _rooneyname = "rooney";

class Rooney : public cocos2d::Layer
{

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	//Salto
	int JUMP;
	int SPEED;
	int _contJump;
	
public:
	Rooney(cocos2d::Layer *layer, int JumpForce, int SpeedForce);

	cocos2d::Sprite *rooney;
	cocos2d::Sprite *rooneyS;
	cocos2d::Sprite *rooneyW;
	cocos2d::Sprite *rooneyJ;
	cocos2d::Sprite *rooneyF;

	Vector<SpriteFrame*> animframes();
	Animation* animation;
	Animate* animateStatic;
	Animate* animateWalk;
	Animate* animateJump;
	Animate* animateFall;
	
	bool left;
	bool right;
	bool move;

	int _speed;
	int __jump;
	bool _canJump;
	bool _isJumping;
	bool _isFalling;
	int vidas;
	bool accion;

	//Vidas
	bool _loseLive; //true si puede perder vidas false si no

	//My functions
	
	float moveRooney();

	void Rooney::setPosition(int X, int Y);
	Vec2 Rooney::getPosition();

	//Salto
	bool Rooney::getCanJump();
	void Rooney::setCanJump(bool p);
	void Rooney::Jump();
	void Rooney::setJumping(bool p);
	void Rooney::changeOpacity(int i);
	void Rooney::Fall();
	void Rooney::changeAnimation();
	void Rooney::loseLive();
	void Rooney::refresh();

};

#endif
