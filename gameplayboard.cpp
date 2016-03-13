/**
 * @file gameplayboard.cpp
 * @brief contains function definitions for the GameplayBoard class
*/
#include "gameplayboard.h"
#include "ui_gameplayboard.h"
#include "mainwindow.h""
#include "hero.h"
#include "enemy1.h"

/**
 * @function Gameplayboard::GameplayBoard
 * @brief constructor for the GameplayBoard class
*/
GameplayBoard::GameplayBoard(QWidget *parent, MainWindow* board) :
QWidget(parent), ui(new Ui::GameplayBoard), window(board), generator(SEED),
 unifX(0,window->WINDOWLENGTH),
 unifY(0,window->WINDOWLENGTH - 125){
	ui->setupUi(this);

	//NEW TRY: no layouts
	dungeonHero = new Hero(this, this);

	enemyTimer = new QTimer(this);
	QObject::connect(enemyTimer,SIGNAL(timeout()),this,SLOT(generateEnemy()));
	//enemyTimer->start(750);	//donw in mainWindow instead

	healthDisplay = new QProgressBar(this);
	healthDisplay->setMaximum(dungeonHero->HP);	//Initializes to max Hero health (currently 100 HP)
	healthDisplay->setValue(dungeonHero->HP);
	healthDisplay->setFormat("HEALTH");
}

/**
 * @function GameplayBoard::~GameplayBoard()
 * @brief destructor
*/
GameplayBoard::~GameplayBoard(){
	delete ui;
}

/**
 * @function GameplayBoard::paintEvent()
 * @brief paints a background
*/
void GameplayBoard::paintEvent(QPaintEvent *e){
	//Draw background:
	QPainter painter(this);
	QPixmap pixMap(":/image/Images/Floor_Stone.jpg");
	painter.setBrush(QBrush(pixMap));
	painter.drawRect(0,0,window->WINDOWLENGTH,window->WINDOWLENGTH);

	//Draw balcony rail:
	pixMap.load(":/image/Images/Floor_Wood.jpg");
	painter.setBrush(pixMap);
	painter.drawRect(0,300,window->WINDOWLENGTH, 10);

	//Background of health bar
	painter.setBrush(QBrush(Qt::white));
	painter.drawRect(0,0,105,21);

	//Display of enemies remaining:
	painter.drawRect(250,0,150,21);
	painter.drawText(255, 15, "Enemies Killed (in Unicode): "); //<< dungeonHero->enemiesKilled);
	QString string = dungeonHero->enemiesKilled;
	painter.drawText(390,15, string);
}

/**
 * @function GameplayBoard::distance_from_hero
 * @brief checks how far away something is from the hero
 * @params int x1, y1 the central coordinates of the object who's distance we're checking
 * @returns the value of the distance
*/
int GameplayBoard::distance_from_hero(int x1, int y1){
	double distanceSquared = (((dungeonHero->x - x1)*(dungeonHero->x - x1)) + (dungeonHero->y - y1)*(dungeonHero->y - y1));
	return sqrt(distanceSquared);
}

/**
 * @function GameplayBoard::generateEnemy
 * @brief puts a new enemy in a random location on screen
*/
void GameplayBoard::generateEnemy(){
	//Creation of the new enemy, in a random location on screen:
	bool enemyCreated = false;
	int x = unifX(generator);
	int y = unifY(generator);
	double distance = distance_from_hero(x,y);

	while (!enemyCreated){
		if (distance > 27.0){	//If new enemy won'r overlap with hero, create it.
			enemies.push_back(new Enemy1(this,this,x, y));
			enemyCreated = true;
		}
		else{	//otherwise keep going
			x = unifX(generator);
			y = unifY(generator);
			distance = distance_from_hero(x,y);
		}
	}
}

/**
 * @function GameplayBoard::endGame();
 * @brief ends the game;
*/
void GameplayBoard::endGame(){
	window->gameOver();
}
