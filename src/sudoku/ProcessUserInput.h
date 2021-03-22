#pragma once

#include <GUI/sudokumainwindow.h>

class ProcessUserInput
{
public:
	ProcessUserInput(SudokuMainWindow *sudokuMainWindow);
	void processInput(unsigned short row, unsigned short column, unsigned short number);

private:
	SudokuMainWindow *m_sudokuMainWindow;
};