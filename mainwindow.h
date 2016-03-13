#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/**
 * @file mainwindow.h
 * @brief file containing function declarations for the MainWindow class
*/
#include <QMainWindow>
#include <QHBoxLayout>
#include <QTimer>
#include "hero.h"
#include "titlescreen.h"
#include "gameplayboard.h"
#include "finalvictory.h"
#include "gameover.h"

class GameplayBoard;
class GameOver;
class FinalVictory;

namespace Ui {
class MainWindow;
}

/**
 * @class MainWindow
 * @brief is the main window that the entirety Dungeon Hero rests upon. Displays everything.
*/
class MainWindow : public QMainWindow{
	Q_OBJECT
	friend class GameplayBoard;
	friend class Hero;	//So that hero can know if it's in bounds
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void introduction();	//Intro Dialogue box
	void gameOver();
public slots:
	void beginNewGame();
private:
	Ui::MainWindow *ui;

	QWidget* mainWidget;
//	Hero* dungeonHero;
	const int WINDOWLENGTH = 400;	//square dimension of window

	//Displays in MainWindow: make these the Central Widget
	TitleScreen* titleScreen;	//The title screen that players will first see upon startup.
	GameplayBoard* gameBoard;	//Game Board that will be set as central widget once game begins
	GameOver* gameOverScreen;	//Game over screen once all lives are lost. Will be displayed and then take you back to the title screen.
	FinalVictory* finalVictoryScreen;	//Victory screen when the game it beaten.
};

#endif // MAINWINDOW_H
