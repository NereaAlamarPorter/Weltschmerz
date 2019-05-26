#include "Nivel1.h"
#include "GameLvl1Scene.h"
#include "Objetos\Plataforma.h"
#include "Objetos\Puerta.h"
#include "Enemigos\Fantasma.h"
#include "Classes/Objetos/Estrella.h"
#include "Objetos\Agujero.h"
#include "Classes/Enemigos/Monstruo.h"

USING_NS_CC;

Nivel1::Nivel1(cocos2d::Layer *layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	right = false;
	left = false;
	rooneyOrigin = Vec2(visibleSize.width / 2, visibleSize.height / 5);

	background = Sprite::create("images/Nivel1/fondo.jpg");
	background->setPosition(origin.x+300,origin.y);

	layer->addChild(background, 0);
	auto purque = 380;

	

	//PUERTAS
	p1 = new Puerta(layer, visibleSize.width * 3 / 1.5f + 250 + purque, 280, 0);
	pf = new Puerta(layer, visibleSize.width * 4 + 200 + purque, 280, 0);
	cama = new Puerta(layer, visibleSize.width * 9 + 100, 150, 7);

	//INTERRUPTOR
	int altura = visibleSize.height / 6;
	interruptor01 = new Interruptor(layer, visibleSize.width / 2 - 200 , altura);	//Baño
	interruptor02 = new Interruptor(layer, visibleSize.width / 2 , altura);	//Pasillo1
	interruptor03 = new Interruptor(layer, visibleSize.width * 6 - 100 , altura);	//Pasillo2
	interruptor04 = new Interruptor(layer, visibleSize.width * 6 - 300 , altura);	//Habitación
	
	luzapagada = Sprite::create("images/Nivel1/interruptor/Negro.jpg");
	luzapagada->setPosition(visibleSize.width/2, visibleSize.height/2);
	luzapagada->setOpacity(248);
	luzapagada->setVisible(false);
	layer->addChild(luzapagada, 3);
	Intestado = false;

	interT[0] = interruptor01;
	interT[1] = interruptor02;
	interT[2] = interruptor03;
	interT[3] = interruptor04;

	//PLATAFORMAS
	//cuadros
	altura = visibleSize.height / 2- 50;
	cuadro1 = new Plataforma(layer, visibleSize.width * 3 / 2 + 350 + purque, altura, 1);
	cuadro2 = new Plataforma(layer, visibleSize.width * 3 - 160 + purque, altura, 1);
	cuadro3 = new Plataforma(layer, visibleSize.width * 3 + 330 + purque, altura, 1);
	cuadro4 = new Plataforma(layer, visibleSize.width * 3 + 820 + purque, altura, 1);
	cuadro5 = new Plataforma(layer, visibleSize.width * 5 + 100 + purque, altura, 1);
	//lamparas
	altura = visibleSize.height / 2 + 50;
	lampara1 = new Plataforma(layer, visibleSize.width + 130 + purque, altura, 4);
	lampara2 = new Plataforma(layer, visibleSize.width * 4 + 700 + purque, altura, 4);
	//cosos
	altura += 20;
	cajadederivacion = new Plataforma(layer, visibleSize.width * 3 / 2 + 30 + purque, altura, 5);
	altura = 90;
	ventilacion = new Plataforma(layer, visibleSize.width * 3 / 2 - 20 + purque, altura, 6);

	//cuarto de baño
	ventanab = new Plataforma(layer, -250, 450, 9);
	bañob = new Plataforma(layer, -visibleSize.width + purque + 144, 100, 21);
	baño2b = new Plataforma(layer, -visibleSize.width + purque + 83, 238, 20);
	armariob = new Plataforma(layer, 200, 630, 19);

	//habitación del nene
	baul = new Plataforma(layer,		visibleSize.width * 6 + 500, 120, 10);
	estanteria1 = new Plataforma(layer, visibleSize.width * 6 + 250, 450, 11);
	estanteria2 = new Plataforma(layer, visibleSize.width * 6 + 600, 750, 12);
	tablon = new Plataforma(layer,		visibleSize.width * 7 + 100, 400, 13);

	pantalla = new Plataforma(layer,	visibleSize.width * 8 + 250, 290, 15);
	torre = new Plataforma(layer,		visibleSize.width * 8 +  100, 90, 16);
	mesa = new Plataforma(layer,		visibleSize.width * 8 + 300, 135, 14);
	lampara3 = new Plataforma(layer,	visibleSize.width * 8, 270, 17);
	armario = new Plataforma(layer, visibleSize.width * 8 - 400, 385, 22);
	
	platT[0] = cuadro1;
	platT[1] = cuadro2;
	platT[2] = cuadro3;
	platT[3] = cuadro4;
	platT[4] = cuadro5;
	platT[5] = lampara1;
	platT[6] = cajadederivacion;
	platT[7] = ventilacion;
	platT[8] = lampara2;

	platT[9] = ventanab;
	platT[10] = bañob;
	platT[11] = baño2b;
	platT[12] = armariob;

	platT[13] = baul;
	platT[14] = estanteria1;
	platT[15] = estanteria2;
	platT[16] = tablon;

	platT[17] = mesa;
	platT[18] = pantalla;
	platT[19] = lampara3;
	platT[20] = torre;
	platT[21] = armario;


	//SOLIDOS
	//bordes
	
	techo = new Plataforma(layer, 0, visibleSize.height * 1.5, 2);
	paredder = new Plataforma(layer, visibleSize.width * 9 + purque, visibleSize.height / 2, 7);
	paredizq = new Plataforma(layer, -visibleSize.width + purque, visibleSize.height / 2, 7);
	paredhabi = new Plataforma(layer, visibleSize.width * 6 - 200, visibleSize.height*1.81, 7);
	paredbano = new Plataforma(layer, visibleSize.width / 2 - 100 , visibleSize.height*1.81, 7);
	suelo = new Plataforma(layer, 0, 0, 18);

	solidT[0] = suelo;
	solidT[1] = techo;
	solidT[2] = paredder;
	solidT[3] = paredizq;
	solidT[4] = paredbano;
	solidT[5] = paredhabi;

	


	//FANTASMAS
	auto j = Vec2(visibleSize.width * 4 + 200 + purque, 200);
	fant1 = new Fantasma(layer, j.x, j.y);
	fant2 = new Fantasma(layer, j.x, j.y);
	fant3 = new Fantasma(layer, j.x, j.y);
	fantT[0] = fant1;
	fantT[1] = fant2;
	fantT[2] = fant3;

	//ESTRELLAS

	estrella01 = new Estrella(layer, visibleSize.width + 130 + purque, 200 + visibleSize.height / 2);
	estrella02 = new Estrella(layer, 200, 850);
	estrella03 = new Estrella(layer, visibleSize.width * 5 + 100 + purque, visibleSize.height / 2 + 150);

	estrellaT[0] = estrella01;
	estrellaT[1] = estrella02;
	estrellaT[2] = estrella03;

	//MONSTRUO

	int XXXXXX = visibleSize.width*8-550;
	int YYYYYY = 350;
	mano0 = new Monstruo(layer, XXXXXX + 350, YYYYYY + 300, 0);
	mano1 = new Monstruo(layer, XXXXXX-50, YYYYYY + 300, 2);
	mano2 = new Monstruo(layer, XXXXXX + 350, YYYYYY, 1);
	mano3 = new Monstruo(layer, XXXXXX - 50, YYYYYY, 3);
	
	manoT[0] = mano0;
	manoT[1] = mano1;
	manoT[2] = mano2;
	manoT[3] = mano3;

	aguj = new Agujero(layer, visibleSize.width, 105);

	MAXx = visibleSize.width * 9 + 330;
	MINx = -visibleSize.width + 410;
}

void Nivel1::Move(int speed)
{
	int _sp = 0;

	if (right==true) _sp = -1 * speed;
	else if (left==true) _sp = speed;
	
	if (MAXx <= visibleSize.width/2 && right|| left && MINx >= visibleSize.width/2) return;
	
	for (int g = 2; g < solidTN; g++)
	{
		solidT[g]->setPosition(solidT[g]->getPosition().x + _sp, solidT[g]->getPosition().y);
	}

	for (int j = 0; j < intTN; j++)
	{
		interT[j]->setPosition(interT[j]->getPosition().x + _sp, interT[j]->getPosition().y);
	}
	for (int i = 0; i < platTN; i++)
	{
		platT[i]->setPosition(platT[i]->getPosition().x + _sp, platT[i]->getPosition().y);
	}

	MINx = baño2b->getPosition().x ;
	
	p1->setPosition(p1->getPosition().x + _sp, p1->getPosition().y);
	pf->setPosition(pf->getPosition().x + _sp, pf->getPosition().y);
	cama->setPosition(cama->getPosition().x + _sp, cama->getPosition().y);

	MAXx = cama->getPosition().x + 200;

	for (int a = 0; a < fantTN; a++)
	{
		fantT[a]->Move();
		fantT[a]->setPosition(fantT[a]->getPosition().x + _sp, fantT[a]->getPosition().y);
		fantT[a]->spawnPoint.x += _sp;
	}

	for (int a = 0; a < manoTN; a++)
	{
		//manoT[a]->Move2(armario->getPosition());

		manoT[a]->Move();
		manoT[a]->setPosition(manoT[a]->getPosition().x + _sp, manoT[a]->getPosition().y);
	}
	
	for (int l = 0; l < estrellaTN; l++)
	{
		estrellaT[l]->setPosition(estrellaT[l]->getPosition().x + _sp, estrellaT[l]->getPosition().y);
	}

	aguj->setPosition(aguj->getPosition().x + _sp, aguj->getPosition().y);
	
}

void Nivel1::Jump(float jump)
{
	
	suelo->setPosition(suelo->getPosition().x, suelo->getPosition().y + jump);
	int sY = suelo->getPosition().y;

	

	//fantasmas
	for (int a = 0; a < fantTN; a++)
	{
		fantT[a]->setPosition(fantT[a]->getPosition().x, sY + fantT[a]->diferenceY2);
		fantT[a]->spawnPoint.y += fantT[a]->diferenceY;
	}

	//solidos
	for (int g = 1; g < solidTN; g++)
	{
		solidT[g]->setPosition(solidT[g]->getPosition().x, sY + solidT[g]->diferenceY);
	}
	//Interruprotres
	for (int j = 0; j < intTN; j++)
	{
		interT[j]->setPosition(interT[j]->getPosition().x, sY + interT[j]->diferenceY);
	}
	//Puerta
	p1->setPosition(p1->getPosition().x, sY + p1->diferenceY);
	pf->setPosition(pf->getPosition().x, sY + pf->diferenceY);
	cama->setPosition(cama->getPosition().x, sY + cama->diferenceY);
	//Plataformas
	for (int i = 0; i < platTN; i++)
	{
		platT[i]->setPosition(platT[i]->getPosition().x, sY + platT[i]->diferenceY);
	}

	//manos
	for (int a = 0; a < manoTN; a++)
	{
		//manoT[a]->jump(armario->getPosition());
		//manoT[a]->diferenceY += jump;
	}

	//Estrrellas
	for (int l = 0; l < estrellaTN; l++)
	{
		estrellaT[l]->setPosition(estrellaT[l]->getPosition().x,sY+ estrellaT[l]->diferenceY);
	}

	background->setPosition(background->getPosition().x, sY + background->getBoundingBox().size.height / 2);

	aguj->setPosition(aguj->getPosition().x, sY + aguj->diferenceY);
}

int Nivel1::Action(Vec2 pos)
{
	int tipo=NULL;
	tipo = cama->Action(pos.x, pos.y);//Puerta
	if (tipo != NULL) return tipo;

	for (int i = 0; i < intTN; i++) //Interruptores
	{
		tipo = interT[i]->Action(pos.x, pos.y);
		if (tipo != NULL){
			Interruptores();
			return tipo;
		}
	}

	return tipo;
}

int Nivel1::ActionIA(Vec2 pos)
{
	int tipo = NULL;

	cama->Action(pos.x, pos.y);
	if (tipo != NULL) return tipo;

	
	//Estrellas
	for (int i = 0; i < estrellaTN; i++)
	{
		tipo = estrellaT[i]->Action(pos.x, pos.y);
		if (tipo != NULL) return tipo;
	}
	//Fantasma
	
	for (int i = 0; i < fantTN; i++){
		if (Intestado) fantT[i]->existe=false;
		else tipo = fantT[i]->Action(pos.x, pos.y);
		if (tipo != NULL) return tipo;
	}

	for (int i = 0; i < manoTN; i++){
		if (Intestado) manoT[i]->existe = false;
		else
		{
			tipo = manoT[i]->Action(pos.x, pos.y);
			manoT[i]->existe = true;
		}
		if (tipo != NULL) return tipo;
	}

	

	tipo= aguj->Action(pos.x, pos.y);

	
	
	return tipo;
}

void Nivel1::desactivePB(float pos)
{
	for (int i = 0; i < platTN; i++)
	{
		if (platT[i]->getPosition().y > pos){ platT[i]->plataforma->getPhysicsBody()->setEnable(false); }
		else platT[i]->plataforma->getPhysicsBody()->setEnable(true);
	}
	if (p1->getPosition().y > pos + p1->getBoundingBox().size.height){ p1->puerta->getPhysicsBody()->setEnable(false); }
	else p1->puerta->getPhysicsBody()->setEnable(true);

}

void Nivel1::Interruptores()
{
	if (Intestado == false)
	{
		Intestado = true;
		luzapagada->setVisible(true);
		cama->disponible = true;
	}
	else 
	{
		Intestado = false;
		luzapagada->setVisible(false);
		cama->disponible = false;
	}
	for (int i = 0; i < intTN; i++)
	{
		interT[i]->changeDisp(Intestado);
	}

	for (int l = 0; l < estrellaTN; l++)
	{
		estrellaT[l]->aparecer();
	}
}

void Nivel1::perSecond()
{
	for (int a = 0; a < fantTN; a++)
	{
		if (!Intestado){
			fantT[a]->updateConts();
		}
	}

	for (int a = 0; a < manoTN; a++)
	{
		
		manoT[a]->perSecond();
		
	}
}

void Nivel1::reposition()
{
	MAXx = visibleSize.width * 8 + 330;
	MINx = -visibleSize.width + 430;

	suelo->setPosition(visibleSize.width/2,0);
	int sY = suelo->getPosition().y;

	//fantasmas
	for (int a = 0; a < fantTN; a++)
	{
		fantT[a]->reposition();
	}

	for (int a = 0; a < manoTN; a++)
	{
		manoT[a]->reposition();
	}

	//solidos
	for (int g = 1; g < solidTN; g++)
	{
		solidT[g]->reposition();
	}

	//Interruprotres
	for (int j = 0; j < intTN; j++)
	{
		interT[j]->reposition();
	}
	//Puerta
	p1->reposition();
	pf->reposition();
	cama->reposition();
	//Plataformas
	for (int i = 0; i < platTN; i++)
	{
		platT[i]->reposition();
	}
	//Estrrellas
	for (int l = 0; l < estrellaTN; l++)
	{
		estrellaT[l]->reposition();
	}

	background->setPosition(origin.x + 300, origin.y);

	aguj->reposition();
	techo->setPosition(techo->getPosition().x, visibleSize.height * 1.5);

}