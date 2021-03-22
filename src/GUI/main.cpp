#include "mainwindow.h"
#include "sudokumainwindow.h"
#include "qdebug.h"
#include <array>


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

	std::array<std::array<unsigned short, 9>, 9> sudoku;

	for (int i = 0; i < 9; i++) {
		sudoku[i].fill(9);
	}

	qDebug() << sudoku[0][0];

    w.show();
    return a.exec();
}
