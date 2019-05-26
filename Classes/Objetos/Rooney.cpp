#include "Rooney.h"

USING_NS_CC;

Rooney::Rooney(cocos2d::Layer *layer, int JumpForce,int SpeedForce)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	//Inicializando variables propias
	JUMP = JumpForce;
	__jump = JUMP;
	SPEED = SpeedForce;
	_speed = SPEED;
	_canJump = false;
	_isJumping = false;
	right = false;
	left = false;
	_isFalling = false;
	vidas = 3;
	accion = false; //A actuado
	_loseLive = false; //A perdido hace poco na vida?
	move = false;
	

	// APARTADO VISUAL
	
	//referencia principal
	rooney = Sprite::create("images/Rooney/Static/rooney_static_000.png");
	rooney->setScale(0.8f);
	rooney->setOpacity(00);

	//animacion estatica
	rooneyS = Sprite::create("images/Rooney/Static/rooney_static_000.png");
	rooneyS->setPosition(rooney->getPosition());
	Vector<SpriteFrame*> animframes(20);
	char str[100] = { 0 };
	for (int i = 0; i < 20; i++)
	{
		sprintf(str, "images/Rooney/Static/rooney_static_%03d.png", i);
		animframes.pushBack(SpriteFrame::create(str, 
			Rect(rooney->getPosition(), rooneyS->getBoundingBox().size)));		
	}
	Animation* animation = Animation::createWithSpriteFrames(animframes, (0.05f));
	Animate* animateStatic = Animate::create(animation);
	rooneyS->runAction(RepeatForever::create(animateStatic));
	rooneyS->setScale(0.8f);
	rooneyS->setVisible(false);

	//animacion caminar
	rooneyW = Sprite::create("images/Rooney/Walk/rooney_walk_000.png");
	rooneyW->setPosition(rooney->getPosition());
	animframes.clear();
	for (int i = 0; i < 20; i++)
	{
		sprintf(str, "images/Rooney/Walk/rooney_walk_%03d.png", i);
		animframes.pushBack(SpriteFrame::create(str,
			Rect(rooney->getPosition(), rooneyW->getBoundingBox().size)));
	}
	animation = Animation::createWithSpriteFrames(animframes, (0.05f));
	Animate* animateWalk = Animate::create(animation);
	rooneyW->runAction(RepeatForever::create(animateWalk));
	rooneyW->setScale(0.8f);
	rooneyW->setVisible(false);

	//animacion saltar
	rooneyJ = Sprite::create("images/Rooney/Jump/rooney_jump_000.png");
	rooneyJ->setPosition(rooney->getPosition());
	animframes.clear();
	for (int i = 0; i < 20; i++)
	{
		sprintf(str, "images/Rooney/Jump/rooney_jump_%03d.png", i);
		animframes.pushBack(SpriteFrame::create(str,
			Rect(rooney->getPosition(), rooneyJ->getBoundingBox().size)));
	}
	animation = Animation::createWithSpriteFrames(animframes, (0.05f));
	Animate* animateJump = Animate::create(animation);
	rooneyJ->runAction(RepeatForever::create(animateJump));
	rooneyJ->setScale(0.8f);
	rooneyJ->setVisible(false);


	//animacion caer
	rooneyF = Sprite::create("images/Rooney/Fall/rooney_fall_000.png");
	rooneyF->setPosition(rooney->getPosition());
	animframes.clear();
	for (int i = 0; i < 20; i++)
	{
		sprintf(str, "images/Rooney/Fall/rooney_fall_%03d.png", i);
		animframes.pushBack(SpriteFrame::create(str,
			Rect(rooney->getPosition(), rooneyF->getBoundingBox().size)));
	}
	animation = Animation::createWithSpriteFrames(animframes, (0.05f));
	Animate* animateFall = Animate::create(animation);
	rooneyF->runAction(RepeatForever::create(animateFall));
	rooneyF->setScale(0.8f);
	rooneyF->setVisible(false);

	changeAnimation();
	

	//FISICAS

	auto physicsBody = PhysicsBody::createBox(Size(rooney->getBoundingBox().size.width-45, rooney->getBoundingBox().size.height-5), 
		PhysicsMaterial(1.0f,0.0f,0.0f));
	physicsBody->setDynamic(true);
	physicsBody->setRotationEnable(false);
	physicsBody->setContactTestBitmask(true);
	physicsBody->setCollisionBitmask(true);
	physicsBody->setTag(_rooneytag); //Para el futuro
	rooney->setPhysicsBody(physicsBody);

	layer->addChild(rooney, 5);
	layer->addChild(rooneyW, 5);
	layer->addChild(rooneyS, 5);
	layer->addChild(rooneyJ, 5);
	layer->addChild(rooneyF, 5);
}

float Rooney::moveRooney()
{
	Vec2 newPos = Vec2(visibleSize.width/2, rooney->getPosition().y);
	rooney->setPosition(newPos);
	float j = rooney->getPosition().y;
	if (_isJumping){
		_canJump = false;
		Vec2 newPos = Vec2(rooney->getPosition().x, rooney->getPosition().y + __jump/2);
		rooney->setPosition(newPos);

		_contJump++;
		if (__jump - _contJump >=0) __jump-=_contJump;
		if (_contJump >= 8){
			_isJumping = false;
			_isFalling = true;
			changeAnimation();
		}
	}
	if (rooney->getPhysicsBody()->getVelocity().y <= 0)
	{
		_canJump = false;
		_isFalling = true;
		changeAnimation();
	}
	if (rooney->getPhysicsBody()->getVelocity().y > 0)rooney->getPhysicsBody()->setVelocity(Vec2(0.0, 0.0));

	if (rooney->getPhysicsBody()->getVelocity().y < 0.5 &&rooney->getPhysicsBody()->getVelocity().y > -0.5){
		_canJump = true; //cuando no baja (ha tocado solido) puede saltar
		_isFalling = false;
		changeAnimation();
	}
	//Actualizaciones
	return rooney->getPosition().y;
}

void Rooney::setPosition(int X, int Y)
{
	rooney->setPosition(X,Y);
}

void Rooney::refresh()
{
	auto jig = rooney->getPosition();
	rooneyW->setPosition(jig);
	rooneyS->setPosition(jig);
	rooneyJ->setPosition(jig);
	rooneyF->setPosition(jig);
}

Vec2 Rooney::getPosition()
{
	return rooney->getPosition();
}

bool Rooney::getCanJump()
{
	return _canJump;
}

void Rooney::setCanJump(bool p)
{
	_canJump = p;
}

void Rooney::setJumping(bool p)
{
	_canJump = p;
}

void Rooney::Jump()
{
	if (_canJump){
		_isJumping = true;
		_contJump = 0;
		__jump = JUMP;
		changeAnimation();
	}
	
}

void Rooney::changeOpacity(int i)
{
	if (rooney->getOpacity()==i)rooney->setOpacity(255);
	else rooney->setOpacity(100);
}

void Rooney::Fall()
{
	float v = rooney->getPhysicsBody()->getVelocity().y;
	if (v < -1100)
	{
		loseLive();
		rooney->getPhysicsBody()->setVelocity(Vec2(0,-200));
	}
}

void Rooney::changeAnimation()
{
	if (move)
	{
		rooneyW->setVisible(true);
		rooneyS->setVisible(false);
		rooneyJ->setVisible(false);
		rooneyF->setVisible(false);
		
	}
	else
	{
		rooneyW->setVisible(false);
		rooneyS->setVisible(true);
		rooneyJ->setVisible(false);
		rooneyF->setVisible(false);
	}
	if (_isJumping)
	{
		rooneyW->setVisible(false);
		rooneyS->setVisible(false);
		rooneyJ->setVisible(true);
		rooneyF->setVisible(false);
	}
	if (_isFalling)
	{
		rooneyW->setVisible(false);
		rooneyS->setVisible(false);
		rooneyJ->setVisible(false);
		rooneyF->setVisible(true);
	}

	if (right)
	{
		rooney->setFlipX(false);
		rooneyS->setFlipX(false);
		rooneyW->setFlipX(false);
		rooneyJ->setFlipX(false);
		rooneyF->setFlipX(false);
	}
	else if (left)
	{
		rooney->setFlipX(true);
		rooneyS->setFlipX(true);
		rooneyW->setFlipX(true);
		rooneyJ->setFlipX(true);
		rooneyF->setFlipX(true);
	}
}

void Rooney::loseLive()
{
	if (!_loseLive){
		_loseLive = true;
		vidas--;
	}
}