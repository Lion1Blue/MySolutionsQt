#pragma once
#include <array>
#include <qlist.h>
#include "ISudokuMainWindow.h"

struct Move {

public:
	Move(short _row, short _column, short _number, short _numberPreClick, bool _isValid) {
		row = _row;
		column = _column;
		number = _number;
		isValid = _isValid;
		numberPreClick = _numberPreClick;
	}

	short row;
	short column;
	short number;
	short numberPreClick;
	bool isValid;
};

class Sudoku
{
public:
	Sudoku();
	Sudoku(ISudokuMainWindow* sudokuMainWindow);
	Sudoku(ISudokuMainWindow* sudokuMainWindow, std::array<std::array<short, 9>, 9> grid);
	void setCell(short number, short rowIndex, short columnIndex);
	void setCancelSudokuSolving(bool cancelSudokuSolving) { m_cancelSudokuSolving = cancelSudokuSolving; }
	bool getCancelSudokuSolving() { return m_cancelSudokuSolving; }
	
	void newClicked(short numberOfFilledCells);
	void undoClicked();
	void solveClicked();
	void resetClicked();

//signals:
//	void updateProgressBar(int);




private:
	ISudokuMainWindow* m_sudokuMainWindow;

	std::array<std::array<short, 9>, 9> newSudoku(short numberOfFilledCells);
	bool solveSudoku(std::array<std::array<short, 9>, 9> &grid, bool fillSudoku);
	bool isValid(std::array<std::array<short, 9>, 9> &grid, short row, short column, short number);
	bool findUnassignedLocation(std::array<std::array<short, 9>, 9> &grid, short& row, short& column);
	bool isValidCell(std::array<std::array<short, 9>, 9> &grid, short row, short column);
	bool isValidGrid(std::array<std::array<short, 9>, 9> &grid, bool checkForEmpty);
	void PrintSudoku(std::array<std::array<short, 9>, 9> &grid);

	void setIsSolveable(bool isSolveable);

	std::array<std::array<short, 9>, 9> m_currentSudoku;
	std::array<std::array<short, 9>, 9> m_startingSudoku;
	QList<Move> moves;
	bool m_cancelSudokuSolving = false;
	bool m_isSolveable = true;

};

