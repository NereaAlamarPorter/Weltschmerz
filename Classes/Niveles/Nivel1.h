#ifndef __NIVEL1_H__
#define __NIVEL1_H__


#include "cocos2d.h"
#include "Objetos\Plataforma.h"
#include "Objetos\Puerta.h"
#include "Objetos\Interruptor.h"
#include "Enemigos\Fantasma.h"
#include "Classes/Objetos/Estrella.h"
#include "Objetos\Agujero.h"
#include "Classes/Enemigos/Monstruo.h"

USING_NS_CC;
const int platTN = 22;
const int intTN = 4;
const int solidTN = 6;
const int fantTN = 3;
const int estrellaTN = 3;
const int manoTN = 4;
//const int manoTN = 1;

class Nivel1 : public cocos2d::Layer
{

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;


	Sprite* background;		//Fondo

	//Limites
	int MAXx;
	int MINx;

	Fantasma* fant1;
	Fantasma* fant2;
	Fantasma* fant3;
	Fantasma* fantT[fantTN];

	Monstruo* mano1;
	Monstruo* mano2;
	Monstruo* mano3;
	Monstruo* mano0;
	Monstruo* manoT[manoTN];

	//Solidos
	Plataforma* suelo;		//Suelo
	Plataforma* techo;		//Techo
	Plataforma* paredizq;	//
	Plataforma* paredder;	//
	Plataforma* paredbano;	//Coso baño
	Plataforma* paredhabi;	//Coso habitación

	Plataforma* ventanab;
	Plataforma* bañob;		//retrete
	Plataforma* baño2b;		//donde vael agua, ahora no me salen los nombres
	Plataforma* armariob;	//Armario
	//habitacion del nene
	Plataforma* baul;
	Plataforma* estanteria1;
	Plataforma* estanteria2;
	Plataforma* tablon;
	Plataforma* armario;


	Plataforma* solidT [solidTN];		//vector de bordes

	Puerta* p1;		//puerta hacia el limbo
	Puerta* pf;		//puerta fantasmas provisional
	Puerta* cama;

	//Interruptores
	Interruptor* interruptor01;//Baño
	Interruptor* interruptor02;//Pasillo1
	Interruptor* interruptor03;//Pasillo2
	Interruptor* interruptor04;//Habitación
	
	cocos2d::Sprite *luzapagada;
	bool Intestado;
	Interruptor* interT[intTN];

	//Estrellas
	Estrella* estrella01;
	Estrella* estrella02;
	Estrella* estrella03;
	Estrella* estrellaT[estrellaTN];


	// Plataformas
	Plataforma* cuadro1;	
	Plataforma* cuadro2;
	Plataforma* cuadro3;
	Plataforma* cuadro4;
	Plataforma* cuadro5;

	Plataforma* lampara1;
	Plataforma* lampara2;

	Plataforma* cajadederivacion;
	Plataforma* ventilacion;

	//hab
	Plataforma* mesa;
	Plataforma* pantalla;
	Plataforma* lampara3;
	Plataforma* torre;

	Plataforma*platT [platTN];

	Agujero* aguj;

public:

	bool right = false;
	bool left = false;
	bool falling = false;
	bool jumping = false;
	Vec2 rooneyOrigin;

	//Variables Mundo
	const Vec2 _gravity = Vec2(0, -1500);
	const int speed = 10;
	const int jump = 50;


	Nivel1(cocos2d::Layer *layer);
	void Move(int speed);
	void Jump(float jump);
	void Fall();
	int Action(Vec2 pos);
	int ActionIA(Vec2 pos);
	void desactivePB(float pos);
	void Interruptores();

	void reposition();

	void perSecond(); //funciones que se hagan cada segundo

};

#endif