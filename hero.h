#define _USE_MATH_DEFINES
#ifndef HERO_H
#define HERO_H
/**
 * @file hero.h
 * @brief file containing function declarations for the Hero class
*/
#include <QWidget>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>
#include <cmath>
#include <QTimer>
class MainWindow;
class GameplayBoard;

namespace Ui {
class Hero;
}

/**
 * @class Hero
 * @brief is the Dungeon Hero and all of the character's functionality
*/
class Hero : public QWidget{
	Q_OBJECT
	friend class GameplayBoard;	//So the board can access lives, health, etc.
	friend class Enemy1;	//So that it can attack back
public:
	explicit Hero(QWidget *parent = nullptr, GameplayBoard *board = nullptr);
	~Hero();
	void paintEvent(QPaintEvent* e);	//So we can paint and repaint!
	void keyPressEvent(QKeyEvent* event);	//So we can control. Not we need paintEvent to notice a difference.
	void weapon(QPainter& painter);	//Weapon drawing and attack animation
	bool attackRegister(double angleRadians);	//Damaging enemies
	bool checkBounds(int i);	//Checking if you can move some direction
	void takeDamage();
public slots:
	void endAttack();
private:
	Ui::Hero *ui;
	double x;
	double y;
	double angle;
	//int currentWeapon;	//Is this how you want to do this?
	//int currentShield;
	bool hasPendant;
	int lives = 4;
	int HP = 100;
	int enemiesKilled = 0;
	bool attacking;

	GameplayBoard* game;
	QTimer* attackTimer;	//attack animation timer.
	//QPainter painter;	//Will draw the hero
	double  body_height = 10.0, body_width = 27.0;	//The hero's body.
	QRectF body;	//initialized in constructor
	double head_height = 10.0, head_width = 9.0;	//The hero's head.
	QRectF head;
};

#endif // HERO_H
