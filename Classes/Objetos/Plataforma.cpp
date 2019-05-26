#include "Classes/Objetos/Plataforma.h"
#include "GameLvl1Scene.h"

USING_NS_CC;

Plataforma::Plataforma(cocos2d::Layer *layer, int X, int Y, int tipo)
{

	_tipo = tipo;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	auto taag = _ptag;
	switch (_tipo)
	{
	case 0: //Suelo
		plataforma = Sprite::create("images/provisional/suelo.jpg");
		plataforma->setScaleX(1.5f);
		plataforma->setPosition(Point(plataforma->getBoundingBox().size.width/2,0));
		break;
	case 1: //cuadro
		plataforma = Sprite::create("images/Nivel1/cuadros/Cuadro0.png");
		plataforma->setPosition(Point(X, Y));
		plataforma->setScale(0.4f);
		break;
	case 2: //suelo limbo
		plataforma = Sprite::create("images/Limbo/suelo.png");
		plataforma->setScaleX(1.2f);
		plataforma->setPosition(Point(plataforma->getBoundingBox().size.width / 2, 0));
		break;
	case 3: //plataforma limbo
		plataforma = Sprite::create("images/Limbo/plataforma.png");
		plataforma->setPosition(Point(X, Y));
		plataforma->setScaleX(1.3f);
		break;
	case 4: //lampara
		plataforma = Sprite::create("images/Nivel1/lampara.png");
		plataforma->setPosition(Point(X, Y));
		plataforma->setScale(0.4f);
		break;
	case 5: //Caja de derivacion
		plataforma = Sprite::create("images/Nivel1/cdd.png");
		plataforma->setPosition(Point(X, Y));
		plataforma->setScale(0.3f);
		break;
	case 6: //Ventilacion
		plataforma = Sprite::create("images/Nivel1/ventilacion.png");
		plataforma->setPosition(Point(X, Y));
		plataforma->setScale(0.3f);
		break;
	case 7: //Paredes
		plataforma = Sprite::create("images/provisional/pared.png");
		plataforma->setPosition(Point(X, Y));
		//plataforma->setScale(0.5f);
		taag = 100;
		break;
	case 8: //Barandilla
		plataforma = Sprite::create("images/Nivel1/paloescalera.png");
		plataforma->setPosition(Point(X, Y));
		plataforma->setScale(0.3f);
		taag = 100;
		break;
	case 9: //Ventana b
		plataforma = Sprite::create("images/Nivel1/ventana.png");
		plataforma->setPosition(Point(X, Y));
		plataforma->setScale(0.5f);
		
		break;
	case 10: //baul
		plataforma = Sprite::create("images/Nivel1/baul.png");
		plataforma->setPosition(Point(X, Y));
		plataforma->setScale(0.3f);

		break;

	case 11: //repisa
		plataforma = Sprite::create("images/Nivel1/repisalibros.png");
		plataforma->setPosition(Point(X, Y));
		plataforma->setScale(0.3f);

		break;
	case 12: //repisa
		plataforma = Sprite::create("images/Nivel1/repisaoso.png");
		plataforma->setPosition(Point(X, Y));
		plataforma->setScale(0.3f);

		break;

	case 13: //tablon
		plataforma = Sprite::create("images/Nivel1/tablon.png");
		plataforma->setPosition(Point(X, Y));
		plataforma->setScale(0.5f);
		break;

	case 14: //mesa
		plataforma = Sprite::create("images/Nivel1/mesa.png");
		plataforma->setPosition(Point(X, Y));
		plataforma->setScale(0.5f);
		break;

	case 15: //tablon
		plataforma = Sprite::create("images/Nivel1/pantalla.png");
		plataforma->setPosition(Point(X, Y));
		plataforma->setScale(0.5f);
		break;
	case 16: //tore
		plataforma = Sprite::create("images/Nivel1/torre.png");
		plataforma->setPosition(Point(X, Y));
		plataforma->setScale(0.5f);
		break;

	case 17: //lamaprah
		plataforma = Sprite::create("images/Nivel1/lamparah.png");
		plataforma->setPosition(Point(X, Y));
		plataforma->setScale(0.6f);

		break;
	case 18: //suelo lvl1
		plataforma = Sprite::create("images/Nivel1/suelo.png");
		plataforma->setScaleX(1.2f);
		plataforma->setPosition(Point(plataforma->getBoundingBox().size.width / 2, 0));
		break;
	case 19: 
		plataforma = Sprite::create("images/Nivel1/armariowc.png");
		plataforma->setScale(0.4f);
		plataforma->setPosition(Point(X, Y));
		break;

	case 20: //wca
		plataforma = Sprite::create("images/Nivel1/wcarriba.png");
		plataforma->setPosition(Point(X, Y));
		plataforma->setScale(0.35f);
		break;

	case 21: //wcb
		plataforma = Sprite::create("images/Nivel1/wcabajo.png");
		plataforma->setPosition(Point(X, Y));
		plataforma->setScale(0.35f);
		break;
	case 22: //armario
		plataforma = Sprite::create("images/Nivel1/monstruoarmario.png");
		plataforma->setPosition(Point(X, Y));
		plataforma->setScale(0.6f);
		break;
	}
	diferenceY = Y;
	Xx = X;

	//FISICAS
	auto body = PhysicsBody::createBox(Size(plataforma->getBoundingBox().size.width, plataforma->getBoundingBox().size.height),
		PhysicsMaterial(100.0f, 0.0f, 0.0f));
	body->setDynamic(false);
	body->setContactTestBitmask(true);
	body->setTag(taag);
	body->setCollisionBitmask(true);
	plataforma->setPhysicsBody(body);

	CCLOG("%d", taag);

	layer->addChild(plataforma, 1);
}

void Plataforma::setPosition(int X, int Y)
{
	plataforma->setPosition(X, Y);
}

Vec2 Plataforma::getPosition()
{
	return plataforma->getPosition();
}
void Plataforma::reposition()
{
	plataforma->setPosition(Xx, diferenceY);
}