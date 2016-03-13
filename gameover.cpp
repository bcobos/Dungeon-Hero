/**
 * @file gameover.cpp
 * @brief contains function definitions for the GameOver widget class
*/
#include "gameover.h"
#include "ui_gameover.h"

/**
 * @function GameOver::GameOver(QWidget *parent)
 * @brief constructor for the GameOver widget
*/
GameOver::GameOver(QWidget *parent) :
QWidget(parent), ui(new Ui::GameOver){
	ui->setupUi(this);
}

/**
 * @function GameOver::paintEvent
 * @brief draws the widget contents.
*/
void GameOver::paintEvent(QPaintEvent *e){
	//Draw background:
	QPainter painter(this);
	QPixmap pixMap(":/image/Images/Floor_Marble.jpg");
	painter.setBrush(QBrush(pixMap));
	painter.drawRect(0,0,400,400);

	painter.drawText(100,105,"YOU HAVE DIED AND LET DOWN YOUR DEAD FAMILY.");

}

/**
 * @function GameOver::~GameOver
 * @brief destructor for this widget
*/
GameOver::~GameOver(){
	delete ui;
}
