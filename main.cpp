/**
 * @file main.cpp
 * @brief contains the main function that runs everything
 * @author Bernardo Cobos
 * @date March 11, 20116
*/
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.setWindowTitle("Dungeon Hero");
	w.show();

	return a.exec();
}
