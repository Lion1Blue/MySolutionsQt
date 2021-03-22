#include "sudokumainwindow.h"
#include "./ui_sudokumainwindow.h"
#include "qmessagebox.h"
#include <qdebug.h>
#include <thread>
#include <chrono>


SudokuMainWindow::SudokuMainWindow(QWidget *parent)
    : QMainWindow(parent),
	ui(new Ui::SudokuMainWindow)
{
    ui->setupUi(this);

	connect(ui->pbCancel, SIGNAL(clicked()), this, SLOT(on_pbCancel_clicked()));

	std::array<std::array<short, 9>, 9> sudoku =

		// richtiges Sudoku
		{{{3, 0, 6, 5, 0, 8, 4, 0, 0},
		  {5, 2, 0, 0, 0, 0, 0, 0, 0},
		  {0, 8, 7, 0, 0, 0, 0, 3, 1},
		  {0, 0, 3, 0, 1, 0, 0, 8, 0},
		  {9, 0, 0, 8, 6, 3, 0, 0, 5},
		  {0, 5, 0, 0, 9, 0, 6, 0, 0},
		  {1, 3, 0, 0, 0, 0, 2, 5, 0},
		  {0, 0, 0, 0, 0, 0, 0, 7, 4},
		  {0, 0, 5, 2, 0, 6, 3, 0, 0}}};
		
	m_sudoku = Sudoku(this, sudoku);
	ui->progressBarSudoku->setValue(100);
	ui->pbCancel->setEnabled(false);
}

SudokuMainWindow::~SudokuMainWindow()
{
    delete ui;
}

void SudokuMainWindow::on_pbSolve_clicked()
{
	m_sudoku.solveClicked();
}

void SudokuMainWindow::on_pbReset_clicked()
{
	m_sudoku.resetClicked();
}

void SudokuMainWindow::on_pbUndo_clicked()
{
	m_sudoku.undoClicked();
}

void SudokuMainWindow::on_pbNewPuzzle_clicked()
{
	setEnableButtons(false);
	m_sudoku.newClicked(ui->lineEditNumberOfFilledCells->text().remove(' ').toShort());
	setEnableButtons(true);
}

void SudokuMainWindow::setEnableButtons(bool enabled) {
	ui->pbNewPuzzle->setEnabled(enabled);
	ui->pbSolve->setEnabled(enabled);
	ui->pbReset->setEnabled(enabled);
	ui->pbUndo->setEnabled(enabled);
	ui->pBEmpty->setEnabled(enabled);
	ui->pb1->setEnabled(enabled);
	ui->pb2->setEnabled(enabled);
	ui->pb3->setEnabled(enabled);
	ui->pb4->setEnabled(enabled);
	ui->pb5->setEnabled(enabled);
	ui->pb6->setEnabled(enabled);
	ui->pb7->setEnabled(enabled);
	ui->pb8->setEnabled(enabled);
	ui->pb9->setEnabled(enabled);
	ui->pbCancel->setEnabled(!enabled);
}

void SudokuMainWindow::updateProgressBar(int value) {
	ui->progressBarSudoku->setValue(value);
	qDebug() << "Progress: " << value;
	ui->progressBarSudoku->repaint();
	//if (value == 100) {
	//	//QCoreApplication::sendPostedEvents(this);
	//	QCoreApplication::removePostedEvents(this);
	//}
}

void SudokuMainWindow::processEvents() {
	QCoreApplication::processEvents();
}

void SudokuMainWindow::fillView(std::array<std::array<short, 9>, 9>& grid, std::array<std::array<short, 9>, 9>& startingSudoku) {

	QFont fontBold("Helvetica", 14, QFont::Bold);
	QFont fontNormal("Helvetica", 14, QFont::Normal);

	//set values from array
	for (short i = 0; i < 9; i++) {
		for (short j = 0; j < 9; j++) {

			short number = grid[i][j];
			QTableWidgetItem *pCell = ui->tableWidget->item(i, j);
			pCell = new QTableWidgetItem;

			//change Font depending on if cells is a starting value
			if (startingSudoku[i][j] == 0) {
				pCell->setFont(fontNormal);
			}
			else {
				pCell->setFont(fontBold);
			}

			QString sNumber = "  ";
			if (number != 0) {
				sNumber += QString::number(number);
			}

			//set tableWidgets cell to a new value
			ui->tableWidget->setItem(i, j, pCell);
			//set Celltext
			pCell->setText(sNumber);
		}
	}

	//highlight the pattern
	highlightSudokuPattern(0, 0);
	highlightSudokuPattern(0, 6);
	highlightSudokuPattern(3, 3);
	highlightSudokuPattern(6, 0);
	highlightSudokuPattern(6, 6);
}

void SudokuMainWindow::highlightSudokuPattern(unsigned short rowStart, unsigned short columnStart) {
	for (int row = 0; row < 3; row++) {
		for (int column = 0; column < 3; column++) {
			ui->tableWidget->item(rowStart + row, columnStart + column)->setBackground(Qt::gray);
		}
	}
}

void SudokuMainWindow::setCellText(short row, short column, short number) {

	QString sNumber;
	// 0 is a empty cell
	if (number != 0) {
		sNumber = "  " + QString::number(number);
	}

	ui->tableWidget->item(row, column)->setText(sNumber);
}

void SudokuMainWindow::selectCell(short rowIndex, short columnIndex)
{
	ui->tableWidget->clearSelection(); //deselcet all cells
	ui->tableWidget->setItemSelected(ui->tableWidget->item(rowIndex, columnIndex), true); //select current cell
	currentColumn = columnIndex;
	currentRow = rowIndex;
}

void SudokuMainWindow::setIsValidLable(bool isValid) {
	//setting color of label
	QString styleSheet = isValid ? "QLabel { background-color : green; color : blue; }" : "QLabel { background-color : red; color : blue; }";
	ui->labelIsValid->setStyleSheet(styleSheet);
}

void SudokuMainWindow::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn) {
	this->currentRow = currentRow;
	this->currentColumn = currentColumn;
}

void SudokuMainWindow::on_pBEmpty_clicked() {
	m_sudoku.setCell(0, currentRow, currentColumn);
}
void SudokuMainWindow::on_pbCancel_clicked(){
	m_sudoku.setCancelSudokuSolving(true);
}
void SudokuMainWindow::on_pb1_clicked() {
	m_sudoku.setCell(1, currentRow, currentColumn);
}
void SudokuMainWindow::on_pb2_clicked() {
	m_sudoku.setCell(2, currentRow, currentColumn);
}
void SudokuMainWindow::on_pb3_clicked() {
	m_sudoku.setCell(3, currentRow, currentColumn);
}
void SudokuMainWindow::on_pb4_clicked() {
	m_sudoku.setCell(4, currentRow, currentColumn);
}
void SudokuMainWindow::on_pb5_clicked() {
	m_sudoku.setCell(5, currentRow, currentColumn);
}
void SudokuMainWindow::on_pb6_clicked() {
	m_sudoku.setCell(6, currentRow, currentColumn);
}
void SudokuMainWindow::on_pb7_clicked() {
	m_sudoku.setCell(7, currentRow, currentColumn);
}
void SudokuMainWindow::on_pb8_clicked() {
	m_sudoku.setCell(8, currentRow, currentColumn);
}
void SudokuMainWindow::on_pb9_clicked() {
	m_sudoku.setCell(9, currentRow, currentColumn);
}
