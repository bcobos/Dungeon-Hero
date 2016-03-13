#ifndef GAMEPLAYBOARD_H
#define GAMEPLAYBOARD_H
/**
 * @file gameplayboard.h
 * @brief file containing function declarations for the GameplayBoard class
*/
#include <QWidget>
#include <QHBoxLayout>
#include <QTimer>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QProgressBar>
#include <cmath>
#include <chrono>
#include <random>

// Macros to make creating random integers easier to read and write
#define SEED (unsigned int)std::chrono::system_clock::now().time_since_epoch().count()
#define DEFAULT std::default_random_engine

class MainWindow;	//Forward declaration to be able to access main game elements
class Hero;
class Enemy1;

namespace Ui {
class GameplayBoard;
}

/**
 * @class GameplayBoard
 * @brief is the main gameplay board that the Dungeon Hero will be played on
*/
class GameplayBoard : public QWidget{
	Q_OBJECT
	friend class MainWindow;
	friend class Hero;
	friend class Enemy1;
public:
	explicit GameplayBoard(QWidget *parent = nullptr, MainWindow* board = nullptr);
	~GameplayBoard();
	int distance_from_hero(int x1, int y1);
	void paintEvent(QPaintEvent* e);	//To make a background.
	void endGame();

public slots:
	void generateEnemy();

private:
	Ui::GameplayBoard *ui;

	MainWindow* window;	//Pointer to the main game
	//QHBoxLayout* gameplayLayout;	//layout which will contain the display on the game board
	Hero* dungeonHero;
	QLabel* livesDisplay;
	QProgressBar* healthDisplay;
	bool death = false;
	QLabel* pendantDisplay;	//Use QPainter to get this to show up in the right place. Is there another better way?
	//QPixmap* floor;
	std::vector<Enemy1*> enemies;

	DEFAULT generator;
	// Create Uniform(0,WINDOWLENGTH) generators. Will determine x and y coordinated of next monsters to be created
	std::uniform_int_distribution<int> unifX;	//how do we account for not spawning an enemy on the Hero?
	std::uniform_int_distribution<int> unifY;

	//test run: want the enemies to start showing up with a timer
	QTimer* enemyTimer;

};

#endif // GAMEPLAYBOARD_H
