/**
 * @file hero.cpp
 * @brief contains function definitions for the Hero class
*/
#include "hero.h"
#include "ui_hero.h"
#include "mainwindow.h"
#include "gameplayboard.h"
#include "enemy1.h"

/**
 * @function Hero::Hero
 * @brief Hero constructor
 * @param parent, a pointer to this widget's parent
*/
Hero::Hero(QWidget *parent, GameplayBoard* board) :	//BEGIN field initializer list
QWidget(parent), ui(new Ui::Hero), game(board), x(200.0), y(300.0), angle(-90),
attacking(false),
body(-body_height/2.0,-body_width/2.0,body_height,body_width),
head(-head_height/2 + 1,-head_width/2,head_height,head_width)	//END Field initializer list.
{
	ui->setupUi(this);
	setFocus();	//Does this exist? Yes.
	grabKeyboard();	//For some reason this is an thing. Lets you take in keyboard stuff because it isn't done automatically
	setFocusPolicy(Qt::ClickFocus);	//In case you lose focus for some reason?

	attackTimer = new QTimer(this);	//Set a QTimer who knows about hero (Will be used for attack
	attackTimer->isSingleShot();	//Only timeout once, don't keep doing it
	QObject::connect(attackTimer, SIGNAL(timeout()), this, SLOT(endAttack()));	//Have the timer change the value of "attacking" bool at timeout
}

/**
 * @function Hero::~Hero()
 * @brief Hero destructor
*/
Hero::~Hero(){
	delete ui;
}

/**
 * @function hero::paintEvent
 * @brief hero avatar
 * @param e, the QPaintevent.
 * I assume this is what gets passed in when the event handler notices it's time for a paint event.
*/
void Hero::paintEvent(QPaintEvent* e){	
	//create the painter and set its coordinates.
	//painter.begin(this);
	QPainter painter(this);
	painter.translate(x,y);
	painter.rotate(angle);

	//set color and style
	painter.setPen(Qt::NoPen);	//Gets rid of outlines
	painter.setRenderHint(QPainter::Antialiasing);	//Sets antialiasing to smooth out graphics
	painter.setBrush(QBrush(Qt::blue));	//NOTE can set brush to pixmap!! Use this for monsters

	//first layer of drawing: Body
	painter.drawEllipse(body);

	//second layer of drawing: Head
	painter.setBrush(QBrush(Qt::gray));
	painter.drawEllipse(head);

	//third layer of drawing: Weapon
	weapon(painter);
}

/**
 * @function Hero::keyPressEvent
 *		Note it must be called this in order to work.
 * @brief handles all key events and how Dungeon Hero reacts
 * @param e, QKeyEvent thing.
*/
void Hero::keyPressEvent(QKeyEvent *event){	//How can I combine simultaneous key events?
	double angleRadians = angle * M_PI / 180.0;
	switch(event->key()){
		//Movement
		case Qt::Key_K:
			if (checkBounds(1)){
				x-= 10.0*cos(angleRadians);
				y-= 10.0*sin(angleRadians);
			}
		break;
		case Qt::Key_I:
			if (checkBounds(2)){
				x+= 10.0*cos(angleRadians);
				y+= 10.0*sin(angleRadians);
			}
		break;
		case Qt::Key_J:
			if (checkBounds(3)){
				x+= 10.0*sin(angleRadians);
				y-= 10.0*cos(angleRadians);
			}
		break;
		case Qt::Key_L:
			if (checkBounds(4)){
				x-= 10.0*sin(angleRadians);
				y+= 10.0*cos(angleRadians);
			}
		break;
		case Qt::Key_A:
			angle-= 10.0;
		break;
		case Qt::Key_D:
			angle+= 10.0;
		break;
		//Attack
		case Qt::Key_S:{
			attacking = true;
			attackTimer->start(200);	//See attackTimer construction in constructor.
		}
		default:
			QWidget::keyPressEvent(event);
	}
	for (auto x : game->enemies)	x->checkDistance();
	repaint();
	QCoreApplication::processEvents();	//Don't forget these last lines!
}

/**
 * @function Hero::checkBounds
 * @brief checks whether a move is legal
 * @param key, the specific case we're checking for (which movement key was hit)
 * @returns bool stating whether the move was legal
*/
bool Hero::checkBounds(int key){
	bool legal = true;
	double angleRadians = angle * M_PI / 180.0;
	int xcheck;
	int ycheck;
	switch(key){	//modify the "check" values
		case 1:
			xcheck = x - 10.0*cos(angleRadians);
			ycheck = y - 10.0*sin(angleRadians);
		break;
		case 2:
			xcheck = x + 10.0*cos(angleRadians);
			ycheck = y + 10.0*sin(angleRadians);
		break;
		case 3:
			xcheck = x + 10.0*sin(angleRadians);
			ycheck = y - 10.0*cos(angleRadians);
		break;
		case 4:
			xcheck = x - 10.0*sin(angleRadians);
			ycheck = y + 10.0*cos(angleRadians);
		break;
		default:	//This really shouldn't ever happen.
			return false;
	}
	if ((xcheck < 0) || (xcheck > game->window->WINDOWLENGTH))	legal = false;
	if ((ycheck < 0) || (ycheck > game->window->WINDOWLENGTH))	legal = false;
	return legal;
}

/**
 * @function Hero::weapon
 * @brief handles drawing of the weapon and the attack animation
 * @param &painter, the QPainter reference that is drawing the hero
 */
void Hero::weapon(QPainter& painter){
	//if (weapon == spear)
	{
		if (!attacking){
			double length = 24.0, width = 2.0;	//Spear body
			painter.setBrush(QBrush(Qt::black));
			QRectF spearBody(-15,9,length,width);
			painter.drawRect(spearBody);
			painter.setPen(Qt::SolidLine);		//Spear Head
			length = 6.0;
			painter.setBrush(QBrush(Qt::gray));
			QRectF spearTip(5,9,length,width);
			painter.drawRect(spearTip);
		}
		//Attack painting / (registration)
		else {
			double length = 24.0, width = 2.0;	//Spear body
			painter.setBrush(QBrush(Qt::black));
			QRectF spearBody(0,9,length,width);
			painter.drawRect(spearBody);
			painter.setPen(Qt::SolidLine);		//Spear head
			length = 6.0;
			painter.setBrush(QBrush(Qt::gray));
			QRectF spearTip(20,9,length,width);
			painter.drawRect(spearTip);
			//NOTE the attack animation is being handled in the QKeyEvent function.

			//Checking whether the attack was valid, and killing monsters if so:
			double angleRadians = angle * M_PI / 180.0;
			attackRegister(angleRadians);
		}
	}
}

/**
 * @function Hero::attackRegister
 * @brief checks whether to register an attack on an Enemy1
 * @param angleRadians the direction that the hero is facing, in radians.
 * @returns a bool stating whether an enamy was killed
*/
bool Hero::attackRegister(double angleRadians){	//note return a bool? Maybe it could be useful.
	//Formalize everything in terms of common coordinates.
	QPoint attackPoint(0,0);(x + 23*cos(angleRadians), y - 10*sin(angleRadians - M_PI/2));	//FIX ANGLES!!!
	attackPoint.setX(x + 23*cos(angleRadians) - 10*sin(angleRadians));
	attackPoint.setY(y + 23*sin(angleRadians) + 10*cos(angleRadians));

//INGENIOUS TROUBLESHOOTING TOOL: Getting the proper "stabby" coordinates: show on screen!
	//QPainter painterTemp(this);
	//painterTemp.setBrush(QBrush(Qt::black));
	//QPoint o(x,y);
	//painterTemp.drawLine(o,attackPoint);

	QRect enemyBodyCheck(0,0,0,0);	//a shape that looks like the enemy. Checks enemy bounds of attack.
	QPoint enemyTopLeft(0,0);	//So we can set this overlap shape on the enemy
	QPoint enemyBottomRight(0,0);
	bool enemyKilled = false;

	//Checking through all monsters on board to check whether the spear has penetrated a monster.
	//If so, kill the monster.
	size_t all = game->enemies.size();
	for (size_t i = 0; i < all; ++i) {	//cycle through all enemies
		enemyTopLeft.setX(game->enemies[i]->x - 9);	// +/- 9 is to get hit-rectangle centered about actual monster. 9 chosen so you must stab inside monster (note the full range of the monster would be +/- 10
		enemyTopLeft.setY(game->enemies[i]->y - 9);
		enemyBottomRight.setX((game->enemies[i]->x)+9);
		enemyBottomRight.setY((game->enemies[i]->y)+9);
		enemyBodyCheck.setTopLeft(enemyTopLeft);
		enemyBodyCheck.setBottomRight(enemyBottomRight);

		if (enemyBodyCheck.contains(attackPoint) && !(game->enemies[i]->isDead)){	//want to check if the attackPoint is inside of a living enemy.
				//std::swap(game->enemies[i], game->enemies[all - 1]);	//Send the monster to the end of the vector.
				//delete game->enemies[all - 1];	//Maybe you can make variables for this so that notation is cleaner.
				//game->enemies.pop_back();	//Banish the monster.
			game->enemies[i]->isDead = true;
			enemyKilled = true;
			++enemiesKilled;
			if (enemiesKilled == 20) game->endGame();
			return enemyKilled;
		}
	}
	return enemyKilled;
}

/**
 * @function Hero::endAttack()
 * @brief effectively ends the attack animation
*/
void Hero::endAttack(){	//to exit attack animation
	attacking = false;
	repaint();
	QCoreApplication::processEvents();
}

/**
 * @function Hero::takeDamage()
 * @brief harms the hero and checks whether the game has ended.
*/
void Hero::takeDamage() {
	HP -= 7;
	if (HP < 0){
		game->death = true;
		game->endGame();
	}
}
