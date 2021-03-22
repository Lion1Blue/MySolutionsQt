#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	ui->tabWidget->clear();

	//add Sudoku
	sudokuMainWindow = new SudokuMainWindow(ui->tabWidget);
	sudokuMainWindow->setAttribute(Qt::WA_DeleteOnClose); // makes Qt delete this widget when the widget has accepted the close event
	ui->tabWidget->addTab(sudokuMainWindow, "Sudoku");
	//sudokuMainWindow->show();
	//ui->tabWidget->sizePolicy().;
	

}

MainWindow::~MainWindow()
{
    delete ui;
}

