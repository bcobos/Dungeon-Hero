#ifndef GAMEOVER_H
#define GAMEOVER_H
/**
 * @file gameover.h
 * @brief file containing function declarations for the GameOver class
*/
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

namespace Ui {
class GameOver;
}
/**
 * @class GameOver
 * @brief is the window that Dungeon Hero sees upon death
*/
class GameOver : public QWidget{
	Q_OBJECT

public:
	explicit GameOver(QWidget *parent = 0);
	~GameOver();
	void GameOver::paintEvent(QPaintEvent *e);

private:
	Ui::GameOver *ui;
};

#endif // GAMEOVER_H
