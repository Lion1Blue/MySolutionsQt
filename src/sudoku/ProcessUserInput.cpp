#include "ProcessUserInput.h"
#include "sudokusolver.h"
#include "qmessagebox.h"

ProcessUserInput::ProcessUserInput(SudokuMainWindow * sudokuMainWindow)
{
	m_sudokuMainWindow = sudokuMainWindow;
}

void ProcessUserInput::processInput(unsigned short row, unsigned short column, unsigned short number) {

	//SudokuSolver sudoku;
	//
	//unsigned short numberPreClick = currentSudoku[row][column];
	//
	////if Cell is filled with a staring value return
	//if (startingSudoku[row][column] != 0 || number == numberPreClick) { return; }
	//
	//currentSudoku[row][column] = number;
	//
	//
	//Move move = Move(row, column, number, numberPreClick, m_sudokuMainWindow->getIsSolveable);
	//moves.push_back(move);
	//
	//m_sudokuMainWindow->setCellText(row, column, number);
	//
	////checking for wincondition
	//if (!sudoku.isValidGrid(currentSudoku, true)) {
	//	//checking for a valid grid
	//	bool validRowColumnBox = sudoku.isValidGrid(currentSudoku, false);
	//	//checking if the grid is solveable
	//	if (validRowColumnBox && sudoku.solveSudoku(currentSudoku, false)) {
	//		m_sudokuMainWindow->setIsSolveable(true);
	//	}
	//	else {
	//		m_sudokuMainWindow->setIsSolveable(false);
	//	}
	//
	//}
	//else {
	//	QMessageBox msgBox;
	//	msgBox.setText("The Sudoku is solved :D");
	//	msgBox.exec();
	//	m_sudokuMainWindow->setIsSolveable(true);
	//}
}
