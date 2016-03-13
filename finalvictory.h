#ifndef FINALVICTORY_H
#define FINALVICTORY_H
/**
 * @file finalvictory.h
 * @brief file containing function declarations for the FinalVictory class
*/
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

namespace Ui {
class FinalVictory;
}

/**
 * @class FinalVictory
 * @brief is the window that pops up when Dungeon Hero wins
*/
class FinalVictory : public QWidget
{
	Q_OBJECT

public:
	explicit FinalVictory(QWidget *parent = 0);
	~FinalVictory();
	void FinalVictory::paintEvent(QPaintEvent *e);

private:
	Ui::FinalVictory *ui;
};

#endif // FINALVICTORY_H
