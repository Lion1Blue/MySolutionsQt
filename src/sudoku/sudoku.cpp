#include "sudoku.h"
#include "qdebug.h"
#include "qmessagebox.h"
#include <QRandomGenerator>

Sudoku::Sudoku()
{
}

Sudoku::Sudoku(ISudokuMainWindow* sudokuMainWindow)
{
	m_sudokuMainWindow = sudokuMainWindow;
	for (int i = 0; i < 9; i++) {
		m_startingSudoku[i].fill(0);
	}
	m_currentSudoku = m_startingSudoku;

	m_sudokuMainWindow->fillView(m_currentSudoku, m_startingSudoku);
	setIsSolveable(true);
}

Sudoku::Sudoku(ISudokuMainWindow* sudokuMainWindow, std::array<std::array<short, 9>, 9> grid)
{
	m_sudokuMainWindow = sudokuMainWindow;
	m_startingSudoku = grid;
	m_currentSudoku = grid;

	m_sudokuMainWindow->fillView(m_currentSudoku, m_startingSudoku);
	setIsSolveable(solveSudoku(grid, false));
	
}

void Sudoku::setCell(short number, short rowIndex, short columnIndex)
{
	short numberPreClick = m_currentSudoku[rowIndex][columnIndex];

	m_currentSudoku[rowIndex][columnIndex] = number;

	//if Cell is filled with a staring value return
	if (m_startingSudoku[rowIndex][columnIndex] != 0 || number == numberPreClick) { return; }

	Move move(rowIndex, columnIndex, number, numberPreClick, this->m_isSolveable);
	moves.push_back(move);

	m_sudokuMainWindow->setCellText(rowIndex, columnIndex, number);

	//checking for wincondition
	if (!isValidGrid(m_currentSudoku, true)) {
		//checking for a valid grid
		bool validRowColumnBox = isValidGrid(m_currentSudoku, false);
		//checking if the grid is solveable
		if (validRowColumnBox && solveSudoku(m_currentSudoku, false)) {
			setIsSolveable(true);
		}
		else {
			setIsSolveable(false);
		}

	}
	else {
		QMessageBox msgBox;
		msgBox.setText("The Sudoku is solved :D");
		msgBox.exec();
		setIsSolveable(true);
	}
}

void Sudoku::newClicked(short numberOfFilledCells)
{
	m_sudokuMainWindow->updateProgressBar(0);
	//checking if number is a viable number
	if (-1 < numberOfFilledCells && numberOfFilledCells < 82) {
		//create new Puzzle
		std::array<std::array<short, 9>, 9> sudoku = newSudoku(numberOfFilledCells);
		
		//only if the sudoku wasnt cancelled 
		if (!m_cancelSudokuSolving) {
			m_currentSudoku = sudoku;
			m_startingSudoku = sudoku;
			moves.clear();
			setIsSolveable(true);

			//fill View with values
			m_sudokuMainWindow->fillView(m_currentSudoku, m_startingSudoku);
		}
	}

	m_cancelSudokuSolving = false;
}

void Sudoku::undoClicked()
{
	if (!moves.isEmpty()) {
		Move move = moves.last(); // get last move
		moves.pop_back(); // remove last move
		//undo last move
		m_currentSudoku[move.row][move.column] = move.numberPreClick;
		setIsSolveable(move.isValid);
		m_sudokuMainWindow->setCellText(move.row, move.column, move.numberPreClick);

		m_sudokuMainWindow->selectCell(move.row, move.column);
	}
}

void Sudoku::solveClicked()
{
	moves.clear();
	setIsSolveable(true);
	//solve Sudoku
	//m_currentSudoku = m_startingSudoku;
	if (!solveSudoku(m_currentSudoku, true)) {

	}
	m_sudokuMainWindow->fillView(m_currentSudoku, m_startingSudoku);
}

void Sudoku::resetClicked()
{
	moves.clear();
	setIsSolveable(true);
	m_currentSudoku = m_startingSudoku;
	m_sudokuMainWindow->fillView(m_currentSudoku, m_startingSudoku);
}

bool Sudoku::solveSudoku(std::array<std::array<short, 9>, 9>& grid, bool fillSudoku)
{
	m_sudokuMainWindow->processEvents();

	short row, column;
	//looking for empty cells
	if (!findUnassignedLocation(grid, row, column)) {
		return true;
	}
	else if (m_cancelSudokuSolving) {
		return false;
	}

	//going through numbers from 1 to 9
	for (short number = 1; number < 10; number++) {
		//set number if it is valid
		if (isValid(grid, row, column, number)) {

			grid[row][column] = number;

			if (solveSudoku(grid, fillSudoku)) {
				if (!fillSudoku) {
					grid[row][column] = 0;
				}
				return true;
			}
			else {
				//undo if not correct
				grid[row][column] = 0;
			}
		}
	}
	//triggering backtracking
	return false;
}

std::array<std::array<short, 9>, 9> Sudoku::newSudoku(short numberOfFilledCells)
{
	std::array<std::array<short, 9>, 9> grid;
	for (short i = 0; i < 9; i++) {
		grid[i].fill(0);
	}

	unsigned short counter = 0;
	long counterRandom = 0;

	while (counter < numberOfFilledCells && !m_cancelSudokuSolving) {

		short row = QRandomGenerator::global()->bounded(0, 9);
		short column = QRandomGenerator::global()->bounded(0, 9);
		short number = QRandomGenerator::global()->bounded(1, 10);
		counterRandom++;

		// was ist das hier gridbool = !grid[row][column] ??? 
		bool gridbool = !grid[row][column];
		bool isValidBool = isValid(grid, row, column, number);

		if (gridbool && isValidBool) {
			grid[row][column] = number;

			time_t now = time(0);
			char* dt = ctime(&now);
			qDebug() << dt;
			PrintSudoku(grid);
			m_sudokuMainWindow->updateProgressBar(counter * 100 / numberOfFilledCells);

			if (solveSudoku(grid, false)) {
				counter++;
			}
			else {
				grid[row][column] = 0;
			}
		}
	}
	qDebug() << "CounterRandom:" << counterRandom;
	m_sudokuMainWindow->updateProgressBar(100);
	//m_cancelSudokuSolving = false;

	return grid;
}

bool Sudoku::findUnassignedLocation(std::array<std::array<short, 9>, 9>& grid, short & row, short & column)
{
	for (short i = 0; i < 9; i++) {
		for (short j = 0; j < 9; j++) {
			if (grid[i][j] == 0) {
				row = i;
				column = j;
				return true;
			}
		}
	}
	return false;
}

bool Sudoku::isValid(std::array<std::array<short, 9>, 9>& grid, short row, short column, short number)
{
	//check rows and columns
	for (short i = 0; i < 9; i++) {
		if (grid[row][i] == number || grid[i][column] == number) { return false; }
	}

	short startRow = row - row % 3;
	short startColumn = column - column % 3;

	//check 3x3 box
	for (short i = 0; i < 3; i++) {
		for (short j = 0; j < 3; j++) {
			if (grid[startRow + i][startColumn + j] == number) { return false; }
		}
	}

	return true;
}

bool Sudoku::isValidCell(std::array<std::array<short, 9>, 9>& grid, short row, short column)
{
	short number = grid[row][column];
	if (number != 0) {
		grid[row][column] = 0;
		if (isValid(grid, row, column, number)) {
			grid[row][column] = number;
			return true;
		}
		else {
			grid[row][column] = number;
			return false;
		}
	}
	else {
		return true;
	}
}

bool Sudoku::isValidGrid(std::array<std::array<short, 9>, 9>& grid, bool checkForEmpty)
{
	if (checkForEmpty) {
		short row, column;
		//checking for empty cells
		if (findUnassignedLocation(grid, row, column)) {
			return false;
		}
	}

	for (short row = 0; row < 9; row++) {
		for (short column = 0; column < 9; column++) {
			if (!isValidCell(grid, row, column)) { return false; }
		}
	}
	return true;
}

void Sudoku::PrintSudoku(std::array<std::array<short, 9>, 9>& grid)
{
	for (int i = 0; i < 9; i++) {
		std::string row = "";
		for (int j = 0; j < 9; j++) {
			row += std::to_string(grid[i][j]) + ", ";
		}
		qDebug() << row.c_str();
	}

	qDebug() << "\n";
}

void Sudoku::setIsSolveable(bool isSolveable)
{
	m_isSolveable = isSolveable;
	m_sudokuMainWindow->setIsValidLable(isSolveable);
}
