/**
 * @file enemy1.cpp
 * @brief contains function definitions for the Enemy1 class
*/
#include "enemy1.h"
#include "ui_enemy1.h"
#include "gameplayboard.h"
#include "hero.h"

/**
 * @brief Enemy1::Enemy1 is the constructor for the class
 * @param parent its parent
 * @param board the game that is being played in
 * @param posX x position of the enemy
 * @param posY y position of the enemy
*/
Enemy1::Enemy1(QWidget *parent, GameplayBoard* board, int posX, int posY) :
QWidget(parent), ui(new Ui::Enemy1), x(posX), y(posY), game(board), isDead(false){
	ui->setupUi(this);

	body = new QRectF(-body_height/2.0,-body_width/2.0,body_height,body_width);	//Set a rectangle about the center of, and the size of the enemy
	show();
}

/**
 * @function Enemy1::~Enemy1()
 * @brief Enemy1 destructor
*/
Enemy1::~Enemy1(){
	delete ui;
}

/**
 * @function Enemy1::paintEvent(QPaintEvent* e);
 * @brief draws the Enemy1 class object
 * @param e, the QPaintEvent thing
*/
void Enemy1::paintEvent(QPaintEvent* e){
	if (!isDead){
	//create the painter and set its coordinates to the Enemy1's current location
		QPainter painter(this);
		painter.translate(x,y);

	//Setting painter style:
		painter.setPen(Qt::NoPen);
		painter.setRenderHint(QPainter::Antialiasing);
		painter.setBrush(QBrush(Qt::red));
		//QPixmap enemyPixMap(":/image/Images/Hellknight.gif");
		//QPixmap enemyPixMap(":/image/Images/Cacodemon.png");
		//painter.setBrush(QBrush(enemyPixMap));

	//Drawing:
		painter.drawEllipse(*body);
		//painter.drawRect(*body);

	}
}

/**
 * @function Enemy1::checkDistance()
 * @brief attacks the hero if too close
*/
void Enemy1::checkDistance(){
	if (!isDead){
		if (game->distance_from_hero(x,y) < 15){
			game->dungeonHero->takeDamage();
			game->healthDisplay->setValue(game->dungeonHero->HP);
		}
	}
}
