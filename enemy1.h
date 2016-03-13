#ifndef ENEMY1_H
#define ENEMY1_H
/**
 * @file enemy1.h
 * @brief declarations for all functions in the Enemy1 class
*/
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class GameplayBoard;
class Hero;

namespace Ui {
class Enemy1;
}

/**
 * @class Enemy1
 * @brief is the main enemy that Dungeon Hero will have to face
*/
class Enemy1 : public QWidget{
	Q_OBJECT
	friend class GameplayBoard;
	friend class Hero;	//So that the hero can kill it
public:
	explicit Enemy1(QWidget *parent = nullptr, GameplayBoard* board = nullptr, int posX = 0, int posY = 0);
	~Enemy1();	
	void paintEvent(QPaintEvent* e);
	void checkDistance();
private:
	Ui::Enemy1 *ui;
	//Coordinates:
	int x;
	int y;
	bool isDead;

	double  body_height = 20.0, body_width = 20.0;
	QRectF* body;	//boundary of the body that we're gonna use to draw

	GameplayBoard* game;
};

#endif // ENEMY1_H
