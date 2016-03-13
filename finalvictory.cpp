/**
 * @file finalvictory.cpp
 * @brief contains function definitions for the FinalVictory class
*/
#include "finalvictory.h"
#include "ui_finalvictory.h"

/**
 * @brief FinalVictory::FinalVictory constructor fot the FinalVictory widget
 * @param parent the parent of this widget
*/
FinalVictory::FinalVictory(QWidget *parent) :
QWidget(parent),
ui(new Ui::FinalVictory){
	ui->setupUi(this);
}

/**
 * @function FinalVictory::paintEvent()
 * @brief paints a background
*/
void FinalVictory::paintEvent(QPaintEvent *e){
	//Draw background:
	QPainter painter(this);
	QPixmap pixMap(":/image/Images/Floor_Grass1.jpg");
	painter.setBrush(QBrush(pixMap));
	painter.drawRect(0,0,400,400);

	painter.drawText(100,100," YOU HAVE WON.");
	painter.drawText(150,150," YOU HAVE SAVED YOUR FAMILY.");
}

/**
 * @brief FinalVictory::~FinalVictory destructo for this class
*/
FinalVictory::~FinalVictory(){
	delete ui;
}
