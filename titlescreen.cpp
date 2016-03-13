/**
 * @file titlescreen.cpp
 * @brief contains function definitions for the TitleScreen class
*/
#include "titlescreen.h"
#include "ui_titlescreen.h"
#include "mainwindow.h"

/**
 * @brief TitleScreen::TitleScreen constructor
 * @param parent parent of this object
 * @param board the main window that this is a part of
*/
TitleScreen::TitleScreen(QWidget *parent, MainWindow* board) :
QWidget(parent), ui(new Ui::TitleScreen), window(board){
	ui->setupUi(this);
//Objects:
	title = new QLabel(this);	//Title label
	showInstructions = new QPushButton(this);	//PushButton to display instructions dialogue box
	begin = new QPushButton(this);	//PushButton to start a new game
//Layouts:
	QLabel* background = new QLabel;
	QHBoxLayout* backgroundLayout = new QHBoxLayout;
	QVBoxLayout* layoutMain = new QVBoxLayout;
	QHBoxLayout* layoutMid = new QHBoxLayout;
	QHBoxLayout* layoutBottom = new QHBoxLayout;
//Setting parameters:
	title->setStyleSheet("QLabel { color : white ;}");
	title->setText("              Dungeon Hero");
	title->setAlignment(Qt::AlignHCenter);
	title->setAlignment(Qt::AlignVCenter);
	showInstructions->setStyleSheet("QPushButton { color : white ;}");
	showInstructions->setText("Instructions");
	QObject::connect(showInstructions, SIGNAL(clicked()), this, SLOT(instructions()));
	begin->setStyleSheet("QPushButton { color : white ;}");
	begin->setText("Story");
	QObject::connect(begin, SIGNAL(clicked()), this, SLOT(beginGame()));
//Setting layouts:
	layoutMain->addWidget(title);
	layoutMain->setAlignment(Qt::AlignHCenter);
	layoutMain->addLayout(layoutMid);
	layoutMain->addLayout(layoutBottom);

	layoutMid->addWidget(showInstructions);
	layoutMid->addWidget(begin);

	//Attempt to paint a background
	this->setStyleSheet("QWidget { background-image: url(:/image/Images/Floor_Grass2.jpg) } ");
		//QPixmap backgroundImage(":/image/Images/Floor_Metal_Diamond.jpg");
		//QPainter painter(this);
		//painter.setBrush(QBrush(backgroundImage));
		//painter.drawRect(0,0,400,400);

//Setting it all on this widget:
	this->setLayout(layoutMain);
	//this->setStyleSheet("background-image:url(\"image/Images/Floor_Metal_Diamond.jpg\"); background-position: center;" );//"QWidget {background-image: url(./image/Images/Floor_Metal_Diamond.jpg) }");
}

/**
 * @function TitleScreen::beginGame()
 * @brief begins the game when clicked
 *		Will begin the story by default, unless a different level is selected in the combo box
 *		Will also begin the game in God Mode if the check box is selected
*/
void TitleScreen::beginGame(){
	window->beginNewGame();
}

/**
 * @function TitleScreen::instructions()
 * @brief dialogue box displaying game instructions
*/
void TitleScreen::instructions() {
	QMessageBox::information(
		this,
		tr("Instructions"),
		tr("WELCOME <br />"
			"To Move: Press I, J, K, L.<br />"
			"To Turn: Press A, D.<br />"
			"ATTACK: Press S.") );
}

/**
 * @function TitleScreen::~TitleScreen()
 * @brief destructor for the TitleScreen class
*/
TitleScreen::~TitleScreen(){
	delete ui;
}
