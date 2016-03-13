/**
 * @file mainwindow.cpp
 * @brief contains function definitions for the MainWindow class
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>

/**
 * @brief MainWindow::MainWindow constructor
 * @param parent the parent of this object
*/
MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow){
	ui->setupUi(this);

	setFixedSize(WINDOWLENGTH, WINDOWLENGTH);	//set permanent size of the window

//Objects:
	//These objects come preloaded with their specifications, as defined in their .cpp files.
	//Creation of...
	mainWidget = new QWidget;	//...The main widget in which everything is displayed...
	titleScreen = new TitleScreen(this, this);	//...Title Screen...
	gameBoard = new GameplayBoard(nullptr, this);	//...Board on which gameplay will take place.
//Layouts:
	QHBoxLayout* titleMenuLayout = new QHBoxLayout;	//layout which will contain the titleMenu
	QHBoxLayout* gameScreenLayout = new QHBoxLayout;	//layout which will contain gameplay
	//QHBoxLayout* gameplayLayout = new QHBoxLayout;	//layout which will contain the display on the game board (QUESTION: WHY AM I DOING THIS HERE? THIS SHOULD MAYBE BE IN GAMEPLAYBOARD.CPP)
//Setting parameters:
	//gameplayLayout->addWidget(dungeonHero);		//Hero added to the gameplay board's layout
	//gameBoard->setLayout(gameplayLayout);		//Gameplay board layout (containing hero) loaded onto the gameplay board.
	gameScreenLayout->addWidget(gameBoard);		//GameBoard widget loaded onto the game screen layout
	titleMenuLayout->addWidget(titleScreen);	//Title Screen widget loaded onto the title screen layout.
//Setting display:
	mainWidget->setLayout(titleMenuLayout);
	this->setCentralWidget(mainWidget);	//make the mainWidget the central widget to display (whichever it may be)
}

/**
 * @function MainWindow::~MainWindow()
 * @brief destructor for MainWindow
*/
MainWindow::~MainWindow(){
	delete ui;
}

/**
 * @function slot MainWindow::beginNewGame()
 * @brief starts a new game.
 *		This function is run once the new game button and option is chosen on the title screen.
*/
void MainWindow::beginNewGame(){
	this->setCentralWidget(gameBoard);
	introduction();
	gameBoard->enemyTimer->start(750);
}

/**
 * @function MainWindow::introduction()
 * @brief dialogue box displaying game introductions
*/
void MainWindow::introduction() {
	QMessageBox::information(
		this,
		tr("INTRODUCTION"),
		tr("YOUR HOUSE IS UNDER ATTACK<br />"
			"You step outside your home to see that monsters are invading your courtyard. <br />"
			"You know you must defend your young family. You must kill all TWENTY monsters.<br />"
			"Armed only with an old spear, you run outside to meet them... <br /> <br />"
			"YOUR DAUGHTER YELLS AFTER YOU: \"Parent!! Hide under the balcony for cover! The monsters will not spawn there!\"<br />"
			)
	);
}

/**
 * @function mainWindow::gameOver()
 * @brief ends the game and gives final screen, whether death or victory.
*/
void MainWindow::gameOver(){
	if (gameBoard->death){
		gameOverScreen = new GameOver(this);
		this->setCentralWidget(gameOverScreen);
	}
	else{
		finalVictoryScreen = new FinalVictory(this);
		this->setCentralWidget(finalVictoryScreen);
	}
}
