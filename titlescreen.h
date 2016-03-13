#ifndef TITLESCREEN_H
#define TITLESCREEN_H
/**
 * @file titlescreen.h
 * @brief file containing function declarations for the TitleScreen class
*/
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
//#include <QBrush>

namespace Ui {
class TitleScreen;
}

class MainWindow;	//Forward declaration. Inclusion will be done in the .cpp file

/**
 * @class TitleScreen
 * @brief is the main menu in Dungeon Hero
*/
class TitleScreen : public QWidget{
	Q_OBJECT
friend class MainWindow;	//Friendship of MainWindow. We'll be able to access each other and begin the game.
public:
	explicit TitleScreen(QWidget* parent = nullptr, MainWindow* board = nullptr);	//CAREFUL, I CHANGED THIS. Default parent to nullptr, instead of the ugly 0
	~TitleScreen();

public slots:
	void beginGame();
	void instructions();
private:
	Ui::TitleScreen *ui;

	MainWindow* window;
	bool gameStart = false;	//keeps track of whether the game start button was clicked
	QLabel* title;
	QPushButton* showInstructions;
	QPushButton* begin;
	QComboBox* levelSelect;
	//note I'd also like a cheat code to unlock (show) the following:
	QCheckBox* godMode;
};

#endif // TITLESCREEN_H
